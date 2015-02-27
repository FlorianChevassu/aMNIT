#pragma once

#include "clang/Tooling/ArgumentsAdjusters.h"


namespace CMG {

	class CommandLineArgumentsAdjuster : public clang::tooling::ArgumentsAdjuster {
	public:
		virtual clang::tooling::CommandLineArguments Adjust(const clang::tooling::CommandLineArguments& Args);
	};

}