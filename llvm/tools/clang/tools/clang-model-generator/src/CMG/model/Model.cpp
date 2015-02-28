#include "CMG/model/Model.h"

#include "CMG/model/Class.h"
#include "CMG/model/Function.h"
#include "CMG/model/Namespace.h"

namespace CMG {

	Model::Model() {
		m_globalNamespace = std::make_unique<Namespace>(*this);
	}

	Model::~Model() {

	}

	bool Model::hasClass(const std::string& usr) const {
		return m_classMap.find(usr) != m_classMap.end();
	}

	bool Model::hasMethod(const std::string& usr) const {
		return m_methodMap.find(usr) != m_methodMap.end();
	}

	bool Model::hasNamespace(const std::string& usr) const {
		return m_namespaceMap.find(usr) != m_namespaceMap.end();
	}

	bool Model::hasParameter(const std::string& usr) const {
		return m_parameterMap.find(usr) != m_parameterMap.end();
	}

	bool Model::hasType(const std::string& usr) const {
		return m_typeMap.find(usr) != m_typeMap.end();
	}


	Class* Model::getClass(const std::string& usr) {
		auto it = m_classMap.find(usr);
		if(it == m_classMap.end()) {
			////throw std::runtime_error("class with USR \"" + usr + "\" not found.");
		}

		if(it->second == nullptr) {
			//throw std::runtime_error("2");
		}

		return (*it).second;
	}

	Method* Model::getMethod(const std::string& usr) {
		auto it = m_methodMap.find(usr);
		if(it == m_methodMap.end()) {
			//throw std::runtime_error("method with USR \"" + usr + "\" not found.");
		}

		if(it->second == nullptr) {
			//throw std::runtime_error("");
		}

		return (*it).second;

	}

	Namespace* Model::getNamespace(const std::string& usr) {
		auto it = m_namespaceMap.find(usr);
		if(it == m_namespaceMap.end()) {
			//throw std::runtime_error("namespace with USR \"" + usr + "\" not found.");
		}

		if(it->second == nullptr) {
			//throw std::runtime_error("");
		}

		return (*it).second;

	}

	Parameter* Model::getParameter(const std::string& usr) {
		auto it = m_parameterMap.find(usr);
		if(it == m_parameterMap.end()) {
			//throw std::runtime_error("parameter with USR \"" + usr + "\" not found.");
		}

		if(it->second == nullptr) {
			//throw std::runtime_error("");
		}

		return (*it).second;

	}

	Type* Model::getType(const std::string& usr) {
		auto it = m_typeMap.find(usr);
		if(it == m_typeMap.end()) {
			//throw std::runtime_error("type with USR \"" + usr + "\" not found.");
		}

		if(it->second == nullptr) {
			//throw std::runtime_error("");
		}

		return (*it).second;

	}


	void Model::addClass(const std::string& usr, Class* clazz) {
		auto it = m_classMap.find(usr);
		if(it != m_classMap.end()) {
			//throw std::runtime_error("class with USR \"" + usr + "\" already exists.");
		}

		m_classMap[usr] = clazz;
	}

	void Model::addMethod(const std::string& usr, Method* method) {
		auto it = m_methodMap.find(usr);
		if(it != m_methodMap.end()) {
			//throw std::runtime_error("method with USR \"" + usr + "\" already exists.");
		}

		m_methodMap[usr] = method;
	}

	void Model::addFunction(const std::string& usr, Function* method) {
		auto it = m_functionMap.find(usr);
		if(it != m_functionMap.end()) {
			//throw std::runtime_error("method with USR \"" + usr + "\" already exists.");
		}

		m_functionMap[usr] = method;
	}

	void Model::addNamespace(const std::string& usr, Namespace* ns) {
		auto it = m_namespaceMap.find(usr);
		if(it != m_namespaceMap.end()) {
			//throw std::runtime_error("namespace with USR \"" + usr + "\" already exists.");
		}

		m_namespaceMap[usr] = ns;
	}

	void Model::addParameter(const std::string& usr, Parameter* p) {
		auto it = m_parameterMap.find(usr);
		if(it != m_parameterMap.end()) {
			//throw std::runtime_error("parameter with USR \"" + usr + "\" already exists.");
		}

		m_parameterMap[usr] = p;
	}

	void Model::addType(const std::string& usr, Type* t) {
		auto it = m_typeMap.find(usr);
		if(it != m_typeMap.end()) {
			//throw std::runtime_error("type with USR \"" + usr + "\" already exists.");
		}

		m_typeMap[usr] = t;
	}
}