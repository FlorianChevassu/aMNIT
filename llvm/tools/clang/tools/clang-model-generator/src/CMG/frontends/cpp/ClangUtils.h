#ifndef _CLANG_UTILS_H_
#define _CLANG_UTILS_H_

#include <string>

#include "clang/AST/Decl.h"
#include "clang/Index/USRGeneration.h"

#include "../../model/AccessSpecifier.h"


namespace CMG {

	class ClangUtils {
	public:
		static std::string generateUSRForDecl(const clang::Decl* D) {
			llvm::SmallVector<char, 20> buf;
			clang::index::generateUSRForDecl(D, buf);
			return std::string(buf.begin(), buf.end());
		}
		static AccessSpecifier getAccessSpecifier(const clang::Decl* d) {
			switch(d->getAccess()) {
				case clang::AS_public:
					return CMG::AS_public;
				case clang::AS_protected:
					return CMG::AS_protected;
				case clang::AS_private:
					return CMG::AS_private;
				case clang::AS_none:
					throw std::runtime_error("AS_none access specifier not handled");
			}

			throw std::runtime_error("Unknown access specifier...");
		}
	};

}

#endif //_CLANG_UTILS_H_
