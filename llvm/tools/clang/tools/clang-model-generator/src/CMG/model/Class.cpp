#include "CMG/model/Class.h"

namespace CMG {

	Class::Class(Model& m, const std::string& usr) : m_model(m), m_usr(usr) {
	}

	Class::~Class() {
	}

	const std::string& Class::getUSR() const {
		return m_usr;
	}

	void Class::setUSR(const std::string& usr) {
		m_usr = usr;
	}

	const std::string& Class::getName() const {
		return m_name;
	}

	void Class::setName(const std::string& name) {
		m_name = name;
	}

	bool Class::isFinal() const {
		return m_isFinal;
	}

	void Class::setFinal(bool f) {
		m_isFinal = f;
	}

	const std::list<Method>& Class::getMethods() const {
		return m_methods;
	}

}