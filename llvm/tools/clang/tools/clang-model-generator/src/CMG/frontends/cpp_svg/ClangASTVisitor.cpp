#include "cppming/frontends/cpp/ClangASTVisitor.h"


namespace cppming {
	namespace frontends {
		namespace cpp {

			ClangASTVisitor::ClangASTVisitor(clang::SourceManager & sourceMgr, cppming::model::Model & m)
					: m_sourceManager(&sourceMgr), m_model(m), m_currentFileSourceLocationSet(false) {
			}

/*
Visit, create and add namespaces to the model.
*/
			bool ClangASTVisitor::VisitNamespaceDecl(clang::NamespaceDecl * ns) {
				if(!ns->isOriginalNamespace())
					return VisitNamespaceDecl(ns->getOriginalNamespace());

				std::string nsName = ns->getDeclName().getAsString();
				std::string nsUSR = ClangUtils::generateUSRForDecl(ns);

				clang::DeclContext* parent = ns->getParent();
				if(parent->isNamespace()) {
					clang::NamespaceDecl* nsParent = llvm::dyn_cast<clang::NamespaceDecl>(parent);
					cppming::model::Namespace::Ptr parentNamespace =
							std::dynamic_pointer_cast<cppming::model::Namespace>(
									m_model.getItemMap()[ClangUtils::generateUSRForDecl(nsParent)]
							);

					if(parentNamespace)
						parentNamespace->getNamespace(nsName, nsUSR);
				}
				else {
					m_model.getNamespace(nsName, nsUSR);
				}
				return true;
			}

			bool ClangASTVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl * c) {
				//Todo: faire une seule fonction pour les structures et les classes
				if(c->isClass()) {
					std::string className = c->getNameAsString();
					std::string classUSR = ClangUtils::generateUSRForDecl(c);

					clang::DeclContext* parent = c->getParent();
					cppming::model::Class::Ptr theClass;
					if(parent->isNamespace()) {
						clang::NamespaceDecl* ns = llvm::dyn_cast<clang::NamespaceDecl>(parent);

						cppming::model::Namespace::Ptr nsPtr =
								std::dynamic_pointer_cast<cppming::model::Namespace>(
										m_model.getItemMap()[ClangUtils::generateUSRForDecl(ns)]
								);

						theClass = nsPtr->getClass(className, classUSR);
					}
					else {
						theClass = m_model.getClass(className, classUSR);
					}

					/*
					Retrieve the access specifier for the class
					*/
					clang::AccessSpecifier accSpec = c->getAccess();
					switch(accSpec) {
						case clang::AS_public:
							theClass->setAccessSpecifier(cppming::model::AS_public);
							break;
						case clang::AS_protected:
							theClass->setAccessSpecifier(cppming::model::AS_protected);
							break;
						case clang::AS_private:
							theClass->setAccessSpecifier(cppming::model::AS_private);
							break;
						case clang::AS_none:
							//todo throw ?
							break;
					}
				}
				return true;
			}

			bool ClangASTVisitor::VisitFunctionDecl(clang::FunctionDecl * c) {
				//check that it is a Class member
				if(c->isCXXClassMember()) {
					clang::CXXMethodDecl* methodDecl = llvm::dyn_cast<clang::CXXMethodDecl>(c);
					clang::DeclContext* parent = c->getParent();

					std::string methodName = c->getNameAsString();
					std::string methodUSR = ClangUtils::generateUSRForDecl(c);
					std::string classUSR;

					cppming::model::Class::Ptr theClass;
					cppming::model::Method::Ptr theMethod;
					if(parent->isRecord()) {
						clang::CXXRecordDecl* parentRecordDecl = llvm::dyn_cast<clang::CXXRecordDecl>(parent);
						classUSR = ClangUtils::generateUSRForDecl(parentRecordDecl);
						theClass = std::dynamic_pointer_cast<cppming::model::Class>(m_model.getItemMap()[classUSR]);

						theMethod = theClass->getMethod(methodName, methodUSR);
					}
					else {
						//error
					}

					/*
					Retrieve the access specifier for the class
					*/
					clang::AccessSpecifier accSpec = c->getAccess();
					switch(accSpec) {
						case clang::AS_public:
							theMethod->setAccessSpecifier(cppming::model::AS_public);
							break;
						case clang::AS_protected:
							theMethod->setAccessSpecifier(cppming::model::AS_protected);
							break;
						case clang::AS_private:
							theMethod->setAccessSpecifier(cppming::model::AS_private);
							break;
						case clang::AS_none:
							//todo throw ?
							break;
					}

					theMethod->setConst(methodDecl->isConst());
					theMethod->setStatic(methodDecl->isStatic());

					return true;
				}
				else {
					//It is a function
					//std::cout << std::string(ClangUtils::generateUSRForDecl(c)) << std::endl;
				}
				return true;
			}

			bool ClangASTVisitor::VisitParmVarDecl(clang::ParmVarDecl * d) {
				clang::DeclContext* parent = d->getParentFunctionOrMethod();
				cppming::model::Parameter::Ptr theParameter;
				if(parent->isFunctionOrMethod()) {//inutile non ?
					clang::FunctionDecl* func = llvm::dyn_cast<clang::FunctionDecl>(parent);

					cppming::model::Method::Ptr methodPtr =
							std::dynamic_pointer_cast<cppming::model::Method>(
									m_model.getItemMap()[ClangUtils::generateUSRForDecl(func)]
							);

					if(methodPtr.get() != nullptr) {
						theParameter = methodPtr->getParameter(
								d->getOriginalType().getUnqualifiedType().getAsString(),
								ClangUtils::generateUSRForDecl(d));
						theParameter->setConst(d->getType().isConstQualified());
						theParameter->setReference(d->getType().getTypePtr()->isReferenceType());
						if(theParameter->isReference()) {
							theParameter->setConst(d->getType().getTypePtr()->getPointeeType().isConstQualified());
						} else {
							theParameter->setConst(d->getType().isConstQualified());
						}
					}
				}
				return true;
			}

			bool ClangASTVisitor::VisitDecl(clang::Decl * d) {
				if(!m_currentFileSourceLocationSet) {
					m_currentFileSourceLocation = d->getSourceRange().getBegin();
					m_currentFileSourceLocationSet = true;
					return true;
				}

				if(m_sourceManager->isWrittenInSameFile(m_currentFileSourceLocation, d->getSourceRange().getBegin())) {
					std::cout << "same file" << std::endl;
					d->dump();
					std::cout << std::endl;
					std::cout << std::endl;
					std::cout << std::endl;
				}

				return m_sourceManager->isWrittenInSameFile(m_currentFileSourceLocation, d->getSourceRange().getBegin());
			}

		}
	}
}