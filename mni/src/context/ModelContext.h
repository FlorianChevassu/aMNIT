#pragma once

#include "CMG/model/Model.h"
#include "CMG/model/Namespace.h"
#include "CMG/model/Class.h"
#include "CMG/model/Method.h"
#include "CMG/model/Parameter.h"
#include "CMG/model/Type.h"


namespace mni {

	class ModelContext {
		union {
			const CMG::Namespace* m_namespace;
			const CMG::Class* m_class;
			const CMG::Method* m_method;
			const CMG::Function* m_function;
			const CMG::Parameter* m_parameter;
			const CMG::Type* m_type;
		};
		enum {
			NAMESPACE,
			CLASS,
			METHOD,
			FUNCTION,
			PARAMETER,
			TYPE
		} m_contextType;

		const ModelContext* m_parentContext;
	public:
		ModelContext(const CMG::Namespace& val, const ModelContext* parent = nullptr);

		ModelContext(const CMG::Class& val, const ModelContext* parent = nullptr);

		ModelContext(const CMG::Method& val, const ModelContext* parent = nullptr);

		ModelContext(const CMG::Function& val, const ModelContext* parent = nullptr);

		ModelContext(const CMG::Parameter& val, const ModelContext* parent = nullptr);

		ModelContext(const CMG::Type& val, const ModelContext* parent = nullptr);

		std::string getValue(const std::string& variableName) const;

		std::list<ModelContext> getSectionItems(const std::string& sectionName) const;

		const ModelContext* getParentContext() const;


		//User defined functions
		const CMG::Namespace& getNamespace() const;

		const CMG::Class& getClass() const;

		const CMG::Method& getMethod() const;

		const CMG::Function& getFunction() const;

		const CMG::Parameter& getParameter() const;

		const CMG::Type& getType() const;
	};
}