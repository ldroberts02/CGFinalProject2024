#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;

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
uniform DirectionalLight directionalLight;
uniform sampler2D texture1;

void main()
{
    // ambient
    vec3 ambient = directionalLight.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = oNormal;
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directionalLight.specular * (spec * material.specular);  
        
    
    FragColor = vec4((ambient + diffuse + specular), 1.0) * texture(texture1, texCoord);
} 

//void main()
//{
//    // ambient
//    float ambientStrength = 0.1;
//    vec3 ambient = ambientStrength * lightColor;
//
//    // diffuse
//    vec3 norm = oNormal;
//    vec3 lightDir = normalize(lightPosition - fragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = diff * lightColor;
//
//    // specular
//    float specularStrength = 0.5;
//    vec3 viewDir = normalize(viewPos - fragPos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;
//
//    if(diff > 0.1)
//        FragColor = vec4((ambient + diffuse + specular), 1.0) * texture(texture1, texCoord);
//    else
//        FragColor = vec4((ambient), 1.0) * texture(texture1, texCoord);
//}