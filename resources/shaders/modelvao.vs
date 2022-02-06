#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

layout(location = 3) in mat4 aModel;

uniform mat4 uVP;

out vec3 vNormal;
out vec2 vUV;

void main()
{
	vNormal = aNormal;
	vUV = aUV;

	gl_Position = vec4(aPos, 1.0) * aModel * uVP;
}