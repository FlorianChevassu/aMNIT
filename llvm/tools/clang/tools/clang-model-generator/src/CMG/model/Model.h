#ifndef _MODEL_MODEL_
#define _MODEL_MODEL_


#include <map>
#include <memory>

#include "API.h"

namespace CMG {

	class Class;

	class Method;

	class Namespace;

	class Parameter;

	class Type;


	class Model {
	public:
		Model();

		~Model();

		bool hasClass(const std::string& usr) const;

		bool hasMethod(const std::string& usr) const;

		bool hasNamespace(const std::string& usr) const;

		bool hasParameter(const std::string& usr) const;

		bool hasType(const std::string& usr) const;

		CMG_API Class* getClass(const std::string& usr);

		CMG_API Method* getMethod(const std::string& usr);

		CMG_API Namespace* getNamespace(const std::string& usr);

		CMG_API Parameter* getParameter(const std::string& usr);

		CMG_API Type* getType(const std::string& usr);

		void addClass(const std::string& usr, Class* clazz);

		void addMethod(const std::string& usr, Method* method);

		void addNamespace(const std::string& usr, Namespace* ns);

		void addParameter(const std::string& usr, Parameter* p);

		void addType(const std::string& usr, Type* t);

		CMG_API Namespace* getGlobalNamespace() {
			return m_globalNamespace.get();
		}


	private:
		std::unique_ptr<Namespace> m_globalNamespace;
		std::map<std::string, Class*> m_classMap;
		std::map<std::string, Method*> m_methodMap;
		std::map<std::string, Namespace*> m_namespaceMap;
		std::map<std::string, Parameter*> m_parameterMap;
		std::map<std::string, Type*> m_typeMap;
	};
}
#endif