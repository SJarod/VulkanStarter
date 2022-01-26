#include "scene.hpp"

Scene::Scene(RendererInterface& renderer)
	: renderer(renderer)
{
    //simple quad
    Mesh quad = {
        //vertices
        { { { 0.f, 0.f, 0.f }, { 0.f, 0.f, 1.f }, { 0.f, 0.f } },
          { { 1.f, 0.f, 0.f }, { 0.f, 0.f, 1.f }, { 1.f, 0.f } },
          { { 0.f, 1.f, 0.f }, { 0.f, 0.f, 1.f }, { 0.f, 1.f } },
          { { 1.f, 1.f, 0.f }, { 0.f, 0.f, 1.f }, { 1.f, 1.f } } },

        //indices
        { 0, 1, 2, 1, 2, 3 },

        //gpu mesh
        renderer.CreateMesh(quad)
    };

    meshes.push_back(std::make_unique<Mesh>(quad));

    //parts

    //objects
}

Scene::~Scene()
{
    for (int i = 0; i < meshes.size(); ++i)
        delete meshes[i]->gpu;

	delete &renderer;
}

void Scene::UpdateAndRender()
{
    renderer.RenderAll(mat4::identity, mat4::identity, dynamicObjects, lights);
}