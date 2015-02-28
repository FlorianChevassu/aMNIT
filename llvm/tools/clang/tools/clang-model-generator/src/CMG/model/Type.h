#pragma once

#include <memory>
#include <string>

#include "API.h"

namespace CMG {
	class Type {
	public:
		Type();

		~Type();

		CMG_API bool isConst() const;

		CMG_API bool isReference() const;

		CMG_API bool isPointer() const;

		CMG_API const std::string& getName() const;

		CMG_API const char* getRawName() const;

		void setConst(bool b);

		void setReference(bool b);

		void setPointer(bool b);

		void setName(const std::string& s);

	private:
		bool m_isConst;
		bool m_isReference;
		bool m_isPointer;
		//std::unique_ptr<Type> m_underlyingType;
		std::string m_name;
	};
}