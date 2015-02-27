#ifndef _CLANG_FRONTEND_ACTION_FACTORY_H_
#define _CLANG_FRONTEND_ACTION_FACTORY_H_

#include "clang/Tooling/Tooling.h"

#include "cppming/frontends/cpp/ClangFrontendAction.h"

#include "cppming/model/Model.h"


namespace cppming {
	namespace frontends {
		namespace cpp {

			class ClangFrontendActionFactory : public clang::tooling::FrontendActionFactory {
			public:
				ClangFrontendActionFactory(cppming::model::Model& m) : m_model(m) {
				}

				clang::FrontendAction* create() override {
					return new ClangFrontendAction(m_model);
				}

			private:
				cppming::model::Model& m_model;

			};

		}
	}
}

#endif
