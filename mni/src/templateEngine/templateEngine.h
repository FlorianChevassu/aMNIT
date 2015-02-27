#pragma once

#include <string>
#include <list>
#include <stack>
#include <map>
#include <istream>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>


#include "scriptEngine.h"
#include "../model/model.h"
#include <chaiscript/utility/utility.hpp>

namespace mni {

	enum NodeType {
		root,
		text,
		var,
		section,
		code,
		partial,
		startScope,
		endScope,
		tagEditor
	};

	struct Node {

		Node(NodeType t, const std::string& v, const std::deque<std::string>& ts = {}) : type(t), value(v), tags(ts) {
		}

		NodeType type;
		std::string value;
		std::list<Node> children;
		std::deque<std::string> tags;
	};


	struct TemplateEngine {

		TemplateEngine(){
		}

		std::list<Node> compile(const std::string& fileName) {
			using namespace boost::filesystem;
			path p = m_templatePath;
			p.append(fileName.begin(), fileName.end());
			if(exists(p)) {
				std::ifstream ifs;
				ifs.open(p.string());
				if(m_compilingTemplates.find(fileName) == m_compilingTemplates.end()) {
					m_compilingTemplates.insert(fileName);
					std::list<Node> res = compile(ifs);
					m_compiledTemplates[fileName] = res;
				}
				return m_compiledTemplates[fileName];
			} else {
				std::cout << "BAD FILE : " << fileName << std::endl;
			}
		}

		std::string extractText(std::istream& is){
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
			}else{
				//we found the characters "{{".
				ss << s.substr(0, startIndex);

				//"unget" the characters that that we do not need, so that it will be handled by the next iteration.
				for(int i = 0; i < s.substr(startIndex).size()+1; ++i)
					is.unget();
			}

			return ss.str();
		}

		std::string extractNode(std::istream& is){
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
			}else{
				//we found the characters "{{".
				//check if "}}" are on the same line
				endIndex = s.find("}}");
				if(endIndex == std::string::npos && !is.eof()){
					ss << s.substr(startIndex + 2);
					while(std::getline(is, s), (endIndex = s.find("}}")) == std::string::npos && !is.eof()) {
						ss << s << std::endl;
					}

					ss << s.substr(0, endIndex) << std::endl;
					//"unget" the characters that that we do not need, so that it will be handled by the next iteration.
					for(int i = 0; i < s.substr(endIndex + 2).size(); ++i)
						is.unget();
					return ss.str();
				}else{
					//"unget" the characters that that we do not need, so that it will be handled by the next iteration.
					for(int i = 0; i < s.substr(endIndex + 2).size(); ++i)
						is.unget();

					return s.substr(startIndex + 2, endIndex - startIndex - 2);
				}
			}
		}

		void applyTags(const std::deque<std::string>& tags){
			std::for_each(std::begin(tags), std::end(tags), [this](const std::string& tag){
				getState().applyTag(tag);
			});
		}

		std::list<Node> compileSectionNode(const std::string node, std::istream& is){
			std::istringstream iss(node);

			std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
			std::string key = tags[0].substr(1);
			tags.pop_front();

			Node res(NodeType::section, key, tags);

			//compile the stream until the end of section tag has been found
			res.children = compile(is, key);

			//The last node is the "endScope" node. It should be at the same level as the "section" node.
			Node res2 = res.children.back();
			res.children.pop_back();
			return {res, res2};
		}

		Node compileStartScopeNode(const std::string node, std::istream& is){
			std::istringstream iss(node);

			std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
			std::string key = tags[0].substr(1);
			tags.pop_front();

			return {NodeType::startScope, key, tags};
		}

		Node compileEndScopeNode(const std::string node, std::istream& is){
			std::istringstream iss(node);

			std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
			std::string key = tags[0].substr(1);
			tags.pop_front();

			return {NodeType::endScope, key};
		}

		Node compilePartialNode(const std::string node, std::istream& is){
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

		void compileLocalPartial(const std::string node, std::istream& is){
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
			}else{
				//TODO : WARNING
			}
		}

		Node compileScriptNode(const std::string node, std::istream& is){
			return {NodeType::code, node.substr(1)};
		}

		Node compileVariableNode(const std::string node, std::istream& is){
			std::istringstream iss(node);

			std::deque<std::string> tags{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
			std::string key = tags[0];
			tags.pop_front();

			return {NodeType::var, key, tags};
		}

		std::list<Node> compile(std::istream& is, const std::string& expectedEndTag = "") {
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

		template<class Context>
		void registerContext(){
			m_scriptingEngine.registerClass<Context>("Context");
			m_scriptingEngine.registerFunction(&Context::getValue, "getValue");
			m_scriptingEngine.registerFunction(&Context::getParentContext, "getParentContext");
		}

		template<class Context>
		void render(const Context& c, std::ostream& os, const std::list<Node>& tmpl, const Context* parentContext = nullptr) {
			m_scriptingEngine.registerVariable(os, "out");
			m_scriptingEngine.registerVariable(c, "context");

			std::for_each(tmpl.begin(), tmpl.end(), [&](const Node& item) {
				switch(item.type) {
					case NodeType::text:
						if(!getState().skipText)
							os << item.value;
						break;
					case NodeType::var:
						os << c.getValue(item.value);
						break;
					case NodeType::section: {
						//reduce scope of variable secItems to the local case to avoid compiler error.
						pushState();
						applyTags(item.tags);
						auto secItems = c.getSectionItems(item.value);
						std::for_each(secItems.begin(), secItems.end(), [&](const Context& secIt) {
							render<Context>(secIt, os, item.children, &c);
						});
					}
						break;
					case NodeType::partial:
						render<Context>(c, os, m_compiledTemplates[item.value], parentContext);
						break;
					case NodeType::code:
						m_scriptingEngine.eval(item.value);
						break;
					case NodeType::endScope:
						popState();
						break;
					case NodeType::startScope:
						pushState();
						applyTags(item.tags);
						break;
					case NodeType::tagEditor:
						pushState();
						applyTags(item.tags);
						break;
					default:
						throw std::exception();//TODO
				}
			});
		}

		void setTemplatePath(const boost::filesystem::path& p) {
			m_templatePath = p;
		}

	private:
		boost::filesystem::path m_templatePath;
		std::set<std::string> m_compilingTemplates;
		std::map<std::string, std::list<Node>> m_compiledTemplates;
		script::ScriptEngine m_scriptingEngine;

		/*
		* Engine state stack
		*/
		struct EngineState{
			//flags
			bool skipText = false;
			bool verbatim = false;

			//state
			std::string expectedEndTag;


			//TODO : fill this method...
			void applyTag(const std::string& tag){
				if(tag.compare("skipText") == 0)
					skipText = true;
				else if(tag.compare("!skipText") == 0)
					skipText = false;
				else if(tag.compare("verbatim") == 0)
					verbatim = true;
				else if(tag.compare("!verbatim") == 0)
					verbatim = false;
			}
		};

		std::stack<EngineState> m_engineStateStack;

		void pushState(){
			m_engineStateStack.push(m_engineStateStack.top());
		}
		void popState(){
			m_engineStateStack.pop();
		}

		EngineState& getState(){
			if(m_engineStateStack.size() == 0){
				m_engineStateStack.push(EngineState());
			}
			return m_engineStateStack.top();
		}
	};
}