#pragma once

#include <vector>
#include <string>

namespace mni {
	namespace tools {
		std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems);

		std::vector<std::string> split(const std::string& s, char delim);
	}
}