/*
 * Class.cpp
 *
 *  Created on: 14 août 2014
 *      Author: chevassu
 */

#include "cppming/model/Class.h"
#include "cppming/model/ModelItem.h"
#include "cppming/model/Model.h"


namespace cppming {
	namespace model {

		Class::~Class() {
			// TODO Auto-generated destructor stub
		}

		Class::Class(Model& model, const std::string& name, const std::string& USR)
				: ModelItem(model, USR), m_name(name) {
		}

		IMPLEMENT_GET_METHOD(Class, Method
		)


		void Class::print(std::ostream & out) const {
			out << "Class " << m_name << std::endl;

			for(auto& m : m_subItems) {
				out << *m << std::endl;
			}
		}

	} /* namespace model */
} /* namespace cppming */
