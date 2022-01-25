#pragma once

#include "types.hpp"

#include <vector>

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
    std::vector<uint> indices;
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