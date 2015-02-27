#include "CMG/model/Type.h"

namespace CMG {

	Type::Type() {

	}

	Type::~Type() {

	}

	bool Type::isConst() const {
		return m_isConst;
	}

	bool Type::isReference() const {
		return m_isReference;
	}

	bool Type::isPointer() const {
		return m_isPointer;
	}

	/*Type& Type::getUnderlyingType(){
		return *m_underlyingType.get();
	  }*/

	const std::string& Type::getName() const {
		return m_name;
	}

	const char* Type::getRawName() const {
		return m_name.c_str();
	}


	void Type::setConst(bool b) {
		m_isConst = b;
	}

	void Type::setReference(bool b) {
		m_isReference = b;
	}

	void Type::setPointer(bool b) {
		m_isPointer = b;
	}

	void Type::setName(const std::string& s) {
		m_name = s;
	}


}