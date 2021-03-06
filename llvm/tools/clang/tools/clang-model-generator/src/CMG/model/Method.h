#pragma once

#include <string>
#include <vector>
#include <memory>


#include "API.h"
#include "CMG/model/AccessSpecifier.h"
#include "CMG/model/Parameter.h"
#include "CMG/model/Model.h"

namespace CMG {

	class Method {
	public:
		Method(Model& m, const std::string& usr);

		Method& operator=(const Method& rhs) = default;

		~Method();

		CMG_API const std::string& getName() const;

		void setName(const std::string& name);

		CMG_API const std::string& getUSR() const;

		void setUSR(const std::string& usr);

		CMG_API bool isFinal() const;

		void setFinal(bool f);

		CMG_API bool isStatic() const;

		void setStatic(bool f);

		CMG_API bool isConst() const;

		void setConst(bool f);

		CMG_API bool isPure() const;

		void setPure(bool f);

		CMG_API AccessSpecifier getAccessSpecifier() const;

		void setAccessSpecifier(AccessSpecifier as);

		CMG_API const std::vector<Parameter>& getParameters() const;

		template<typename... T>
		Parameter* addParameter(const std::string& usr, T... params) {
			m_parameters.emplace_back(*m_model, usr, params...);
			m_model->addParameter(usr, &m_parameters.back());
			return &m_parameters.back();
		}

		Type& getReturnType(){
			return m_returnType;
		}

		const Type& getReturnType() const{
			return m_returnType;
		}

		CMG_API bool isConstructor() const;

		void setConstructor(bool f);

		CMG_API bool isDestructor() const;

		void setDestructor(bool f);


	private:
		Model* m_model;
		std::string m_name;
		std::string m_usr;
		bool m_isFinal;
		bool m_isStatic;
		bool m_isConst;
		bool m_isPure;
		bool m_isCtor;
		bool m_isDtor;

		AccessSpecifier m_accessSpecifier;

		std::vector<Parameter> m_parameters;
		Type m_returnType;
	};
}
