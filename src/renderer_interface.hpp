#pragma once

#include <vector>

#include "object.hpp"

class RendererInterface
{
public:
    virtual ~RendererInterface() {}

    // Les objets statiques ne bougent pas est sont passé une seul fois au renderer
    virtual void SetStaticObjects(const std::vector<Object>& staticObjects) = 0;

    // Fonction qui rends à la fois les objets statiques et les objets dynamiques
    virtual void RenderAll(const mat4& proj, const mat4& view, const std::vector<Object>& dynamicObjects, const std::vector<Light>& lights) = 0;

    virtual GPUMesh* CreateMesh(const Mesh& mesh) = 0;
    virtual GPUMaterial* CreateMaterial(const Material& material) = 0;
    virtual GPUTexture* CreateTexture(const Texture& texture) = 0;
};