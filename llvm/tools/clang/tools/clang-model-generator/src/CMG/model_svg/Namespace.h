/*
* Namespace.h
*
*  Created on: 14 août 2014
*      Author: chevassu
*/

#ifndef NAMESPACE_H_
#define NAMESPACE_H_

#include <map>
#include <memory>
#include <vector>


#include "cppming/model/Class.h"
#include "cppming/model/Function.h"
#include "cppming/model/ModelItem.h"

namespace cppming {
	namespace model {

		class Namespace : public ModelItem {
		public:
			typedef std::shared_ptr <Namespace> Ptr;

			Namespace(Model& model, const std::string& name, const std::string& USR)
					: ModelItem(model, USR), m_name(name) {
			}

			const std::string& getName() const {
				return m_name;
			}


			DECLARE_GET_METHOD(Namespace)
			DECLARE_GET_METHOD(Class)
			DECLARE_GET_METHOD(Function)

			virtual void print(std::ostream& out) const;

			virtual eModelItem getType() {
				return eModelItem::eNamespace;
			}

		private:
			std::string m_name;
		};

	} /* namespace model */
} /* namespace cppming */

#endif /* MODEL_H_ */
