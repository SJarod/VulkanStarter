#pragma once

typedef unsigned int uint;

struct float2
{
	float x;
	float y;

	static const float2 zero;
};

union float3
{
	struct { float x, y, z; };
	float e[3];
	float2 xy;

	static const float3 zero;
};

union float4
{
	struct { float x, y, z, w; };
	float e[4];
	float3 xyz;

	static const float4 white;
	static const float4 silver;
	static const float4 gray;
	static const float4 black;
	static const float4 red;
	static const float4 maroon;
	static const float4 yellow;
	static const float4 olive;
	static const float4 lime;
	static const float4 green;
	static const float4 aqua;
	static const float4 teal;
	static const float4 blue;
	static const float4 navy;
	static const float4 fuchsia;
	static const float4 purple;
};

typedef float2 vec2;
typedef float3 vec3;
typedef float4 vec4;

union mat4
{
	float4 r[4];
	float e[16];

	static const mat4 identity;
};