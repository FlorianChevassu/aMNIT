#include "CMG/model/Method.h"

namespace CMG {

	Method::Method(Model& m, const std::string& usr) : m_model(m), m_usr(usr) {
	}

	Method::~Method() {
	}

	const std::string& Method::getUSR() const {
		return m_usr;
	}

	void Method::setUSR(const std::string& usr) {
		m_usr = usr;
	}

	const std::string& Method::getName() const {
		return m_name;
	}

	void Method::setName(const std::string& name) {
		m_name = name;
	}

	bool Method::isFinal() const {
		return m_isFinal;
	}

	void Method::setFinal(bool f) {
		m_isFinal = f;
	}

	bool Method::isStatic() const {
		return m_isStatic;
	}

	void Method::setStatic(bool f) {
		m_isStatic = f;
	}

	bool Method::isConst() const {
		return m_isConst;
	}

	void Method::setConst(bool f) {
		m_isConst = f;
	}

	bool Method::isPure() const {
		return m_isPure;
	}

	void Method::setPure(bool f) {
		m_isPure = f;
	}

	AccessSpecifier Method::getAccessSpecifier() const {
		return m_accessSpecifier;
	}

	void Method::setAccessSpecifier(AccessSpecifier as) {
		m_accessSpecifier = as;
	}

	const std::list<Parameter>& Method::getParameters() const {
		return m_parameters;
	}
}