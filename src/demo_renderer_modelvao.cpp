#include <glad/gl.h>

#include "demo_renderer_modelvao.hpp"

#include "renderer_modelvao.hpp"

DemoRendererModelVao::DemoRendererModelVao()
{
	scene = new Scene(*(new RendererModelVAO("modelvao")));
}

DemoRendererModelVao::~DemoRendererModelVao()
{
	delete scene;
}

void DemoRendererModelVao::display()
{
	scene->UpdateAndRender();
}