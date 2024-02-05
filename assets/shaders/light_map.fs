#version 330 core

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
};

in vec3 oNormal;
in vec2 texCoord;
in vec3 fragPos;

out vec4 FragColor;

//uniform vec3 lightColor;
//uniform vec3 lightPosition;
uniform vec3 viewPos;
uniform Material material;
uniform PointLight pointLight;

void main()
{
    // ambient
    vec3 ambient = pointLight.ambient * texture(material.diffuse, texCoord).rgb;
  	
    // diffuse 
    vec3 norm = oNormal;
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * (diff * texture(material.diffuse, texCoord).rgb);
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * texture(material.specular, texCoord).rgb;  
        
    
    FragColor = vec4((ambient + diffuse + specular), 1.0);
} 
