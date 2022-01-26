#include <glad/gl.h>

#include <fstream>
#include <iostream>

#include "renderer_basic.hpp"
#include "memleaks.hpp"

RendererBasic::RendererBasic(const char* shader)
{
	std::string filename = shader;
	filename = "resources/shaders/" + filename;

	//vertex shader
	std::ifstream vsStream(filename + ".vs");
	std::ifstream fsStream(filename + ".fs");

	if (!vsStream.is_open() || !fsStream.is_open())
	{
		std::cout << "could not open shader files : " << filename << std::endl;
		return;
	}

	std::string vs((std::istreambuf_iterator<char>(vsStream)), std::istreambuf_iterator<char>());
	std::string fs((std::istreambuf_iterator<char>(fsStream)), std::istreambuf_iterator<char>());

	const char* vertexShaderSource = vs.c_str();
	const char* fragmentShaderSource = fs.c_str();

	//shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int  success[2];
	char infoLog[2][512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success[0]);

	if (!success[0])
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog[0]);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED : " << filename << ".vs\n" << infoLog[0] << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success[1]);

	if (!success[1])
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog[1]);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED : " << filename << ".fs\n" << infoLog[1] << std::endl;
	}

	if (success[0] && success[1])
	{
		std::cout << "successfully loaded shader files : " << filename << std::endl;
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	vsStream.close();
	fsStream.close();
}

RendererBasic::~RendererBasic()
{
}

void RendererBasic::SetStaticObjects(const std::vector<Object>& staticObjects)
{
	this->staticObjects = staticObjects;
}

void RendererBasic::RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights)
{
	glUseProgram(program);

	for (const Object& obj : staticObjects)
	{
		for (const Part& p : obj.parts)
		{
			glBindVertexArray((static_cast<GPUMeshBasic*>(p.mesh->gpu))->VAO);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)p.mesh->vertices.size());
			glBindVertexArray(0);
		}
	}

	for (const Object& obj : dynamicObjects)
	{
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