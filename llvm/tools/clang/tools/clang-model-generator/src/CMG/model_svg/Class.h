/*
 * Class.h
 *
 *  Created on: 14 août 2014
 *      Author: chevassu
 */

#ifndef CLASS_H_
#define CLASS_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cppming/model/ModelItem.h"
#include "cppming/model/Method.h"
#include "cppming/model/AccessSpecifier.h"

namespace cppming {
	namespace model {

		class Model;

		class Class : public ModelItem {
		public:
			typedef std::shared_ptr <Class> Ptr;

			Class(Model& model, const std::string& name, const std::string& USR);

			virtual ~Class();

			DECLARE_GET_METHOD(Method)

			void setAccessSpecifier(AccessSpecifier as) {
				m_accessSpecifier = as;
			}


			virtual void print(std::ostream& out) const;

			virtual eModelItem getType() {
				return eModelItem::eClass;
			}

			virtual const char* getRawName() {
				return m_name.c_str();
			}

		private:
			std::string m_name;

			bool m_isFinal;
			AccessSpecifier m_accessSpecifier;
		};

	} /* namespace model */
} /* namespace cppming */

#endif /* CLASS_H_ */
