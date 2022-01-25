#include "demo_renderer_basic.hpp"

DemoRendererBasic::DemoRendererBasic()
{
	scene = new Scene(*(new RendererBasic()));
}

DemoRendererBasic::~DemoRendererBasic()
{
	delete scene;
}

void DemoRendererBasic::display()
{
	if (!scene)
		return;

	scene->UpdateAndRender();
}

RendererBasic::~RendererBasic()
{
}

void RendererBasic::SetStaticObjects(const std::vector<Object>& staticObjects)
{
}

void RendererBasic::RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights)
{
}

GPUMesh* RendererBasic::CreateMesh(const Mesh& mesh)
{
	return nullptr;
}

GPUMaterial* RendererBasic::CreateMaterial(const Material& material)
{
	return nullptr;
}

GPUTexture* RendererBasic::CreateTexture(const Texture& texture)
{
	return nullptr;
}