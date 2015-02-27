#ifndef _CLANG_FRONTEND_ACTION_FACTORY_H_
#define _CLANG_FRONTEND_ACTION_FACTORY_H_

#include "clang/Tooling/Tooling.h"

#include "CMG/frontends/cpp/ClangFrontendAction.h"

#include "CMG/model/Model.h"


namespace CMG {

	class ClangFrontendActionFactory : public clang::tooling::FrontendActionFactory {
	public:
		ClangFrontendActionFactory(CMG::Model& m) : m_model(m) {
		}

		clang::FrontendAction* create() override {
			return new ClangFrontendAction(m_model);
		}

	private:
		CMG::Model& m_model;

	};

}

#endif
