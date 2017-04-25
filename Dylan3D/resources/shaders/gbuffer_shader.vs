#version 450

in vec3 position;
in vec2 texcoord;
in vec3 normal;
in mat4 world;

out vec4 Position;
out vec2 TexCoord;
out vec3 Normal;

//uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
	Position = world * vec4(position, 1.0f);
	TexCoord = vec2(texcoord.x, texcoord.y);
	Normal = (world * vec4(normal, 0)).xyz;
	
    gl_Position = projection * view * Position;
}