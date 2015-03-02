#include "CMG/model/Parameter.h"

namespace CMG {

	Parameter::Parameter(Model& m, const std::string& usr) : m_model(&m), m_usr(usr) {
	}

	Parameter::~Parameter() {
	}

	const std::string& Parameter::getUSR() const {
		return m_usr;
	}

	void Parameter::setUSR(const std::string& usr) {
		m_usr = usr;
	}

	const std::string& Parameter::getName() const {
		return m_name;
	}

	void Parameter::setName(const std::string& name) {
		m_name = name;
	}

	const Type& Parameter::getType() const {
		return m_type;
	}

	Type& Parameter::getType() {
		return m_type;
	}
}