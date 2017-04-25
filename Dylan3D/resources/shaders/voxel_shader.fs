#version 450

in vec4 Position;
in vec3 Normal;
in vec2 TexCoord;

out vec4 color;
out vec4 texcoord;
out vec4 position;
out vec4 normal;

uniform sampler2D diffuse_image;
uniform sampler2D sprite_sheet_image;

void main()
{
    color = texture(sprite_sheet_image, TexCoord);
	position = Position;
	normal = vec4(Normal, 0);
	texcoord = vec4(TexCoord, 0, 1);
}