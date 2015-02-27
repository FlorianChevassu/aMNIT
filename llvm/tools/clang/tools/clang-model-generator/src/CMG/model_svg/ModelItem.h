/*
 * ModelItem.h
 *
 *  Created on: 18 aout 2014
 *      Author: chevassu
 */

#ifndef MODELITEM_H_
#define MODELITEM_H_

#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>

//#include "Model.h"

#ifndef IMPLEMENT_GET_METHOD

#define IMPLEMENT_GET_METHOD(Class, Type)\
  std::shared_ptr<Type> Class::get##Type(const std::string& name, const std::string& USR){\
  auto foundVal = std::find_if(std::begin(m_subItems), std::end(m_subItems), \
  [&USR](const ModelItem::Ptr& item){\
    return item->getUSR().compare(USR) == 0; \
  }); \
  std::shared_ptr<Type> ret; \
  if (foundVal == m_subItems.end()){\
    ret = std::make_shared<Type>(m_model, name, USR); \
    m_subItems.push_back(ret); \
    m_model.getItemMap()[USR] = ret; \
  }else{\
    std::shared_ptr<ModelItem> retModelType = *foundVal; \
    ret = std::dynamic_pointer_cast<Type>(retModelType); \
  }\
  return ret; \
}\

#endif //IMPLEMENT_GET_METHOD

#ifndef DECLARE_GET_METHOD

#define DECLARE_GET_METHOD(Type)\
  std::shared_ptr<Type> get##Type(const std::string& name, const std::string& USR);
#endif //DECLARE_GET_METHOD


namespace cppming {
	namespace model {

		class Model;

		enum eModelItem {
			eNamespace,
			eClass,
			eFunction,
			eMethod,
			eParameter,
			eType
		};

		class ModelItem {
		public:
			typedef std::shared_ptr <ModelItem> Ptr;

			ModelItem(Model& model, const std::string& USR) : m_model(model), m_USR(USR) {
			}

			virtual ~ModelItem() {
			}

			const std::string& getUSR() const {
				return m_USR;
			}


			friend std::ostream& operator<<(std::ostream& out, const ModelItem& m) {
				m.print(out);
				return out;
			}

			virtual void print(std::ostream& out) const = 0;

		public:
			virtual eModelItem getType() = 0;

		public:
			std::vector <std::shared_ptr<ModelItem>> getSubItems();

		protected:
			std::vector <std::shared_ptr<ModelItem>> m_subItems;

			Model& m_model;
			std::string m_USR;

		};

	} /* namespace model */
} /* namespace cppming */

#endif /* MODELITEM_H_ */
