/*
 * Method.cpp
 *
 *  Created on: 14 aout 2014
 *      Author: chevassu
 */

#include "cppming/model/Method.h"
#include "cppming/model/Model.h"

namespace cppming {
	namespace model {

		IMPLEMENT_GET_METHOD(Method, Parameter
		)


		Method::~Method() {
			// TODO Auto-generated destructor stub
		}

		Method::Method(Model& model, const std::string& name, const std::string& USR) : ModelItem(model, USR),
																						m_name(name),
																						m_isFinal(false),
																						m_isStatic(false),
																						m_isConst(false),
																						m_isPure(false) {
		}

		void Method::print(std::ostream & out) const {
			out << "Method : " << std::endl;
			out << "m_name : " << m_name << std::endl;
			out << "m_isFinal : " << m_isFinal << std::endl;
			out << "m_isStatic : " << m_isStatic << std::endl;
			out << "m_isConst : " << m_isConst << std::endl;
			out << "m_isPure : " << m_isPure << std::endl;

			for(auto& p : m_subItems) {
				out << *p << std::endl;
			}
		}

	} /* namespace model */
} /* namespace cppming */
