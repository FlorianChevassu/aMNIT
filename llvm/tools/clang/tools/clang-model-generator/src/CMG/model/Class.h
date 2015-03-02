#pragma once

#include <string>
#include <memory>
#include <vector>


#include "API.h"
#include "CMG/model/Method.h"
#include "CMG/model/Model.h"

namespace CMG {

	class Class {
	public:
		Class(Model& m, const std::string& usr);

		Class& operator=(const Class& rhs) = default;

		~Class();

		template<typename... T>
		Method* addMethod(const std::string& usr, T... params) {
			m_methods.emplace_back(*m_model, usr, params...);
			m_model->addMethod(usr, &m_methods.back());
			return &m_methods.back();
		}

		CMG_API const std::string& getName() const;

		void setName(const std::string& name);

		CMG_API const std::string& getUSR() const;

		void setUSR(const std::string& usr);

		CMG_API bool isFinal() const;

		void setFinal(bool f);

		CMG_API const std::vector<Method>& getMethods() const;

	private:
		Model* m_model;
		std::string m_usr;
		std::string m_name;
		bool m_isFinal;

		std::vector<Method> m_methods;
	};
}