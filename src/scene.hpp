#pragma once

#include <memory>

#include "renderer_interface.hpp"

class Scene
{
public:
    Scene(RendererInterface& renderer); // Chargement de la sc�ne ici
    ~Scene();

    // Rendre la sc�ne � l'aide du renderer
    // Faire bouger al�atoirement les objets dynamiques
    void UpdateAndRender();

private:
    RendererInterface& renderer;

    std::vector<Object> staticObjects;
    std::vector<Object> dynamicObjects;

    std::vector<Light> lights;

    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::unique_ptr<Texture>> textures;
};