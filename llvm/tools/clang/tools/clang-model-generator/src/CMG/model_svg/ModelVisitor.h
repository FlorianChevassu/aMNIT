/*
 * Model.h
 *
 *  Created on: 14 août 2014
 *      Author: chevassu
 */

#ifndef MODEL_VISITOR_H_
#define MODEL_VISITOR_H_

#include <map>
#include <memory>
#include <vector>
#include <algorithm>

#include "cppming/model/Model.h"

namespace cppming {
	namespace model {

		class ModelVisitor {
		public:
			ModelVisitor() {
			}

			virtual ~ModelVisitor() {
			}

			virtual void visit(Model& model) {
				for(auto item : m_subItems) {
					visitItem(item);
				}
			}

			virtual void visitItem(ModelItem& modelItem) {
				switch(modelItem.getType()) {
					case eNamespace:
						visitNamespace(modelItem);
					case eClass:
						visitClass(modelItem);
					case eFunction:
						visitFunction(modelItem);
					case eMethod:
						visitMethod(modelItem);
					case eParameter:
						visitParameter(modelItem);
						//case eType:
						//visitType(modelItem);
				}

				for(auto item : modelItem.getSubItems()) {
					visitItem(item);
				}
			}

			virtual void visitNamespace(const Namespace& ns) = 0;

			virtual void visitClass(const Class& ns) = 0;

			virtual void visitFunction(const Function& ns) = 0;

			virtual void visitMethod(const Method& ns) = 0;

			virtual void visitParameter(const Parameter& ns) = 0;
			//virtual void visitType(const Type& ns) = 0;
		};

	} /* namespace model */
} /* namespace cppming */

#endif /* MODEL_H_ */
