#include <string>
#include <algorithm>
#include <iostream>

#include "CMG/frontends/cpp/Frontend.h"

#include "templateEngine/templateEngine.h"


#include <boost/filesystem/fstream.hpp>
#include <chaiscript/dispatchkit/bootstrap_stl.hpp>

int main() {
	std::unique_ptr<CMG::Frontend, decltype(&CMG::destroyFrontend)> f(CMG::getFrontend(), &CMG::destroyFrontend);
	f->addFolder("/home/florian/dev/MNI/workspace/test");
	f->run();

	CMG::Model& model = f->getModel();

	const CMG::Namespace& ns = *model.getGlobalNamespace();


	mni::TemplateEngine te;
	te.setTemplatePath(boost::filesystem::path("/home/florian/dev/MNI/workspace/mni/templates/Matlab/cpp"));
	//std::list<mni::Node> nodes = te.compile("namespace.mustache");
	te.registerContext<mni::ModelContext>();

	//get model item from model context.
	te.registerFunction(&mni::ModelContext::getClass, "getClass");
	te.registerFunction(&mni::ModelContext::getFunction, "getFunction");
	te.registerFunction(&mni::ModelContext::getMethod, "getMethod");
	te.registerFunction(&mni::ModelContext::getNamespace, "getNamespace");
	te.registerFunction(&mni::ModelContext::getParameter, "getParameter");
	te.registerFunction(&mni::ModelContext::getType, "getType");

	//model items handling
	te.getScriptEngine().add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CMG::Class> >("ClassVector"));
	te.getScriptEngine().add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CMG::Function> >("FunctionVector"));
	te.getScriptEngine().add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CMG::Method> >("MethodVector"));
	te.getScriptEngine().add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CMG::Namespace> >("NamespaceVector"));
	te.getScriptEngine().add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CMG::Parameter> >("ParameterVector"));
	te.getScriptEngine().add(chaiscript::bootstrap::standard_library::vector_type<std::vector<CMG::Type> >("TypeVector"));


	te.registerFunction(&CMG::Function::getParameters, "getParameters");
	te.registerFunction(&CMG::Method::getParameters, "getParameters");


	te.registerFunction(&CMG::Parameter::getName, "getName");



	std::list<mni::Node> nodes = te.compile("main.cpp.mustache");

	//boost::filesystem::ofstream result("/home/florian/dev/MNI/workspace/mni/templates/Matlab/cpp/main.cpp");

	//te.render<mni::ModelContext>(mni::ModelContext(ns), result, nodes);
	te.render<mni::ModelContext>(mni::ModelContext(ns), std::cout, nodes);


	return 0;
}