#version 330 core

out vec4 FragColor;

// struct Material {
//     vec3 ambient;
//     sampler2D diffuse;
//     sampler2D specular;
//     float shininess;
// };

// struct DirLight {
//     vec3 direction;
	
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
// };

in vec3 FragPos;
in vec3 Normal; 

uniform vec3 viewPos;

void main(){
    vec3 viewDir = normalize(viewPos - FragPos);

    FragColor = vec4(Normal, 1.0); // Initialize color to black
}
