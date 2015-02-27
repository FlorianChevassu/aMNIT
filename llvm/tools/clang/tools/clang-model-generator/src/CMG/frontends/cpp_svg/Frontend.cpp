#include "cppming/frontends/cpp/Frontend.h"

#include <exception>
#include <sstream>

#include <boost/filesystem.hpp>


#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include "cppming/frontends/cpp/ClangFrontendAction.h"
#include "cppming/frontends/cpp/ClangFrontendActionFactory.h"
#include "cppming/frontends/cpp/CommandLineArgumentsAdjuster.h"
#include "cppming/frontends/cpp/Frontend.h"

namespace cppming {
	namespace frontends {
		namespace cpp {


			void Frontend::setFolder(const std::string& folder) {
				m_folder = folder;
			}

			static llvm::cl::OptionCategory cppFrontendCategory("CppFrontendCategory");

			void Frontend::runOnFile(const std::string& fileName) {
				const char* argv[] = {
						"dummy",
						fileName.c_str(),
						"--"
				};

				int argc = sizeof(argv) / sizeof(argv[0]);

				clang::tooling::CommonOptionsParser op(argc, argv, cppFrontendCategory);
				clang::tooling::ClangTool tool(op.getCompilations(), op.getSourcePathList());

				//on ajoute un commandlineadjuster qui va ajouter les paths spécifiés dans la config pour la std
				clang::tooling::ArgumentsAdjuster* argAdj = new cppming::frontends::cpp::CommandLineArgumentsAdjuster();

				tool.appendArgumentsAdjuster(argAdj);

				cppming::frontends::cpp::ClangFrontendActionFactory f(m_model);

				int res = tool.run(&f);
			}

			void Frontend::run() {
				using namespace boost::filesystem;

				path p(m_folder);

				if(exists(p)) {
					if(is_regular_file(p)) {
						runOnFile(p.string());
					} else if(is_directory(p)) {
						for(directory_iterator it = directory_iterator(p); it != directory_iterator(); ++it) {
							if(is_regular_file(it->path()) && (it->path().extension().compare(".h") == 0 || it->path().extension().compare(".hpp") == 0))
								runOnFile(it->path().string());
						}
					} else {
						std::stringstream ss;
						ss << p << " exists, but is neither a regular file nor a directory." << std::endl;
						throw std::runtime_error(ss.str().c_str());
					}
				} else {
					std::stringstream ss;
					ss << p << " does not exist." << std::endl;
					throw std::runtime_error(ss.str().c_str());
				}

			}

			cppming::model::Model& Frontend::getModel() {
				return m_model;
			}

		}
	}
}
