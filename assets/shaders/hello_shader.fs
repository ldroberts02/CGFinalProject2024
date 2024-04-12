#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

in vec2 fragmentUV;
in vec3 normal;
in vec3 fragmentPos;

uniform vec3 COLOR;
uniform Material MATERIAL;

uniform vec3 AMBIENTSTRENGTH;
uniform vec3 DIFFUSECOLOR;
uniform vec3 SPECULARCOLOR;
uniform vec3 LIGHTPOS;
uniform vec3 VIEWPOS;

void main() {
	// base color
	vec4 color = texture(MATERIAL.diffuse, fragmentUV);

	// ambient
	vec4 ambient = vec4(AMBIENTSTRENGTH, 1.0);

	// diffuse
	vec3 n = normalize(normal);
	vec3 lightDir = normalize(LIGHTPOS - fragmentPos);
	float diff = max(dot(n, lightDir), 0.0);
	vec4 diffuse = vec4(DIFFUSECOLOR * diff, 1.0);

	// specular
	float specStrength = texture(MATERIAL.specular, fragmentUV);
	vec3 viewDir = normalize(VIEWPOS - fragmentPos);
	vec3 reflectDir = reflect(-lightDir, n);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), MATERIAL.shininess);
	vec4 specular = vec4(SPECULARCOLOR * specStrength * spec, 1.0);

	FragColor = color * (ambient + diffuse + specular);
}