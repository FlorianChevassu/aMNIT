#include "cppming/frontends/cpp/CommandLineArgumentsAdjuster.h"


#include  <iostream>


namespace cppming {
	namespace frontends {
		namespace cpp {

			clang::tooling::CommandLineArguments CommandLineArgumentsAdjuster::Adjust(const clang::tooling::CommandLineArguments& args) {
				clang::tooling::CommandLineArguments res = args;

				//obtained by compiling an empty c++ file with : g++ a.cpp -v -E
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\include\\c++");
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\include\\c++\\mingw32");
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\include\\c++\\backward");
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\include");
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\..\\..\\..\\..\\include");
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\include-fixed");
// 	res.insert(++res.begin(), "-Ic:\\users\\chevassu\\documents\\llvm\\mingw\\bin\\..\\lib\\gcc\\mingw32\\4.8.1\\..\\..\\..\\..\\mingw32\\include");
				res.insert(++res.begin(), "-xc++");
				res.insert(++res.begin(), "-std=c++11");
// 	res.insert(++res.begin(), "-fno-ms-compatibility");//because there are problems with char_32_t with compatibility activated...

				/*std::cout << "res = " << std::endl;
				for (int i = 0; i < res.size(); ++i){
					std::cout << res.at(i) << std::endl;
				}*/


				return res;
			}

		}
	}
}