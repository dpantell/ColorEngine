#version 450

in vec4 Position;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;
out vec4 normal;
out vec4 position;
out vec4 texcoord;

uniform sampler2D diffuse_image;

void main()
{
    color = texture(diffuse_image, TexCoord);
	
	position = Position;
	texcoord = vec4(TexCoord, 0, 1);
	normal = vec4(Normal, 0);
}