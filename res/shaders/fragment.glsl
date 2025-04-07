#version 330 core

#define MAX_LIGHTS 128

in vec3 FragPos;
in vec3 Normal; 

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 


uniform vec3 viewPos;

// Light properties
uniform int lightCount;
uniform Light lights[MAX_LIGHTS];

// Material properties
uniform Material material;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){

    vec3 norm = normalize(Normal);

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < lightCount; i++)
    {
        result += CalcPointLight(lights[i], norm, FragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    // ambient
    vec3 ambient = light.ambient * material.ambient;

    // diffuse 
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 specular = light.specular * (spec * material.specular); 

    diffuse *= attenuation;
    specular *= attenuation; 
    return (ambient + diffuse + specular);
}