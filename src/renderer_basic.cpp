#include <glad/gl.h>

#include "renderer_basic.hpp"

#include "memleaks.hpp"

RendererBasic::RendererBasic(const char* shader)
{

}

RendererBasic::~RendererBasic()
{
}

void RendererBasic::SetStaticObjects(const std::vector<Object>& staticObjects)
{
}

void RendererBasic::RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights)
{
	for (const Object& obj : dynamicObjects)
	{
		glUseProgram(0);

		for (const Part& p : obj.parts)
		{
			glBindVertexArray((static_cast<GPUMeshBasic*>(p.mesh->gpu))->VAO);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)p.mesh->vertices.size());
			glBindVertexArray(0);
		}
	}
}

GPUMesh* RendererBasic::CreateMesh(const Mesh& mesh)
{
	GPUMeshBasic* gpu = new GPUMeshBasic();

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &gpu->VAO);
	glBindVertexArray(gpu->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(vec3)));
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);

	return gpu;
}

GPUMaterial* RendererBasic::CreateMaterial(const Material& material)
{
	return nullptr;
}

GPUTexture* RendererBasic::CreateTexture(const Texture& texture)
{
	return nullptr;
}