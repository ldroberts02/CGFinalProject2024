#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

in vec2 fragmentUV;
in vec3 normal;

uniform vec3 COLOR;
uniform sampler2D MEMETEXTURE;

uniform vec3 AMBIENTSTRENGTH;
uniform vec3 DIFFUSECOLOR;
uniform vec3 LIGHTPOS;

void main() {
	// base color
	vec4 color = texture(MEMETEXTURE, fragmentUV);

	// ambient
	vec4 ambient = vec4(AMBIENTSTRENGTH, 1.0);

	// diffuse
	vec3 n = normalize(normal);
	vec3 lightDir = normalize(LIGHTPOS, );

	FragColor = color * ambient * diffuse;
}