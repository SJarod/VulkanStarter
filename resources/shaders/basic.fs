#version 450 core
in vec3 vNormal;
in vec2 vUV;

out vec4 oColor;

uniform sampler2D tex;

void main()
{
	//oColor = vec4(vUV.x, vUV.y, 1.0 - abs(vUV.x - vUV.y), 1.0);
	oColor = texture(tex, vUV);
}