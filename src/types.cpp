#include "types.hpp"

const float2 float2::zero = { 0.f, 0.f };

const float3 float3::zero = { 0.f, 0.f, 0.f };

const float4 float4::white = { 1.f, 1.f, 1.f, 1.f };
const float4 float4::silver = { 0.75f, 0.75f, 0.75f };
const float4 float4::gray = { 0.5f, 0.5f, 0.5f };
const float4 float4::black = { 0.f, 0.f, 0.f, 1.f };
const float4 float4::red = { 1.f, 0.f, 0.f, 1.f };
const float4 float4::maroon = { 0.5f, 0.f, 0.f, 1.f };
const float4 float4::yellow = { 1.f, 1.f, 0.f, 1.f };
const float4 float4::olive = { 0.5f, 0.5f, 0.f, 1.f };
const float4 float4::lime = { 0.f, 1.f, 0.f, 1.f };
const float4 float4::green = { 0.f, 0.5f, 0.f, 1.f };
const float4 float4::aqua = { 0.f, 1.f, 1.f, 1.f };
const float4 float4::teal = { 0.f, 0.5f, 0.5f, 1.f };
const float4 float4::blue = { 0.f, 0.f, 1.f, 1.f };
const float4 float4::navy = { 0.f, 0.f, 0.5f, 1.f };
const float4 float4::fuchsia = { 1.f, 0.f, 1.f, 1.f };
const float4 float4::purple = { 0.5f, 0.f, 0.5f, 1.f };

const mat4 mat4::identity = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};