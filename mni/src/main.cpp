#include <string>
#include <algorithm>
#include <iostream>

#include "CMG/frontends/cpp/Frontend.h"

#include "templateEngine/templateEngine.h"


#include <boost/filesystem/fstream.hpp>

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

	//boost::filesystem::ofstream result("/home/florian/dev/MNI/workspace/mni/templates/Matlab/cpp/main.cpp");

	//te.render<mni::ModelContext>(mni::ModelContext(ns), result, nodes);
	te.render<mni::ModelContext>(mni::ModelContext(ns), std::cout, nodes);


	return 0;
}