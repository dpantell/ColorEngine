#version 450

in vec2 Position;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);
}