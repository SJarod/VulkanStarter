#pragma once

#include "demo.hpp"
#include "renderer_interface.hpp"

#include "scene.hpp"

class DemoRendererBasic : public Demo
{
private:
    Scene* scene;

public:
    ~DemoRendererBasic() override;
    const char* name() override { return "Renderer basic"; };
    void display() override;
};

class RendererBasic : public RendererInterface
{
public:
    ~RendererBasic() override;

    // Les objets statiques ne bougent pas est sont passé une seul fois au renderer
    void SetStaticObjects(const std::vector<Object>& staticObjects) override;

    // Fonction qui rends à la fois les objets statiques et les objets dynamiques
    void RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights) override;

    GPUMesh* CreateMesh(const Mesh& mesh) override;
    GPUMaterial* CreateMaterial(const Material& material) override;
    GPUTexture* CreateTexture(const Texture& texture) override;
};