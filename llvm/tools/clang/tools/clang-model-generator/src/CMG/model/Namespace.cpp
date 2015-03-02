#include "CMG/model/Namespace.h"

namespace CMG {

	Namespace::Namespace(Model& m, const std::string& usr) : m_model(&m), m_usr(usr) {
	}

	Namespace::~Namespace() {
	}

	const std::string& Namespace::getUSR() const {
		return m_usr;
	}

	void Namespace::setUSR(const std::string& usr) {
		m_usr = usr;
	}

	const std::string& Namespace::getName() const {
		return m_name;
	}

	void Namespace::setName(const std::string& name) {
		m_name = name;
	}

	const std::vector<Class>& Namespace::getClasses() const {
		return m_classes;
	}

	const std::vector<Function>& Namespace::getFunctions() const {
		return m_functions;
	}

	const std::vector<Namespace>& Namespace::getNamespaces() const {
		return m_namespaces;
	}

}