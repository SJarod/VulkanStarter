#include <glad/gl.h>

#include "demo_renderer_multidraw.hpp"

#include "renderer_multidraw.hpp"

DemoRendererMultiDraw::DemoRendererMultiDraw()
{
	scene = new Scene(*(new RendererMultiDraw("multidraw")));
}

DemoRendererMultiDraw::~DemoRendererMultiDraw()
{
	delete scene;
}

void DemoRendererMultiDraw::display()
{
	scene->UpdateAndRender();
}