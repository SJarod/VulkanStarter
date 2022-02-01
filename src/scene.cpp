#include <iostream>
#include <string>
#include <imgui.h>

#include "tiny_obj_loader.h"
#include "maths.hpp"

#include "scene.hpp"

Scene::Scene(RendererInterface& renderer)
	: renderer(renderer)
{
	std::vector<Vertex> fileVertices;
	std::vector<uint> fileIndices;
	loadObj("teapot.obj", fileVertices, fileIndices);

	Mesh fileMesh = {
		fileVertices,
		fileIndices,
		renderer.CreateMesh(fileMesh)
	};

	meshes.push_back(std::make_unique<Mesh>(fileMesh));

	Part filePart = {
		meshes.back().get(),
		nullptr,
		mat4::identity
	};

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
	staticObjects.push_back({ { filePart } });
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
	ImGui::DragFloat("fovY", &fovY, 0.1f);
	static float aspect = 16.f / 9.f;
	mat4 perspective = m4::perspective(fovY, aspect, 0.1f, 1000.f);

	// Setup camera position
	static vec3 camPos = { 0.f, 0.f, 1.f };
	ImGui::DragFloat3("camera position", camPos.e, 0.01f);
	static float pitch = 0.f;
	ImGui::DragFloat("pitch", &pitch, 0.1f);
	static float yaw = 0.f;
	ImGui::DragFloat("yaw", &yaw, 0.1f);
	mat4 view = m4::translateMatrix(-camPos) * m4::rotateXMatrix(pitch) * m4::rotateYMatrix(-yaw);

	renderer.RenderAll(perspective, view, dynamicObjects, lights);
}

void Scene::loadObj(const char* filename, std::vector<Vertex>& vertices, std::vector<uint>& indices) const
{
	std::string Warn;
	std::string Err;
	tinyobj::attrib_t Attrib;
	std::vector<tinyobj::shape_t> Shapes;

	std::string file = filename;
	file = "assets/" + file;

	if (tinyobj::LoadObj(&Attrib, &Shapes, nullptr, &Warn, &Err, file.c_str(), "assets/", true))
		std::cout << "successfully loaded object : " << filename << std::endl;
	else
		std::cout << "could not load object : " << filename << std::endl;

	for (int i = 0; i < Attrib.vertices.size() / 3; ++i)
	{
		vec3 v = { Attrib.vertices[i * 3 + 0], Attrib.vertices[i * 3 + 1], Attrib.vertices[i * 3 + 2] };
		vec3 n = vec3::zero;
		if (!Attrib.normals.empty() && i < Attrib.normals.size() / 3)
			n = { Attrib.normals[i], Attrib.normals[i + 1], Attrib.normals[i + 2] };
		vec2 u = vec2::zero;
		if (!Attrib.texcoords.empty() && i < Attrib.texcoords.size() / 3)
			u = { Attrib.texcoords[i], Attrib.texcoords[i + 1] };

		vertices.push_back({ v, n, u });
	}

	for (tinyobj::shape_t& sh : Shapes)
	{
		for (tinyobj::index_t& ind : sh.mesh.indices)
		{
			indices.push_back(ind.vertex_index);
		}
	}
}