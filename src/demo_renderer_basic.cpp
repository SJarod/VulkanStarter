#include <glad/gl.h>

#include "demo_renderer_basic.hpp"

#include "renderer_basic.hpp"

DemoRendererBasic::DemoRendererBasic()
{
	scene = new Scene(*(new RendererBasic("basic")));
}

DemoRendererBasic::~DemoRendererBasic()
{
	delete scene;
}

void DemoRendererBasic::display()
{
	scene->UpdateAndRender();
}