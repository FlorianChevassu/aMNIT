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

#include "CMG/model/Model.h"
#include "CMG/model/Namespace.h"
#include "CMG/frontends/cpp/ClangUtils.h"

#include <iostream>


namespace CMG {


	class ClangASTVisitor : public clang::RecursiveASTVisitor<ClangASTVisitor> {
	public:
		ClangASTVisitor(clang::SourceManager& sourceMgr, CMG::Model& m);

		bool VisitNamespaceDecl(clang::NamespaceDecl* ns);

		bool VisitCXXRecordDecl(clang::CXXRecordDecl* c);

		bool VisitCXXMethodDecl(clang::CXXMethodDecl* c);

		bool VisitFunctionDecl(clang::FunctionDecl* c);

		bool VisitCXXConstructorDecl(clang::CXXConstructorDecl* c);

		bool VisitParmVarDecl(clang::ParmVarDecl* d);

		bool VisitDecl(clang::Decl* d);


	private:
		clang::SourceManager* m_sourceManager;
		CMG::Model& m_model;
		clang::SourceLocation m_currentFileSourceLocation;
		bool m_currentFileSourceLocationSet;
	};

}

#endif
