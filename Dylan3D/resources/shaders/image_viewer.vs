#version 450

in vec2 Position;
in vec2 TexCoords;

out vec2 vTexCoords;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
	vTexCoords = TexCoords;
	
    gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);
}