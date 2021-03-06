#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "scriptEngine.h"
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

		std::string toIdentifier(std::string s) {
			auto pred = [](auto& c) {
				return c != '_' && !std::isalnum(c);
			};
			auto index = std::find_if(s.begin(), s.end(), pred);
			while(index != s.end()) {
				*index = '_';
				index = std::find_if(s.begin(), s.end(), pred);
			}

			//first character must be either '_' or a letter
			if(s[0] != '_' && !std::isalpha(s[0]))
				s[0] = '_';

			return s;
		}

		ScriptEngine::ScriptEngine() : ChaiScript(chaiscript::Std_Lib::library()){
			add(chaiscript::fun(&print_ostream<std::string>), "<<");
			add(chaiscript::fun(&print_ostream<std::time_t>), "<<");
			add(chaiscript::fun(&print_ostream<std::size_t>), "<<");
			add(chaiscript::fun(&getDate), "getDate");
			add(chaiscript::fun(&toIdentifier), "toIdentifier");
		}
	}
}