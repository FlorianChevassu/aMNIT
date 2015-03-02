#pragma once

#include <string>
#include <memory>
#include <list>


#include "API.h"
#include "CMG/model/Model.h"
#include "CMG/model/Class.h"
#include "CMG/model/Function.h"

namespace CMG {

	class Namespace {
	public:
		Namespace(Model& m, const std::string& usr = "");

		Namespace& operator=(const Namespace& rhs) = default;

		virtual ~Namespace();

		CMG_API const std::string& getUSR() const;

		void setUSR(const std::string& usr);

		CMG_API const std::string& getName() const;

		void setName(const std::string& name);

		CMG_API const std::vector<Class>& getClasses() const;

		template<typename... T>
		Class* addClass(const std::string& usr, T... params) {
			m_classes.emplace_back(*m_model, usr, params...);
			m_model->addClass(usr, &m_classes.back());
			return &m_classes.back();
		}

		CMG_API const std::vector<Function>& getFunctions() const;

		template<typename... T>
		Function* addFunction(const std::string& usr, T... params) {
			m_functions.emplace_back(*m_model, usr, params...);
			m_model->addFunction(usr, &m_functions.back());
			return &m_functions.back();
		}

		CMG_API const std::vector<Namespace>& getNamespaces() const;

		template<typename... T>
		Namespace* addNamespace(const std::string& usr, T... params) {
			m_namespaces.emplace_back(*m_model, usr, params...);
			m_model->addNamespace(usr, &m_namespaces.back());
			return &m_namespaces.back();
		}

	private:
		Model* m_model;
		std::string m_usr;
		std::string m_name;
		std::vector<Class> m_classes;
		std::vector<Function> m_functions;
		std::vector<Namespace> m_namespaces;
	};
}
