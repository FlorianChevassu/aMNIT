#pragma once

#include <string>


namespace model {
	class Type {
	public:
		Type(const std::string& name, const std::string& USR) : m_name(name), m_USR(USR) {
		}

		~Type() {
		}

		//virtual eModelItem getType(){ return eModelItem::eType;}

	private:
		std::string m_name;
		//Unified Symbol Resolution
		std::string m_USR;
	};
}

