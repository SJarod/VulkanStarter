# TP Opengl like Vulkan
Nous nous appuierons sur ce document de référence fourni par Nvidia : https://developer.nvidia.com/opengl-vulkan

Le but de ce TP est d'arriver à utiliser OpenGL en utilisant le minimum de fonctions possible pour mieux saisir la philosophie de Vulkan.

Le cas d'étude sera une scène 3D avec une liste d'objets statiques et dynamiques.

## Prérequis
Basez-vous sur le template fourni (OpenGL + GLFW + glad) et modifiez la version de glad pour atteindre OpenGL 4.5. C'est dans cette version d'OpenGL qu'ont été intégrées les extensions qui nous intéressent.

On veut la version de gl 4.5, core, avec le loader intégré, à créer ici : https://gen.glad.sh/

## Création d'une scène 3D
La première étape (et non la moindre) est de créer un système de scène qui va nous permettre de représenter les objets 3D dans notre applications.

`objects.hpp`:
```c++
// Base classes to override for each renderer
struct GPUMesh {};
struct GPUTexture {};
struct GPUMaterial {};

// objects.hpp
struct Vertex
{
    float3 position;
    float3 normal;
    float2 uv0;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GPUMesh* gpu;
};

struct Texture
{
    int width;
    int height;
    int bpp;
    void* data; // On va dire qu'on supporte seulement UNSIGNED_BYTE

    GPUTexture* gpu;
};

struct Material
{
    float4 diffuseColor;
    Texture* diffuseTexture;

    GPUMaterial* gpu;
};

struct Light
{
    float4 position; // w = 0 for directionnal light
};

struct Part
{
    Mesh* mesh;
    Material* material;

    mat4 localMatrix;
};

struct Object
{
    std::vector<Part> parts;
};

struct ObjectInstance
{
    float3 position;
    float3 eulerAngles; // Vous pouvez utiliser un quaternion aussi
    float scale;        // Uniform scale pour simplifier
    
    bool dirtyFlag; // true pour signifier qu'il faut recalculer la worldMatrix de toutes ses parts
    std::vector<mat4> worldMatricesPerParts;
};
```

`scene.hpp`:
```c++
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

    std::vector<ObjectInstance> staticObjects;
    std::vector<ObjectInstance> dynamicObjects;
    
    std::vector<Light> lights;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::unique_ptr<Texture>> textures;
};

```

`renderer_interface.hpp`:
```c++
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
```

## Etapes d'implémentation
1. Créer un fichier (`demo_renderer_basic.hpp`)
    - Ajouter la classe `DemoRendereBasic` qui hérite de `Demo` dans le .hpp
    - Ajouter aussi la classe `RendererBasic` qui hérite de `RendererInterface`
    - Ajouter les fonctions mais ne les implémentez pas pour l'instant
1. Implémentez le chargement d'une scène (plusieurs modèle obj avec TinyObj par exemple)
    - Créer les meshs, matériaux et textures qui seront référencés par les objets
    - Charger les objets dans `Scene()`
        - Utilisez random pour créer beaucoup d'objets à différentes position
    - Une fois tous les mesh/textures/materiaux chargés en RAM, appelez les fonctions `CreateMesh()`, `CreateMaterial()`, `CreateTexture()` du renderer et stocker ces données dans les objets correspondant (`Mesh`, `Material`, `Texture`)
1. A la fin du constructeur de Scene, mettez à jour les matrices des objets statiques et envoyez-les au renderer avec la fonction `renderer.SetStaticObjects(...)`
1. Dans `DemoRendereBasic::Update()` appelez la fonction `scene.UpdateAndRender()`
1. `Scene::UpdateAndRender()`
    - Ici, faite bouger les objets dynamiques
    - Puis mettez à jour les matrices en fonction
1. Implémentez à présent les fonction du renderer
    - `CreateMesh` crée le VBO/EBO et VAO (à stocker dans une nouvelle classe GPUMeshBasic qui hérite de `GPUMesh`)
    - `CreateMaterial`:Il n'y a rien à stocker pour l'instant, la fonction retourne `nullptr`
    - `CreateTexture`: Pour les texture il faut générer la texture et l'uploader sur le GPU.

## Implémentation du renderer
Pseudo code de la boucle de rendu:
```
BindShader
SendData (projection, view, lights)

for each part
    SendMaterial (bind texture + material uniforms)
    SendModelMatrix

    BindVAO

    DrawElements
```

Au fur et à mesure du TP, nous ferons évoluer notre renderer afin d'optmiser cette boucle.