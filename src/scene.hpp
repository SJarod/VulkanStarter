#pragma once

#include <memory>

#include "renderer_interface.hpp"

class Scene
{
public:
    Scene(RendererInterface& renderer); // Chargement de la scène ici
    ~Scene();

    // Rendre la scène à l'aide du renderer
    // Faire bouger aléatoirement les objets dynamiques
    void UpdateAndRender();

private:
    RendererInterface& renderer;

    std::vector<Object> staticObjects;
    std::vector<Object> dynamicObjects;

    std::vector<Light> lights;

    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::unique_ptr<Texture>> textures;
};