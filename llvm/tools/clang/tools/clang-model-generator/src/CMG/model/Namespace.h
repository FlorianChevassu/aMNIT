#ifndef _MODEL_NAMESPACE_
#define _MODEL_NAMESPACE_

#include <string>
#include <memory>
#include <list>


#include "API.h"
#include "CMG/model/Class.h"
#include "CMG/model/Model.h"

namespace CMG {

	class Namespace {
	public:
		Namespace(Model& m, const std::string& usr = "");

		virtual ~Namespace();

		CMG_API const std::string& getUSR() const;

		void setUSR(const std::string& usr);

		CMG_API const std::string& getName() const;

		void setName(const std::string& name);

		CMG_API const std::list<Class>& getClasses() const;

		template<typename... T>
		Class* addClass(const std::string& usr, T... params) {
			m_classes.emplace_back(m_model, usr, params...);
			m_model.addClass(usr, &m_classes.back());
			return &m_classes.back();
		}

		CMG_API const std::list<Namespace>& getNamespaces() const;

		template<typename... T>
		Namespace* addNamespace(const std::string& usr, T... params) {
			m_namespaces.emplace_back(m_model, usr, params...);
			m_model.addNamespace(usr, &m_namespaces.back());
			return &m_namespaces.back();
		}

	private:
		Model& m_model;
		std::string m_usr;
		std::string m_name;
		std::list<Class> m_classes;
		std::list<Namespace> m_namespaces;
	};
}
#endif