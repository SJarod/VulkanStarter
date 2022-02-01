#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

uniform mat4 uVP;
uniform mat4 uModel;

out vec3 vNormal;
out vec2 vUV;

void main()
{
	vNormal = aNormal;
	vUV = aUV;

	gl_Position = vec4(aPos, 1.0) * uModel * uVP;
}