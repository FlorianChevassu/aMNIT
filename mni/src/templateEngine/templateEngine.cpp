#include "templateEngine.h"
#include "../tools/stringUtils.h"

namespace mni {

	TemplateEngine::TemplateEngine() {
	}

	std::list<Node> TemplateEngine::compile(const std::string& fileName) {
		using namespace boost::filesystem;
		path p = m_templatePath;
		p.append(fileName.begin(), fileName.end());
		if(!exists(p)) {
			throw std::runtime_error("The file does not exist.");
		}
		std::ifstream ifs;
		ifs.open(p.string());
		if(m_compilingTemplates.find(fileName) == m_compilingTemplates.end()) {
			m_compilingTemplates.insert(fileName);
			std::list<Node> res = compile(ifs);
			m_compiledTemplates[fileName] = res;
		}
		return m_compiledTemplates[fileName];

	}

	std::list<Node> TemplateEngine::compile(std::istream& is, const std::string& expectedEndTag) {
		std::stringstream ss;
		std::string s;

		std::list<Node> res;

		std::string::size_type startIndex;
		std::string::size_type endIndex;

		while(is.good()) {
			res.emplace_back(NodeType::text, extractText(is));

			std::string node = extractNode(is);

			//the size of the string "node" may be equal to zero if the last node was a text node.
			if(node.size() > 0) {
				//detect the node type

				switch(node[0]) {
					case '#':
						res.splice(res.end(), compileSectionNode(node, is));
						break;
					case '\\':
						res.push_back(compileStartScopeNode(node, is));
						return res;
					case '/':
						res.push_back(compileEndScopeNode(node, is));
						return res;
					case '>':
						res.push_back(compilePartialNode(node, is));
						break;
					case '<':
						compileLocalPartial(node, is);
						break;
					case '=':
						res.push_back(compileScriptNode(node, is));
						break;
					case '!':
						//comment. Nothing to do
						break;
					default:
						res.push_back(compileVariableNode(node, is));
						break;
				}
			}
		}
		return res;
	}

	std::string TemplateEngine::extractText(std::istream& is) {
		std::string::size_type startIndex;
		std::stringstream ss;
		std::string s;

		std::getline(is, s);
		while((startIndex = s.find("{{")) == std::string::npos && !is.eof()) {
			ss << s << std::endl;
			std::getline(is, s);
		}

		//if we are at the end of the file
		if(startIndex == std::string::npos && is.eof()) {
			ss << s;
		} else {
			//we found the characters "{{".
			ss << s.substr(0, startIndex);

			//"unget" the characters that that we do not need, so that it will be handled by the next iteration.
			for(int i = 0; i < s.substr(startIndex).size() + 1; ++i)
				is.unget();
		}

		return ss.str();
	}

	std::string TemplateEngine::extractNode(std::istream& is) {
		std::string::size_type startIndex;
		std::string::size_type endIndex;
		std::stringstream ss;
		std::string s;

		std::getline(is, s);
		while((startIndex = s.find("{{")) == std::string::npos && !is.eof()) {
			std::getline(is, s);
		}

		//if we are at the end of the file
		if(startIndex == std::string::npos && is.eof()) {
			return "";
		} else {
			//we found the characters "{{".
			//check if "}}" are on the same line
			endIndex = s.find("}}");
			if(endIndex == std::string::npos && !is.eof()) {
				ss << s.substr(startIndex + 2);
				while(std::getline(is, s), (endIndex = s.find("}}")) == std::string::npos && !is.eof()) {
					ss << s << std::endl;
				}

				ss << s.substr(0, endIndex) << std::endl;
				//"unget" the characters that that we do not need, so that it will be handled by the next iteration.
				for(int i = 0; i < s.substr(endIndex + 2).size() + 1; ++i)
					is.unget();
				return ss.str();
			} else {
				//"unget" the characters that that we do not need, so that it will be handled by the next iteration.
				for(int i = 0; i < s.substr(endIndex + 2).size() + 1; ++i)
					is.unget();

				return s.substr(startIndex + 2, endIndex - startIndex - 2);
			}
		}
	}


	void TemplateEngine::applyTags(const std::deque<std::string>& tags) {
		std::for_each(std::begin(tags), std::end(tags), [this](const std::string& tag) {
			getState().applyTag(tag);
		});
	}

	std::list<Node> TemplateEngine::compileSectionNode(const std::string node, std::istream& is) {
		std::istringstream iss(node);

		std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		std::string key = tags[0].substr(1);
		tags.pop_front();

		//if key contains points ('.'), split it into multiple sections
		std::vector<std::string> sections = mni::tools::split(key, '.');

		//Node res(NodeType::section, sections[0], tags);
		std::list<Node> res;
		std::list<Node>* currentNodeList = &res;
		for(auto sec : sections) {
			currentNodeList->push_back({NodeType::section, sec, tags});
			currentNodeList->push_back({NodeType::endScope, sec});
			currentNodeList = &(currentNodeList->front().children);
		}

		//compile the stream until the end of section tag has been found
		*currentNodeList = compile(is, sections.back());

		//The last node is the "endScope" node. It should be at the same level as the "section" node.
		currentNodeList->pop_back();
		return res;
	}

	Node TemplateEngine::compileStartScopeNode(const std::string node, std::istream& is) {
		std::istringstream iss(node);

		std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		std::string key = tags[0].substr(1);
		tags.pop_front();

		return {NodeType::startScope, key, tags};
	}

	Node TemplateEngine::compileEndScopeNode(const std::string node, std::istream& is) {
		std::istringstream iss(node);

		std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		std::string key = tags[0].substr(1);
		tags.pop_front();

		return {NodeType::endScope, key};
	}

	Node TemplateEngine::compilePartialNode(const std::string node, std::istream& is) {
		std::istringstream iss(node);

		std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		std::string key = tags[0].substr(1);
		tags.pop_front();


		//partial defined in the file named as "key"
		if(m_compiledTemplates.find(key) == m_compiledTemplates.end()
				&& m_compilingTemplates.find(key) == m_compilingTemplates.end()) {
			compile(key);
		}

		return {NodeType::partial, key, tags};
	}

	void TemplateEngine::compileLocalPartial(const std::string node, std::istream& is) {
		std::istringstream iss(node);

		std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		std::string key = tags[0].substr(1);
		tags.pop_front();

		//definition of a local partial
		//if the name already exists, we omit this declaration
		if(m_compiledTemplates.find(key) == m_compiledTemplates.end()) {
			m_compilingTemplates.insert(key);
			m_compiledTemplates[key].push_back({NodeType::startScope, key, tags});
			m_compiledTemplates[key].splice(std::end(m_compiledTemplates[key]), compile(is, key));
			//endScope is useless here because it will be handled by the end tag of the local partial
			//m_compiledTemplates[key].push_back({NodeType::endScope, "", tags});
		} else {
			//TODO : WARNING
		}
	}

	Node TemplateEngine::compileScriptNode(const std::string node, std::istream& is) {
		return {NodeType::code, node.substr(1)};
	}

	Node TemplateEngine::compileVariableNode(const std::string node, std::istream& is) {
		std::istringstream iss(node);

		std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
		std::string key = tags[0];
		tags.pop_front();

		return {NodeType::var, key, tags};
	}

	script::ScriptEngine& TemplateEngine::getScriptEngine() {
		return m_scriptingEngine;
	}
}