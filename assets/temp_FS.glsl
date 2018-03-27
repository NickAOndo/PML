#version 150 core

in vec3 Pos;
in vec3 Color;
in vec3 Normal;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
	vec3 amb_dir = normalize(vec3(0.0, -1.0, 1.0));
	vec3 src_pnt = vec3(0.0,0.0,-0.5);
	float lum_src = 10*dot( Normal, src_pnt-Pos) / pow( length(Pos-src_pnt), 3);
	float amb = 1.0*dot(Normal, -amb_dir);
	float lum_tot = ( 3*lum_src+amb )/4;

	outColor = clamp( texture(tex,Texcoord)*vec4(Color,1.0)*lum_tot, vec4(0,0,0,0), vec4(1,1,1,1) );
}
