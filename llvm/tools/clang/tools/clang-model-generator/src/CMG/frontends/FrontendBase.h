#ifndef _FRONTEND_BASE_H_
#define _FRONTEND_BASE_H_

#include "CMG/model/Model.h"


namespace CMG {

	class FrontendBase {
	public:
		FrontendBase() {
		}

		virtual ~FrontendBase() {
		}

		virtual void run() = 0;

		Model& getModel() {
			return m_model;
		}

	protected:
		Model m_model;
	};

}

#endif
