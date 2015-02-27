/*
 * Parameter.cpp
 *
 *  Created on: 22 aout 2014
 *      Author: chevassu
 */

#include "cppming/model/Parameter.h"
#include "cppming/model/Model.h"
#include "cppming/model/Class.h"

namespace cppming {
	namespace model {

		Parameter::~Parameter() {
		}

		IMPLEMENT_GET_METHOD(Parameter, Class
		)

		void Parameter::print(std::ostream & out) const {
			out << "Parameter : " << std::endl;
			out << "m_USR : " << m_USR << std::endl;
			out << "m_name : " << m_name << std::endl;
			out << "m_isConst : " << m_isConst << std::endl;
			out << "m_isReference : " << m_isReference << std::endl;
		}

	} /* namespace model */
} /* namespace cppming */


