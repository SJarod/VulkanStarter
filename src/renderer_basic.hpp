#pragma once

#include "renderer_interface.hpp"

struct GPUMeshBasic : GPUMesh
{
    GLuint VBO, EBO;
    GLuint VAO;

    ~GPUMeshBasic()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};

struct GPUTextureBasic : GPUTexture
{
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

    // Les objets statiques ne bougent pas est sont passé une seul fois au renderer
    void SetStaticObjects(const std::vector<Object>& staticObjects) override;

    // Fonction qui rends à la fois les objets statiques et les objets dynamiques
    void RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights) override;

    //create gpu version of mesh, material and texture (VAO, VBO, EBO, ...)
    GPUMesh* CreateMesh(const Mesh& mesh) override;
    GPUMaterial* CreateMaterial(const Material& material) override;
    GPUTexture* CreateTexture(const Texture& texture) override;
};