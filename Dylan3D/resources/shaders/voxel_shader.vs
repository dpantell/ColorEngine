#version 450

in vec3 position;
in vec3 normal;
in vec2 texcoord;
in vec3 i_position;
in vec2 i_sprite_index;

out vec4 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform float sprite_size;
uniform vec2 sprite_sheet_size;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
	Position = vec4(position + i_position, 1.0f);
	Normal = normal;
	
	vec2 index = i_sprite_index;
	vec2 ratio =  sprite_size / sprite_sheet_size;
	
	if (texcoord.x < 0.5f) TexCoord.x = ratio.x * index.x;
	if (texcoord.x >= 0.5f) TexCoord.x = ratio.x * (index.x + 1);
	if (texcoord.y < 0.5f) TexCoord.y = ratio.y * index.y;
	if (texcoord.y >= 0.5f) TexCoord.y = ratio.y * (index.y + 1);
	
    gl_Position = projection * view * Position;
}