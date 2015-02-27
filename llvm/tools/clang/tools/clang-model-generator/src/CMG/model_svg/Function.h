/*
 * Function.h
 *
 *  Created on: 14 août 2014
 *      Author: chevassu
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <memory>


#include "cppming/model/ModelItem.h"

namespace cppming {
	namespace model {

		class Function : public ModelItem {
		public:
			typedef std::shared_ptr <Function> Ptr;

			Function(Model& model, const std::string& name, const std::string& USR)
					: ModelItem(model, USR), m_name(name) {
			}

			virtual ~Function() {
			}


			virtual void print(std::ostream& out) const;


			virtual eModelItem getType() {
				return eModelItem::eFunction;
			}


		private:
			std::string m_name;
		};

	} /* namespace model */
} /* namespace cppming */

#endif /* FUNCTION_H_ */
