#version 450

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D PositionTexture;

uniform vec3 ViewPosition;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform vec2 ScreenSize;

out vec4 PhongColor;

void main()
{
	vec2 frag_coord = gl_FragCoord.xy / ScreenSize;
	
	vec3 diffuse_color = texture(DiffuseTexture, frag_coord).xyz;
	vec3 world_normal = texture(NormalTexture, frag_coord).xyz;
	vec3 world_position = texture(PositionTexture, frag_coord).xyz;
	
	vec3 N = world_normal;
	vec3 L = normalize(LightPosition - world_position);
	vec3 E = normalize(ViewPosition - world_position);
	vec3 R = normalize(-reflect(L, N));
	
	float ambient = 0.5f;
	float diffuse = max(dot(N, L), 0);
	float specular = max(dot(R, E), 0);
	
	vec3 phong = ((ambient + diffuse + specular) * LightColor) * diffuse_color;
	
	PhongColor = vec4(phong, 0);
} 