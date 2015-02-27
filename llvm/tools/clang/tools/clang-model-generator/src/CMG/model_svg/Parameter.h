/*
 * Parameter.h
 *
 *  Created on: 22 août 2014
 *      Author: chevassu
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <iostream>
#include <memory>
#include <string>


#include "cppming/model/ModelItem.h"

namespace cppming {
	namespace model {

		class Class;

		class Parameter : public ModelItem {
		public:
			typedef std::shared_ptr <Parameter> Ptr;

			virtual ~Parameter();

			Parameter(Model& model, const std::string& name, const std::string& USR)
					: ModelItem(model, USR), m_name(name) {
			}

			DECLARE_GET_METHOD(Class)

			friend std::ostream& operator<<(std::ostream& out, const Parameter& f);

			void setReference(bool val) {
				m_isReference = val;
			}

			bool isReference() {
				return m_isReference;
			}

			void setConst(bool val) {
				m_isConst = val;
			}

			bool isConst() {
				return m_isConst;
			}

			virtual void print(std::ostream& out) const;

			virtual eModelItem getType() {
				return eModelItem::eParameter;
			}


		private:
			std::string m_name;

			bool m_isConst;
			bool m_isReference;
		};


	} /* namespace model */
} /* namespace cppming */

#endif /* PARAMETER_H_ */
