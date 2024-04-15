#version 330 core
//The fragment shader operates on each pixel in a given polygon
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

in vec2 fragmentUV;
in vec3 fragmentPos;
in vec3 fragmentNormal;

uniform vec3 COLOR;
uniform Material MATERIAL;
uniform PointLight POINTLIGHTS[4];
uniform int numberOfPointLights;

uniform vec3 VIEWPOS;

void main() {
	// base color
	vec4 color = texture(MATERIAL.diffuse, fragmentUV);

	// ambient
    vec3 ambient = POINTLIGHTS[0].ambient;
  	
    // diffuse 
    vec3 norm = normalize(fragmentNormal);
    vec3 lightDir = normalize(POINTLIGHTS[0].position - fragmentPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = POINTLIGHTS[0].diffuse * diff;  
    
    // specular
    vec3 viewDir = normalize(VIEWPOS - fragmentPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), MATERIAL.shininess);
    vec3 specular = POINTLIGHTS[0].specular * spec * texture(MATERIAL.specular, fragmentUV).rgb;  
    
    // attenuation
    float distance    = length(POINTLIGHTS[0].position - fragmentPos);
    float attenuation = 1.0 / (POINTLIGHTS[0].constant + POINTLIGHTS[0].linear * distance + POINTLIGHTS[0].quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;

	FragColor = color * vec4(result, 1.0);
}