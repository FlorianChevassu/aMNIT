#pragma once

#include <chaiscript/chaiscript.hpp>

namespace mni {
	namespace script {
		class ScriptEngine : public chaiscript::ChaiScript{
		public:
			ScriptEngine();

			template<class Class>
			void registerClass(const std::string& className){
				static bool added = false;
				if(!added) {
					add(chaiscript::user_type<Class>(), className);
					added = true;
				}else{
					throw ScriptEngine::Exception("Class already registered.");
				}
			}

			template <class T>
			void registerFunction(const T& f, const std::string& funcName){
				static std::set<std::string> m_addedFunctions;
				if(m_addedFunctions.find(funcName) == m_addedFunctions.end()) {
					add(chaiscript::fun(f), funcName);
					m_addedFunctions.insert(funcName);
				}else{
					throw ScriptEngine::Exception("Function name already registered.");
				}
			}

			template <class T>
			void registerVariable(T& v, const std::string& varName){
				add(chaiscript::var(&v), varName);
			}

			///Exceptions

			class Exception : public std::runtime_error{
			public:
				Exception(const std::string& message) : std::runtime_error(message.c_str()){

				}
			};
		};
	}
}