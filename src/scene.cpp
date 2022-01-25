#include "scene.hpp"

Scene::Scene(RendererInterface& renderer)
	: renderer(renderer)
{
}

Scene::~Scene()
{
	delete& renderer;
}

void Scene::UpdateAndRender()
{
}