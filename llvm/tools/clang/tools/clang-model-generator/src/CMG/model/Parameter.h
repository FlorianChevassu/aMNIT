#pragma once

#include <string>
#include <list>
#include <memory>


#include "API.h"
#include "CMG/model/Model.h"
#include "CMG/model/Type.h"

namespace CMG {
	class Parameter {
	public:
		Parameter(Model& m, const std::string& usr);

		Parameter& operator=(const Parameter& rhs) = default;

		~Parameter();

		CMG_API const std::string& getName() const;

		void setName(const std::string& name);

		CMG_API const std::string& getUSR() const;

		void setUSR(const std::string& usr);

		Type& getType();

		CMG_API const Type& getType() const;

	private:
		Model* m_model;
		std::string m_usr;
		std::string m_name;
		Type m_type;
	};
}
