#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

in vec2 fragmentUV;
in vec3 normal;
in vec3 fragmentPos;

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
	vec3 lightDir = normalize(LIGHTPOS - fragmentPos);
	float diff = max(dot(n, lightDir), 0.0);
	vec4 diffuse = vec4(DIFFUSECOLOR * diff, 1.0);

	FragColor = color * (ambient + diffuse);
}