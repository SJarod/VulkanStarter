// v1 (One big vertex/index buffer)
// Only one VAO for all objects
// (Object store an index to the first index/vertex)

BindShader
SendData (projection, view, lights)

BindVAO
for each object
    SendMaterial
    SendModelMatrix

    DrawElementsBaseVertex

// v2 (Materials UBO)
// Send all materials to the shader in advance (in a uniform buffer)
// Put all textures in one GL_TEXTURE_2D_ARRAY (with glTexImage3D) texture to access them via index
struct material{
    int diffuseTextureIndex; // Index in 3D texture
    float4 diffuseColor;
    ...
};

layout (binding = 0) uniform sampler2DArray textureArray;
color = texture(textureArray, vec3(uv.x, uv.y, material.textureIndex));

// Setup the vertex array to setup the material index (each mesh has a material index)

// Then ...
for each object
    SendModelMatrix

    DrawElementsBaseVertex

// v3: (Draw static objects in one draw call)
// Distinguish between static objects that never move, and dynamic objects that can move every frame.
// Send all the materials to the shader

// Render all static objects
// Also send all model matrices (or only pos/rot/scale) in a UBO (like materials in v2)
// 

...
BindVAO
for each object
    DrawElementsBaseVertex(enum mode, sizei count, enum type, const void *indices, int basevertex);

// Then, instead of passing all parameters each time https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_draw_indirect.txt
for each object
    DrawElementsIndirect

// Then, remove for loop with https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multi_draw_indirect.txt
MultiDrawElementsIndirect

// v4: (NV_command_list) https://www.khronos.org/registry/OpenGL/extensions/NV/NV_command_list.txt
// Add extension by generating glad header: https://gen.glad.sh/ (4.6, core, check loader)
