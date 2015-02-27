#pragma once

#include "clang/Tooling/ArgumentsAdjusters.h"


namespace cppming {
	namespace frontends {
		namespace cpp {

			class CommandLineArgumentsAdjuster : public clang::tooling::ArgumentsAdjuster {
			public:
				virtual clang::tooling::CommandLineArguments Adjust(const clang::tooling::CommandLineArguments& Args);
			};

		}
	}
}