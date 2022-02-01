#pragma once

#include <cmath>

#include "types.hpp"

inline float3 operator-(float3 a)
{
	return { -a.x, -a.y, -a.z };
}

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

inline mat4 operator*(const mat4& m, const mat4& m2)
{
	mat4 temp = {};

	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				temp.r[j].e[i] += m.r[k].e[i] * m2.e[j * 4 + k];
			}
		}
	}

	return temp;
}

namespace maths
{
    const float TAU = 6.283185307179586476925286f;
	const float PI = 3.14159265358979323846264338327950288f;

	const float TORAD = PI / 180.f;
	const float TODEG = 180.f / PI;
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

namespace m4
{
	inline mat4 frustum(const float& left, const float& right, const float& bot, const float& top, const float& near, const float& far)
	{
		mat4 frs;
		frs.r[0] = { (2 * near) / (right - left), 0.f, 0.f, -near * (right + left) / (right - left) };
		frs.r[1] = { 0.f, (2 * near) / (top - bot), 0.f, -near * (top + bot) / (top - bot) };
		frs.r[2] = { 0.f, 0.f, -(far + near) / (far - near), -(2 * far * near) / (far - near) };
		frs.r[3] = { 0.f, 0.f, -1.f, 0.f };
		return frs;
	}

	inline mat4 perspective(const float& fovYdeg, const float& aspect, const float& near, const float& far)
	{
		float top = near * tanf(fovYdeg * maths::TORAD * 0.5f);
		float right = top * aspect;

		return frustum(-right, right, -top, top, near, far);
	}

	inline mat4 orthographic(const float& left, const float& right, const float& bot, const float& top, const float& near, const float& far)
	{
		mat4 orth;
		orth.r[0] = { 2 / (right - left), 0.f, 0.f, -(right + left) / (right - left) };
		orth.r[1] = { 0.f, 2 / (top - bot), 0.f, -(top + bot) / (top - bot) };
		orth.r[2] = { 0.f, 0.f, -2 / (far - near), -(far + near) / (far - near) };
		orth.r[3] = { 0.f, 0.f, 0.f, 1.f };
		return orth;
	}

	inline mat4 translateMatrix(const vec3& pos)
	{
		return mat4{
			1.f, 0.f, 0.f, pos.x,
			0.f, 1.f, 0.f, pos.y,
			0.f, 0.f, 1.f, pos.z,
			0.f, 0.f, 0.f, 1.f,
		};
	}

	//angle in degrees
	inline mat4 rotateXMatrix(const float& pitch)
	{
		float a = pitch * maths::TORAD;
		return mat4{
			1.f, 0.f, 0.f, 0.f,
			0.f, cos(a), -sin(a), 0.f,
			0.f, sin(a), cos(a), 0.f,
			0.f, 0.f, 0.f, 1.f,
		};
	}

	//angle in degrees
	inline mat4 rotateYMatrix(const float& yaw)
	{
		float a = yaw * maths::TORAD;
		return mat4{
			cos(a), 0.f, sin(a), 0.f,
			0.f, 1.f, 0.f, 0.f,
			-sin(a), 0.f, cos(a), 0.f,
			0.f, 0.f, 0.f, 1.f,
		};
	}

	//angle in degrees
	inline mat4 rotateZMatrix(const float& roll)
	{
		float a = roll * maths::TORAD;
		return mat4{
			cos(a), -sin(a), 0.f, 0.f,
			sin(a), cos(a), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f,
		};
	}

	inline mat4 scaleMatrix(const vec3& scale)
	{
		return mat4{
			scale.x, 0.f, 0.f, 0.f,
			0.f, scale.y, 0.f, 0.f,
			0.f, 0.f, scale.z, 0.f,
			0.f, 0.f, 0.f, 1.f,
		};
	}
}