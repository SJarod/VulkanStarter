#include <glad/gl.h>

#include <fstream>
#include <iostream>

#include "renderer_multidraw.hpp"
#include "memleaks.hpp"

#include "maths.hpp"

RendererMultiDraw::RendererMultiDraw(const char* shader)
{
	loadShader(shader);
}

RendererMultiDraw::~RendererMultiDraw()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void RendererMultiDraw::SetStaticObjects(const std::vector<Object>& staticObjects)
{
	this->staticObjects = staticObjects;
}

void RendererMultiDraw::RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights)
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, matricesVBO);
	int i = 0;
	for (Object& obj : staticObjects)
	{
		for (Part& p : obj.parts)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i++ * sizeof(mat4), sizeof(mat4), p.localMatrix.e);
		}
	}

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "uVP"), 1, GL_FALSE, (view * proj).e);

	glBindVertexArray(VAO);

	for (const Object& obj : staticObjects)
	{
		for (const Part& p : obj.parts)
		{
			if (p.material)
			{
				glBindTexture(GL_TEXTURE_2D, (static_cast<GPUTextureMultiDraw*>(p.material->diffuseTexture->gpu))->data);
				glUniform1i(glGetUniformLocation(program, "uHasTexture"), true);
			}
			else
			{
				glUniform1i(glGetUniformLocation(program, "uHasTexture"), false);
			}

			glUniformMatrix4fv(glGetUniformLocation(program, "uModel"), 1, GL_FALSE, p.localMatrix.e);

			GPUMeshMultiDraw gpuMesh = *static_cast<GPUMeshMultiDraw*>(p.mesh->gpu);
			glDrawArrays(GL_TRIANGLES, gpuMesh.startIndex, gpuMesh.size);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	for (const Object& obj : dynamicObjects)
	{
		for (const Part& p : obj.parts)
		{
			if (p.material)
			{
				glBindTexture(GL_TEXTURE_2D, (static_cast<GPUTextureMultiDraw*>(p.material->diffuseTexture->gpu))->data);
				glUniform1i(glGetUniformLocation(program, "uHasTexture"), true);
			}
			else
			{
				glUniform1i(glGetUniformLocation(program, "uHasTexture"), false);
			}

			glUniformMatrix4fv(glGetUniformLocation(program, "uModel"), 1, GL_FALSE, p.localMatrix.e);

			GPUMeshMultiDraw gpuMesh = *static_cast<GPUMeshMultiDraw*>(p.mesh->gpu);
			glDrawArrays(GL_TRIANGLES, gpuMesh.startIndex, gpuMesh.size);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	glBindVertexArray(0);

	glDisable(GL_DEPTH_TEST);
}

GPUMesh* RendererMultiDraw::CreateMesh(const Mesh& mesh)
{
	return new GPUMeshMultiDraw();
}

GPUMaterial* RendererMultiDraw::CreateMaterial(const Material& material)
{
	return nullptr;
}

GPUTexture* RendererMultiDraw::CreateTexture(const Texture& texture)
{
	GPUTextureMultiDraw* gpu = new GPUTextureMultiDraw();

	glGenTextures(1, &gpu->data);

	glBindTexture(GL_TEXTURE_2D, gpu->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (texture.data)
	{
		GLint bpp = texture.bpp == 1 ? GL_RED : texture.bpp == 2 ? GL_RG : texture.bpp == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, bpp, texture.width, texture.height, 0, bpp, GL_UNSIGNED_BYTE, texture.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return gpu;
}

void RendererMultiDraw::loadShader(const char* shader)
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

void RendererMultiDraw::createVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(vec3)));

	glBindBuffer(GL_ARRAY_BUFFER, matricesVBO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)sizeof(vec4));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)(2 * sizeof(vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)(3 * sizeof(vec4)));

	glBindVertexArray(0);
}

void RendererMultiDraw::CreateMeshes(std::vector<std::unique_ptr<Mesh>>& meshes)
{
	//vertices
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	std::vector<Vertex> vertices;
	int offsetIndex = 0;
	for (auto& m : meshes)
	{
		vertices.insert(vertices.end(), m->vertices.begin(), m->vertices.end());

		m.get()->gpu = CreateMesh(*m.get());
		(static_cast<GPUMeshMultiDraw*>(m.get()->gpu))->startIndex = offsetIndex;
		(static_cast<GPUMeshMultiDraw*>(m.get()->gpu))->size = m->vertices.size();
		offsetIndex += m->vertices.size();
	}
	
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	//model matrices
	glGenBuffers(1, &matricesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, matricesVBO);
	glBufferData(GL_ARRAY_BUFFER, meshes.size() * sizeof(mat4), NULL, GL_STATIC_DRAW);

	createVAO();
}