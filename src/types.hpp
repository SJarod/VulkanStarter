#pragma once

typedef unsigned int uint;

struct float2
{
    float x;
    float y;
};

struct float3
{
    float x;
    float y;
    float z;
};

struct float4
{
    float x;
    float y;
    float z;
    float w;
};

typedef float2 vec2;
typedef float3 vec3;
typedef float4 vec4;

union mat4
{
    float4 c[4];
    float e[16];

    static const mat4 identity;
};