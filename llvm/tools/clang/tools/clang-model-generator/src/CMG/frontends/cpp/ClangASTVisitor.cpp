#include "CMG/frontends/cpp/ClangASTVisitor.h"


namespace CMG {

	ClangASTVisitor::ClangASTVisitor(clang::SourceManager& sourceMgr,
			CMG::Model& m) : m_sourceManager(&sourceMgr),
							 m_model(m), m_currentFileSourceLocationSet(false) {
	}

	/*
	Visit, create and add namespaces to the model.
	*/
	bool ClangASTVisitor::VisitNamespaceDecl(clang::NamespaceDecl* ns) {
		if(!ns->isOriginalNamespace())
			return VisitNamespaceDecl(ns->getOriginalNamespace());

		std::string nsName = ns->getDeclName().getAsString();
		std::string nsUSR = ClangUtils::generateUSRForDecl(ns);
		std::string USR;

		clang::DeclContext* parent = ns->getParent();
		if(parent->isNamespace()) {
			clang::NamespaceDecl* nsParent = llvm::dyn_cast<clang::NamespaceDecl>(parent);
			USR = ClangUtils::generateUSRForDecl(nsParent);

			if(m_model.hasNamespace(USR)) {
				m_model.getNamespace(USR)->addNamespace(nsUSR)->setName(nsName);
			}
			else {
				//throw or create on the fly...
			}
		}
		else if(!m_model.hasNamespace(nsUSR)) {
			m_model.getGlobalNamespace()->addNamespace(nsUSR)->setName(nsName);
		}
		return true;
	}

