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
#include "../context/ModelContext.h"
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


	class TemplateEngine {
	public:
		TemplateEngine();

		std::list <Node> compile(const std::string& fileName);

		std::list <Node> compile(std::istream& is, const std::string& expectedEndTag = "");

		template<class Context>
		void registerContext() {
			m_scriptingEngine.registerClass<Context>("Context");
			m_scriptingEngine.registerFunction(&Context::getValue, "getValue");
			m_scriptingEngine.registerFunction(&Context::getParentContext, "getParentContext");
		}

		template<class C>
		void registerClass(const std::string& className) {
			m_scriptingEngine.registerClass<C>(className);
		}


		template<class T>
		void registerFunction(const T& f, const std::string& funcName) {
			m_scriptingEngine.registerFunction(f, funcName);
		}

		template<class T>
		void registerVariable(T& v, const std::string& varName) {
			registerVariable(v, varName);
		}

		template<class Context>
		void render(const Context& c, std::ostream& os, const std::list <Node>& tmpl, const Context* parentContext = nullptr) {
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

		script::ScriptEngine& getScriptEngine();

	private:
		std::string extractText(std::istream& is);

		std::string extractNode(std::istream& is);

		void applyTags(const std::deque <std::string>& tags);

		std::list <Node> compileSectionNode(const std::string node, std::istream& is);

		Node compileStartScopeNode(const std::string node, std::istream& is);

		Node compileEndScopeNode(const std::string node, std::istream& is);

		Node compilePartialNode(const std::string node, std::istream& is);

		void compileLocalPartial(const std::string node, std::istream& is);

		Node compileScriptNode(const std::string node, std::istream& is);

		Node compileVariableNode(const std::string node, std::istream& is);

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