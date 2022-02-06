#version 450 core
in vec3 vNormal;
in vec2 vUV;

out vec4 oColor;

uniform bool uHasTexture;
uniform sampler2D tex;

void main()
{
	if (!uHasTexture)
		oColor = vec4(1.0);
	else
		oColor = texture(tex, vUV);
}