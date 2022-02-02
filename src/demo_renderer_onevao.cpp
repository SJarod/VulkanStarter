#include <glad/gl.h>

#include "demo_renderer_onevao.hpp"

#include "renderer_onevao.hpp"

DemoRendererOneVao::DemoRendererOneVao()
{
	scene = new Scene(*(new RendererOneVao("basic")));
}

DemoRendererOneVao::~DemoRendererOneVao()
{
	delete scene;
}

void DemoRendererOneVao::display()
{
	scene->UpdateAndRender();
}