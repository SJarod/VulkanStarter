#include <imgui.h>

#include "maths.hpp"

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
	Part part = {
		meshes.back().get(),
		nullptr,
		m4::translateMatrix({0.f, 0.f, -1.f})
	};

	//simple triangle
	Mesh triangle = {
		//vertices
		{ { { -0.5f, -0.5f, 0.f }, { 0.f, 0.f, 1.f }, { 0.f, 0.f } },
		  { { 0.5f, -0.5f, 0.f }, { 0.f, 0.f, 1.f }, { 1.f, 0.f } },
		  { { 0.f, 0.5f, 0.f }, { 0.f, 0.f, 1.f }, { 0.f, 1.f } } },

		  //indices
		  { 0, 1, 2 },

		  //gpu mesh
		  renderer.CreateMesh(triangle)
	};

	meshes.push_back(std::make_unique<Mesh>(triangle));

	Part part2 = {
		meshes.back().get(),
		nullptr,
		mat4::identity
	};

	//objects
	staticObjects.push_back({ { part, part2 } });
	renderer.SetStaticObjects(staticObjects);
}

Scene::~Scene()
{
	for (int i = 0; i < meshes.size(); ++i)
		delete meshes[i]->gpu;

	delete& renderer;
}

void Scene::UpdateAndRender()
{
	// Setup a perspective projection matrix
	static float fovY = 90.f;
	static float aspect = 16.f / 9.f;
	mat4 perspective = m4::perspective(fovY, aspect, 0.1f, 1000.f);

	// Setup camera position
	static vec3 camPos = { 0.f, 0.f, -1.f };
	ImGui::DragFloat3("camera position", camPos.e, 0.01f);
	static float pitch = 0.f;
	ImGui::DragFloat("pitch", &pitch, 0.1f);
	static float yaw = 0.f;
	ImGui::DragFloat("yaw", &yaw, 0.1f);
	mat4 view = m4::rotateXMatrix(pitch) * m4::rotateYMatrix(yaw) * m4::translateMatrix(camPos);

	renderer.RenderAll(perspective, view, dynamicObjects, lights);
}