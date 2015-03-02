#include "CMG/model/Function.h"

namespace CMG {

	Function::Function(Model& m, const std::string& usr) : m_model(&m), m_usr(usr) {
	}

	Function::~Function() {
	}

	const std::string& Function::getUSR() const {
		return m_usr;
	}

	void Function::setUSR(const std::string& usr) {
		m_usr = usr;
	}

	const std::string& Function::getName() const {
		return m_name;
	}

	void Function::setName(const std::string& name) {
		m_name = name;
	}

	const std::vector<Parameter>& Function::getParameters() const {
		return m_parameters;
	}
}