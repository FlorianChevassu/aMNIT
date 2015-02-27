#include "CMG/frontends/cpp/Frontend.h"

#include <exception>
#include <sstream>

#ifdef _WIN32
#include <filesystem>
#else

#include <boost/filesystem.hpp>

#endif

#include <memory>
#include <string>


#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include "CMG/frontends/cpp/ClangFrontendAction.h"
#include "CMG/frontends/cpp/ClangFrontendActionFactory.h"
#include "CMG/frontends/cpp/CommandLineArgumentsAdjuster.h"
#include "CMG/frontends/cpp/Frontend.h"

namespace CMG {

	Frontend::~Frontend() {
	}

	static llvm::cl::OptionCategory cppFrontendCategory("CppFrontendCategory");

	void Frontend::addFolder(const char* folderName) {
		addFolder(std::string(folderName));
	}

	void Frontend::addFile(const std::string& file) {
#ifdef _WIN32
		using namespace std::tr2::sys;
		#else
		using namespace boost::filesystem;
#endif
		path p(file);
		if(exists(p)) {
			if(is_regular_file(p) && (p.extension().compare(".h") == 0 || p.extension().compare(".hpp") == 0))
				m_files.insert(p.string());
		}
		else {
			std::stringstream ss;
			ss << p << " does not exist." << std::endl;
			throw std::runtime_error(ss.str().c_str());
		}
	}

	void Frontend::addFolder(const std::string& folder) {
#ifdef _WIN32
		using namespace std::tr2::sys;
		#else
		using namespace boost::filesystem;
#endif
		path p(folder);
		if(exists(p)) {
			if(is_directory(p)) {
				for(directory_iterator it = directory_iterator(p); it != directory_iterator(); ++it) {
					addFile(it->path().string());
				}
			}
		}
		else {
			std::stringstream ss;
			ss << p << " does not exist." << std::endl;
			throw std::runtime_error(ss.str().c_str());
		}
	}

	void Frontend::run() {
		int argc = m_files.size() + 2;
		std::vector<const char*> argv(argc);
		argv[0] = "dummy";
		int i = 0;
		for(auto it = std::begin(m_files); it != std::end(m_files); ++it, ++i)
			argv[i + 1] = it->c_str();
		argv[m_files.size() + 1] = "--";

		clang::tooling::CommonOptionsParser op(argc, &argv[0], cppFrontendCategory);
		clang::tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());

		//on ajoute un commandlineadjuster qui va ajouter les paths spécifiés dans la config pour la std
		clang::tooling::ArgumentsAdjuster* argAdj = new CMG::CommandLineArgumentsAdjuster();
		tool.appendArgumentsAdjuster(argAdj);

		CMG::ClangFrontendActionFactory f(m_model);

		tool.run(&f);
	}

	CMG::Model& Frontend::getModel() {
		return m_model;
	}

	void destroyFrontend(Frontend* f) {
		delete f;
	}

	Frontend* getFrontend() {
		return new Frontend();
	}

}
