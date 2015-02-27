#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "scriptEngine.h"
#include <chrono>
#include <regex>


namespace mni{
	namespace script{

		template <class T>
		std::ostream& print_ostream(std::ostream& os, const T& s) {
			return os << s;
		}

		template <>
		std::ostream& print_ostream(std::ostream& os, const std::time_t& s) {
			//ctime always print \n at the end of the string...
			std::string time = std::string(std::ctime(&s));
			return os << time.substr(0, time.length()-1);
		}


		std::time_t getDate() {
			return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		}

//		const std::string& toIdentifierString(const std::string& s){
//			return std::regex_replace(s, "[0-9a-fA-F]", "[$&]");
//		}

		ScriptEngine::ScriptEngine() : ChaiScript(chaiscript::Std_Lib::library()){
			add(chaiscript::fun(&print_ostream<std::string>), "<<");
			add(chaiscript::fun(&print_ostream<std::time_t>), "<<");
			add(chaiscript::fun(&getDate), "getDate");
		}
	}
}