	bool ClangASTVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl* c) {
		//Todo: faire une seule fonction pour les structures et les classes
		if(c->isClass()) {
			std::string className = c->getNameAsString();
			std::string classUSR = ClangUtils::generateUSRForDecl(c);
			std::string USR;

			clang::DeclContext* parent = c->getParent();
			CMG::Namespace* theNamespace;
			if(parent->isNamespace()) {
				clang::NamespaceDecl* ns = llvm::dyn_cast<clang::NamespaceDecl>(parent);
				USR = ClangUtils::generateUSRForDecl(ns);

				theNamespace = m_model.getNamespace(USR);
			}
			else {
				theNamespace = m_model.getGlobalNamespace();
			}

			CMG::Class* theClass = theNamespace->addClass(classUSR);
			theClass->setName(className);

			/*
			Retrieve the access specifier for the class
			*/
			//TODO : Je vois pas à quoi ca correspond ??
			/*clang::AccessSpecifier accSpec = c->getAccess();
			switch (accSpec){
			case clang::AS_public:
			theClass->setAccessSpecifier(CMG::AS_public);
			break;
			case clang::AS_protected:
			theClass->setAccessSpecifier(CMG::AS_protected);
			break;
			case clang::AS_private:
			theClass->setAccessSpecifier(CMG::AS_private);
			break;
			case clang::AS_none:
			//todo throw ?
			break;
			}*/
		}
		return true;
	}

	bool ClangASTVisitor::VisitCXXConstructorDecl(clang::CXXConstructorDecl* c) {
		clang::DeclContext* parent = c->getParent();
		std::string ctorUSR = ClangUtils::generateUSRForDecl(c);

		std::string classUSR;

		CMG::Class* theClass;
		CMG::Method* theCtor;

		clang::CXXRecordDecl* parentRecordDecl = llvm::dyn_cast<clang::CXXRecordDecl>(parent);
		classUSR = ClangUtils::generateUSRForDecl(parentRecordDecl);

		theClass = m_model.getClass(classUSR);
		theCtor = theClass->addMethod(ctorUSR);
		theCtor->setAccessSpecifier(ClangUtils::getAccessSpecifier(c));
		theCtor->setConstructor(true);

		return true;
	}

	bool ClangASTVisitor::VisitCXXMethodDecl(clang::CXXMethodDecl* c) {
		clang::DeclContext* parent = c->getParent();

		std::string methodName = c->getNameAsString();
		std::string methodUSR = ClangUtils::generateUSRForDecl(c);
		std::string classUSR;

		CMG::Class* theClass;
		CMG::Method* theMethod;
		if(parent->isRecord()) {
			clang::CXXRecordDecl* parentRecordDecl = llvm::dyn_cast<clang::CXXRecordDecl>(parent);
			classUSR = ClangUtils::generateUSRForDecl(parentRecordDecl);

			theClass = m_model.getClass(classUSR);
			theMethod = theClass->addMethod(methodUSR);
			theMethod->setName(methodName);
		}
		else {
			//TODO error
		}


		theMethod->setAccessSpecifier(ClangUtils::getAccessSpecifier(c));
		theMethod->setConst(c->isConst());
		theMethod->setStatic(c->isStatic());


		CMG::Type& theReturnType = theMethod->getReturnType();
		theReturnType.setName(c->getReturnType().getUnqualifiedType().getAsString());
		theReturnType.setConst(c->getReturnType().isConstQualified());
		theReturnType.setPointer(c->getReturnType().getTypePtr()->isPointerType());
		theReturnType.setReference(c->getReturnType().getTypePtr()->isReferenceType());
		if(theReturnType.isReference()) {
			theReturnType.setConst(c->getReturnType().getTypePtr()->getPointeeType().isConstQualified());
		}
		else {
			theReturnType.setConst(c->getReturnType().isConstQualified());
		}

		return true;
	}

	bool ClangASTVisitor::VisitFunctionDecl(clang::FunctionDecl* c) {
		if(!c->isCXXClassMember()) {
			clang::DeclContext* parent = c->getParent();

			std::string fctName = c->getNameAsString();
			std::string fctUSR = ClangUtils::generateUSRForDecl(c);

			CMG::Namespace* theNamespace;
			CMG::Function* theFunction;
			if(parent->isNamespace()) {
				theNamespace = m_model.getNamespace(ClangUtils::generateUSRForDecl(llvm::dyn_cast<clang::Decl>(parent)));
			}
			else {
				theNamespace = m_model.getGlobalNamespace();
			}


			theFunction = theNamespace->addFunction(fctUSR);
			CMG::Type& theReturnType = theFunction->getReturnType();
			theReturnType.setName(c->getReturnType().getUnqualifiedType().getAsString());
			theReturnType.setConst(c->getReturnType().isConstQualified());
			theReturnType.setPointer(c->getReturnType().getTypePtr()->isPointerType());
			theReturnType.setReference(c->getReturnType().getTypePtr()->isReferenceType());
			if(theReturnType.isReference()) {
				theReturnType.setConst(c->getReturnType().getTypePtr()->getPointeeType().isConstQualified());
			}
			else {
				theReturnType.setConst(c->getReturnType().isConstQualified());
			}
		}
		return true;
	}

	bool ClangASTVisitor::VisitParmVarDecl(clang::ParmVarDecl* d) {
		clang::DeclContext* parent = d->getParentFunctionOrMethod();
		CMG::Parameter* theParameter;
		if(parent->isFunctionOrMethod()) {//TODO inutile non ?
			clang::FunctionDecl* func = llvm::dyn_cast<clang::FunctionDecl>(parent);

			CMG::Method* methodPtr = m_model.getMethod(ClangUtils::generateUSRForDecl(func));

			if(methodPtr != nullptr) {
				theParameter = methodPtr->addParameter(ClangUtils::generateUSRForDecl(d));
				theParameter->setName(d->getNameAsString());

				CMG::Type& theType = theParameter->getType();

				theType.setName(d->getOriginalType().getUnqualifiedType().getAsString());
				theType.setConst(d->getType().isConstQualified());
				theType.setPointer(d->getType().getTypePtr()->isPointerType());
				theType.setReference(d->getType().getTypePtr()->isReferenceType());
				if(theType.isReference()) {
					theType.setConst(d->getType().getTypePtr()->getPointeeType().isConstQualified());
				}
				else {
					theType.setConst(d->getType().isConstQualified());
				}
			}
			else {
				//TODO throw
			}
		}
		return true;
	}

	bool ClangASTVisitor::VisitDecl(clang::Decl* d) {
		if(!m_currentFileSourceLocationSet) {
			m_currentFileSourceLocation = d->getSourceRange().getBegin();
			m_currentFileSourceLocationSet = true;
			return true;
		}

		/*if(m_sourceManager->isWrittenInSameFile(m_currentFileSourceLocation, d->getSourceRange().getBegin())){
		  std::cout << "same file" << std::endl;
		  d->dump();
		  std::cout << std::endl;
		  std::cout << std::endl;
		  std::cout << std::endl;
		  }*/

		return m_sourceManager->isWrittenInSameFile(m_currentFileSourceLocation, d->getSourceRange().getBegin());
	}

}