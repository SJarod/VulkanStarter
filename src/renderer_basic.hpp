#pragma once

#include "renderer_interface.hpp"

struct GPUMeshBasic : GPUMesh
{
    GLuint VBO;
    GLuint VAO;

    ~GPUMeshBasic()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
};

struct GPUTextureBasic : GPUTexture
{
    GLuint data;
};

struct GPUMaterialBasic : GPUMaterial
{
};

class RendererBasic : public RendererInterface
{
private:
    GLuint program = 0;

    std::vector<Object> staticObjects;

public:
    RendererBasic(const char* shader);
    ~RendererBasic() override;

    // Les objets statiques ne bougent pas est sont pass� une seul fois au renderer
    void SetStaticObjects(const std::vector<Object>& staticObjects) override;

    // Fonction qui rends � la fois les objets statiques et les objets dynamiques
    void RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights) override;

    void loadShader(const char* shader);

    //create gpu version of mesh, material and texture (VAO, VBO, EBO, ...)
    GPUMesh* CreateMesh(const Mesh& mesh) override;
    void CreateMeshes(std::vector<std::unique_ptr<Mesh>>& meshes) override;
    GPUMaterial* CreateMaterial(const Material& material) override;
    GPUTexture* CreateTexture(const Texture& texture) override;
};