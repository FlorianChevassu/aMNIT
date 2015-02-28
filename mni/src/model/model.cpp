#include "model.h"

#include <sstream>
#include <algorithm>

namespace mni {

	ModelContext::ModelContext(const CMG::Namespace& val, const ModelContext* parent)
			: m_namespace(&val), m_contextType(NAMESPACE), m_parentContext(parent) {
	}

	ModelContext::ModelContext(const CMG::Class& val, const ModelContext* parent)
			: m_class(&val), m_contextType(CLASS), m_parentContext(parent) {
	}

	ModelContext::ModelContext(const CMG::Method& val, const ModelContext* parent)
			: m_method(&val), m_contextType(METHOD), m_parentContext(parent) {
	}

	ModelContext::ModelContext(const CMG::Parameter& val, const ModelContext* parent)
			: m_parameter(&val), m_contextType(PARAMETER), m_parentContext(parent) {
	}

	ModelContext::ModelContext(const CMG::Type& val, const ModelContext* parent)
			: m_type(&val), m_contextType(TYPE), m_parentContext(parent) {
	}

	std::string ModelContext::getValue(const std::string& variableName) const {
		switch(m_contextType) {
			case NAMESPACE:
				if(variableName.compare("name") == 0) {
					return m_namespace->getName();
				} else if(variableName.compare("USR") == 0) {
					return m_namespace->getUSR();
				}
				break;
			case CLASS:
				if(variableName.compare("name") == 0) {
					return m_class->getName();
				} else if(variableName.compare("fullName") == 0) {
					std::list<std::string> nss;
					const ModelContext* curCtx = getParentContext();
					while(curCtx != nullptr && curCtx->m_contextType == NAMESPACE) {
						nss.push_back(curCtx->m_namespace->getName());
						curCtx = curCtx->getParentContext();
					}
					//remove the global namespace
					nss.pop_back();
					std::stringstream ss;
					std::for_each(nss.rbegin(), nss.rend(), [&](auto& s) {
						ss << s << "::";
					});
					ss << m_class->getName();
					return ss.str();
				} else if(variableName.compare("USR") == 0) {
					return m_class->getUSR();
				}
				break;
			case METHOD:
				if(variableName.compare("name") == 0) {
					return m_method->getName();
				} else if(variableName.compare("returnType") == 0) {
					return m_method->getReturnType().getName();
				} else if(variableName.compare("USR") == 0) {
					return m_method->getUSR();
				}
				break;
			case PARAMETER:
				if(variableName.compare("name") == 0) {
					return m_parameter->getName();
				} else if(variableName.compare("type") == 0) {
					return m_parameter->getType().getName();
				} else if(variableName.compare("USR") == 0) {
					return m_parameter->getUSR();
				}
				break;
			case TYPE:
				if(variableName.compare("name") == 0) {
					return m_type->getName();
				}
				break;
		}
		throw std::exception();
	}


	std::list<ModelContext>  ModelContext::getSectionItems(const std::string& variableName) const {
		std::list<ModelContext> res;
		switch(m_contextType) {
			case NAMESPACE:
				if(variableName.compare("namespaces") == 0) {
					std::for_each(m_namespace->getNamespaces().begin(), m_namespace->getNamespaces().end(), [&](const CMG::Namespace& ns) {
						res.emplace_back(ns, this);
					});
				} else if(variableName.compare("classes") == 0) {
					std::for_each(m_namespace->getClasses().begin(), m_namespace->getClasses().end(), [&](const CMG::Class& c) {
						res.emplace_back(c, this);
					});
				}
				break;
			case CLASS:
				if(variableName.compare("methods") == 0) {
					std::for_each(m_class->getMethods().begin(), m_class->getMethods().end(), [&](const CMG::Method& m) {
						res.emplace_back(m, this);
					});
				}
				break;
			case METHOD:
				if(variableName.compare("parameters") == 0) {
					if(!m_method->getParameters().empty()) {
						std::for_each(m_method->getParameters().begin(), m_method->getParameters().end(), [&](const CMG::Parameter& p) {
							res.emplace_back(p, this);
						});
					}
				}
				break;
			case PARAMETER:
			case TYPE:
				break;
		}
		return res;
	}


	const ModelContext* ModelContext::getParentContext() const {
		return m_parentContext;
	}
}