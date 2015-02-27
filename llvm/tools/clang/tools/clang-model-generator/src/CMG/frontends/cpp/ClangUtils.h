#ifndef _CLANG_UTILS_H_
#define _CLANG_UTILS_H_

#include <string>

#include "clang/AST/Decl.h"
#include "clang/Index/USRGeneration.h"


namespace CMG {

	class ClangUtils {
	public:
		static std::string generateUSRForDecl(const clang::Decl* D) {
			llvm::SmallVector<char, 20> buf;
			clang::index::generateUSRForDecl(D, buf);
			return std::string(buf.begin(), buf.end());
		}
	};

}

#endif //_CLANG_UTILS_H_
