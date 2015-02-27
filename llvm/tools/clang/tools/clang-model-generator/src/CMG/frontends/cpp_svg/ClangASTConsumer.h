#ifndef _CLANG_AST_CONSUMER_H_
#define _CLANG_AST_CONSUMER_H_

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/Tooling.h"


#include "cppming/frontends/cpp/ClangASTVisitor.h"

namespace cppming {
	namespace frontends {
		namespace cpp {

			// Implementation of the ASTConsumer interface for reading an AST produced
			// by the Clang parser.
			class ClangASTConsumer : public clang::ASTConsumer {
			public:
				ClangASTConsumer(clang::SourceManager& sourceMgr, cppming::model::Model& m) : Visitor(sourceMgr, m) {
				}

				// Override the method that gets called for each parsed top-level
				// declaration.
				bool HandleTopLevelDecl(clang::DeclGroupRef DR) override {
					for(clang::DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
						// Traverse the declaration using our AST visitor.
						Visitor.TraverseDecl(*b);
					}
					return true;
				}

			private:
				ClangASTVisitor Visitor;
			};

		}
	}
}

#endif