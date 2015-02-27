#ifndef _CPP_FRONTEND_H_
#define _CPP_FRONTEND_H_


#include "API.h"
#include "CMG/model/Model.h"

#include <set>
#include <string>
#include <memory>

namespace CMG {

	class Frontend {
	public:
		~Frontend();

		CMG_API void addFolder(const char* folderName);

		CMG_API void run();

		CMG_API void addFile(const std::string& file);

		CMG_API void addFolder(const std::string& folder);

		CMG_API CMG::Model& getModel();

	private:
		CMG::Model m_model;

		std::set<std::string> m_files;
	};

	CMG_API void destroyFrontend(Frontend* f);

	CMG_API Frontend* getFrontend();
}


#endif