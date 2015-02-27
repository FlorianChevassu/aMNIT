/*
* Namespace.cpp
*
*  Created on: 18 août 2014
*      Author: chevassu
*/

#include "cppming/model/Namespace.h"
#include "cppming/model/Model.h"
#include "cppming/model/Class.h"
#include "cppming/model/Function.h"

namespace cppming {
	namespace model {

		IMPLEMENT_GET_METHOD(Namespace, Namespace
		)
		IMPLEMENT_GET_METHOD(Namespace, Class
		)
		IMPLEMENT_GET_METHOD(Namespace, Function
		)

		void Namespace::print(std::ostream & out) const {
			out << "Namespace " << m_name << std::endl;

			for(auto& m : m_subItems) {
				out << *m << std::endl;
			}
		}
	}
}
