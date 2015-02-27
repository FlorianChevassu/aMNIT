/*
 * ModelItem.cpp
 *
 *  Created on: 18 aout 2014
 *      Author: chevassu
 */

#include "cppming/model/ModelItem.h"

using namespace cppming::model;


std::vector <std::shared_ptr<ModelItem>> ModelItem::getSubItems() {
	return m_subItems;
}

std::ostream& operator<<(std::ostream& out, const ModelItem& m) {
	m.print(out);
	return out;
}
