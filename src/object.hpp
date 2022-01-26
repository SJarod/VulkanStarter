#pragma once
                              
#include <vector>

#include "types.hpp"

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

//stores cpu and gpu version of mesh
struct Mesh
{
    //cpu
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    //gpu
    GPUMesh* gpu;
};

struct Texture
{
    //cpu
    int width;
    int height;
    int bpp;
    void* data; // On va dire qu'on supporte seulement UNSIGNED_BYTE
    //gpu
    GPUTexture* gpu;
};

struct Material
{
    //cpu
    float4 diffuseColor;
    Texture* diffuseTexture;
    //gpu
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