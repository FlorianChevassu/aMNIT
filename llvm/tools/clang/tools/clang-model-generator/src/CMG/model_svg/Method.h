/*
 * Method.h
 *
 *  Created on: 14 août 2014
 *      Author: chevassu
 */

#ifndef METHOD_H_
#define METHOD_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>


#include "cppming/model/ModelItem.h"
#include "cppming/model/AccessSpecifier.h"
#include "cppming/model/Parameter.h"

namespace cppming {
	namespace model {

		class Model;

		class Method : public ModelItem {
		public:
			typedef std::shared_ptr <Method> Ptr;

			virtual ~Method();

			Method(Model& model, const std::string& name, const std::string& USR);

			DECLARE_GET_METHOD(Parameter)


			virtual void print(std::ostream& out) const;


			void setAccessSpecifier(AccessSpecifier as) {
				m_accessSpecifier = as;
			}

			void setStatic(bool val) {
				m_isStatic = val;
			}

			bool isStatic() {
				return m_isStatic;
			}

			void setConst(bool val) {
				m_isConst = val;
			}

			bool isConst() {
				return m_isConst;
			}

			virtual eModelItem getType() {
				return eModelItem::eMethod;
			}


		private:
			std::string m_name;

			bool m_isFinal;
			bool m_isStatic;
			bool m_isConst;
			bool m_isPure;

			AccessSpecifier m_accessSpecifier;
		};

	} /* namespace model */
} /* namespace cppming */

#endif /* METHOD_H_ */
