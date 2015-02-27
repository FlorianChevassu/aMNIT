#ifndef _CLANG_AST_VISITOR_H_
#define _CLANG_AST_VISITOR_H_

#include "clang/AST/AST.h"
#include "clang/AST/Decl.h"
#include "clang/AST/Type.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Lexer.h"
#include "clang/Index/USRGeneration.h"

#include "llvm/Support/Casting.h"

#include "cppming/model/Model.h"
#include "cppming/model/Namespace.h"
#include "cppming/frontends/cpp/ClangUtils.h"

#include <iostream>


namespace cppming {
	namespace frontends {
		namespace cpp {


			class ClangASTVisitor : public clang::RecursiveASTVisitor<ClangASTVisitor> {
			public:
				ClangASTVisitor(clang::SourceManager& sourceMgr, cppming::model::Model& m);

				/*
				Visit, create and add namespaces to the model.
				*/
				bool VisitNamespaceDecl(clang::NamespaceDecl* ns);

				bool VisitCXXRecordDecl(clang::CXXRecordDecl* c);

				bool VisitFunctionDecl(clang::FunctionDecl* c);

				bool VisitParmVarDecl(clang::ParmVarDecl* d);

				bool VisitDecl(clang::Decl* d);


			private:
				clang::SourceManager* m_sourceManager;
				cppming::model::Model& m_model;
				clang::SourceLocation m_currentFileSourceLocation;
				bool m_currentFileSourceLocationSet;
			};

		}
	}
}

#endif
