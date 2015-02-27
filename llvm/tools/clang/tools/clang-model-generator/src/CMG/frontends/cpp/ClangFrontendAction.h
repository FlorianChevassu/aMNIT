#ifndef _CLANG_FRONTEND_ACTION_H_
#define _CLANG_FRONTEND_ACTION_H_

#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/Tooling.h"

#include "CMG/frontends/cpp/ClangASTConsumer.h"
#include "CMG/model/Model.h"


namespace CMG {

	// For each source file provided to the tool, a new FrontendAction is created.
	class ClangFrontendAction : public clang::ASTFrontendAction {
	public:
		ClangFrontendAction(CMG::Model& m) : m_model(m) {
		}

		clang::ASTConsumer* CreateASTConsumer(clang::CompilerInstance& ci, clang::StringRef file) override {
			//llvm::errs() << "** Creating AST consumer for: " << file << "\n";
			return new ClangASTConsumer(ci.getSourceManager(), m_model);
		}

	private:
		CMG::Model& m_model;
	};

}

#endif
