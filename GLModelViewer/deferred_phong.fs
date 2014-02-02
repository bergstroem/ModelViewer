#version 150

in vec2 uv;

uniform mat4 proj;
uniform mat4 view;

uniform sampler2D position_sampler;
uniform sampler2D normal_sampler;
uniform sampler2D diffuse_sampler;
uniform sampler2D ambient_sampler;
uniform sampler2D specular_sampler;
uniform sampler2D shininess_sampler;

out vec4 outColor;



void main() {
    vec4 spec = vec4(0.0);
    
    vec3 n = vec3(normalize(texture(normal_sampler, uv)));
    vec4 eyeSpacePosition = texture(position_sampler, uv);
    vec4 diffuse = texture(diffuse_sampler, uv);
    vec4 specular = texture(specular_sampler, uv);
    vec4 ambient = texture(ambient_sampler, uv);
    float shininess = texture(shininess_sampler, uv).x;
    
    vec3 l = normalize((view * vec4(1.0, 1.0, 1.0, 1.0)) - eyeSpacePosition).xyz;
    float intensity = max(dot(n, l), 0.0);
    
    if(intensity > 0.0) {
        vec3 e = normalize(- vec3(eyeSpacePosition));
        vec3 h = normalize(l + e);
        
        float intSpec = max(dot(l, n), 0.0);
        spec = specular * pow(intSpec, 50);
    }
    outColor = max(diffuse * intensity +  spec, ambient*diffuse);
}