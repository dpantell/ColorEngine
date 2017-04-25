#version 450

in vec2 vTexCoords;
out vec4 color;

uniform sampler2D image;

void main()
{
	color = texture(image, vTexCoords);
} 