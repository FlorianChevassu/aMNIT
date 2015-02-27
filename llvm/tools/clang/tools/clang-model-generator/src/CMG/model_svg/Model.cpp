/*
 * Model.cpp
 *
 *  Created on: 14 août 2014
 *      Author: chevassu
 */

#include "cppming/model/Model.h"
#include "cppming/model/Namespace.h"
#include "cppming/model/Class.h"

#include <iostream>

namespace cppming {
	namespace model {

		IMPLEMENT_GET_METHOD(Model, Namespace
		)
		IMPLEMENT_GET_METHOD(Model, Class
		)

	}
}
