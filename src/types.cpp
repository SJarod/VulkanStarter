#include "types.hpp"

const float3 float3::zero = { 0.f, 0.f, 0.f };

const mat4 mat4::identity = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};