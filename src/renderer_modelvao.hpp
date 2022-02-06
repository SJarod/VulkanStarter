#pragma once

#include "renderer_interface.hpp"

struct GPUMeshMultiDraw : GPUMesh
{
    int startIndex;
};

struct GPUTextureMultiDraw : GPUTexture
{
    GLuint data;
};

struct GPUMaterialMultiDraw : GPUMaterial
{
};

class RendererModelVAO : public RendererInterface
{
private:
    GLuint program;
    GLuint VAO;
    GLuint VBO, matricesVBO;

    std::vector<Object> staticObjects;

public:
    RendererModelVAO(const char* shader);
    ~RendererModelVAO() override;

    // Les objets statiques ne bougent pas est sont passé une seul fois au renderer
    void SetStaticObjects(const std::vector<Object>& staticObjects) override;

    // Fonction qui rends à la fois les objets statiques et les objets dynamiques
    void RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights) override;

    void loadShader(const char* shader);
    void createVAO();
    void createModelVAO();

    //create gpu version of mesh, material and texture (VAO, VBO, EBO, ...)
    GPUMesh* CreateMesh(const Mesh& mesh) override;
    void CreateMeshes(std::vector<std::unique_ptr<Mesh>>& meshes) override;
    GPUMaterial* CreateMaterial(const Material& material) override;
    GPUTexture* CreateTexture(const Texture& texture) override;
};