#ifndef _CPP_FRONTEND_H_
#define _CPP_FRONTEND_H_

#include "cppming/frontends/FrontendBase.h"

namespace cppming {
	namespace frontends {
		namespace cpp {

			class Frontend : public FrontendBase {
			public:
				virtual void run();

				void runOnFile(const std::string& fileName);

				void setFolder(const std::string& folder);

				cppming::model::Model& getModel();

			private:
				std::string m_folder;
				cppming::model::Model m_model;
			};

		}
	}
}


#endif