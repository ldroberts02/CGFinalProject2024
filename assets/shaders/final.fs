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

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec3 oNormal;
in vec2 texCoord;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform sampler2D texture1;
uniform int numDirLights;
uniform int numPointLights;
uniform int numSpotLights;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[10];
uniform SpotLight spotLight[2];
uniform vec4 color;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fp, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fp, vec3 viewDir);

void main()
{
    if (texture(texture1, texCoord).a == 0.0)
        discard;
    
    // properties
    vec3 norm = normalize(oNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    // phase 1: directional lighting
    vec3 result;
    if (numDirLights > 0)
        result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < numPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);    
    // phase 3: spot light
    for(int i = 0; i < numSpotLights; i++)
        result += CalcSpotLight(spotLight[i], norm, fragPos, viewDir);

    float alpha = min(color.a, texture(texture1, texCoord).a);
    
    FragColor = vec4(result, alpha);

    // apply gamma correction
    float gamma = 2.2;
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * material.ambient * (vec3(color) * vec3(texture(texture1, texCoord)));
    //vec3 ambient = light.ambient * texture1;
    vec3 diffuse = light.diffuse * material.diffuse * diff * (vec3(color) * vec3(texture(texture1, texCoord)));
    //vec3 diffuse = light.diffuse * diff * texture1;
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fp, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fp);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    //vec3 reflectDir = reflect(-lightDir, normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // specular shading blinn-phong
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fp);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * material.ambient * (vec3(color) * vec3(texture(texture1, texCoord)));
    vec3 diffuse = light.diffuse * material.diffuse * diff * (vec3(color) * vec3(texture(texture1, texCoord)));
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    vec3 specular = light.specular * spec * material.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fp, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fp);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fp);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * (vec3(color) * vec3(texture(texture1, texCoord)));
    vec3 diffuse = light.diffuse * diff * (vec3(color) * vec3(texture(texture1, texCoord)));
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
    //vec3 ambient = light.ambient * texture1;
    //vec3 diffuse = light.diffuse * diff * texture1;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}