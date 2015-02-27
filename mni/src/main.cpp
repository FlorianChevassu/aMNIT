#include <string>
#include <algorithm>
#include <iostream>

#include "CMG/frontends/cpp/Frontend.h"

#include "templateEngine/templateEngine.h"

#include "CMG/model/Namespace.h"
#include "model/model.h"

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
	std::list<mni::Node> nodes = te.compile("main.cpp.mustache");

	te.render<mni::ModelContext>(mni::ModelContext(ns), std::cout, nodes);


	return 0;
}