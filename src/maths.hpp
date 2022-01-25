#pragma once

#include <cmath>

#include "types.hpp"

inline float3 operator-(float3 a, float3 b)
{
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline float3 operator+(float3 a, float3 b)
{
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline float3 operator*(float a, float3 b)
{
    return { a * b.x, a * b.y, a* b.z };
}

namespace maths
{
    const float TAU = 6.283185307179586476925286f;
}

namespace v3
{
inline float3 cross(float3 a, float3 b)
{
    return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}

inline float dot(float3 a, float3 b)
{
    return { a.x * b.x + a.y * b.y + a.z * b.z };
}

inline float length(float3 a)
{
    return sqrtf(dot(a, a));
}

inline float3 normalize(float3 a)
{
    float l = length(a);
    return { a.x / l, a.y / l, a.z / l };
}
}