#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>


#include "API.h"
#include "CMG/model/Parameter.h"
#include "CMG/model/Model.h"

namespace CMG {

	class Function {
	public:
		Function(Model& m, const std::string& usr);

		~Function();

		CMG_API const std::string& getName() const;

		void setName(const std::string& name);

		CMG_API const std::string& getUSR() const;

		void setUSR(const std::string& usr);

		CMG_API const std::list<Parameter>& getParameters() const;

		template<typename... T>
		Parameter* addParameter(const std::string& usr, T... params) {
			m_parameters.emplace_back(m_model, usr, params...);
			m_model.addParameter(usr, &m_parameters.back());
			return &m_parameters.back();
		}

		Type& getReturnType() {
			return m_returnType;
		}

		const Type& getReturnType() const {
			return m_returnType;
		}


	private:
		Model& m_model;
		std::string m_name;
		std::string m_usr;

		std::list<Parameter> m_parameters;
		Type m_returnType;
	};
}
