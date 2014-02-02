#version 150

in vec2 uv;

uniform mat4 proj;
uniform mat4 view;

uniform sampler2D position_sampler;
uniform sampler2D normal_sampler;
uniform sampler2D depth_sampler;

//Material
uniform sampler2D diffuse_sampler;
uniform sampler2D ambient_sampler;
uniform sampler2D specular_sampler;
uniform sampler2D shininess_sampler;

uniform float nearZ;
uniform float farZ;

out vec4 outColor;

void main() {
    /*vec4 spec = vec4(0.0);
    vec3 n = vec3(normalize(texture(normal_sampler, uv)));
    vec4 eyeSpacePosition = texture(position_sampler, uv); // Felet, denna är en unit vector, dvs inte position
    // Lösning, spara in denna utan accessa ljuset istället, det +  uv och inversen av proj kan ge position.

    //Material
    vec4 diffuse = texture(diffuse_sampler, uv);
    vec4 specular = texture(specular_sampler, uv);
    vec4 ambient = texture(ambient_sampler, uv);
    float shininess = texture(shininess_sampler, uv).x;
    
    
    vec3 l = normalize((view * vec4(1.0, 1.0, 1.0, 1.0)) - eyeSpacePosition).xyz;
    float intensity = max(dot(l, n), 0.0);
    
    if(intensity > 0.0f) {
        vec3 e = normalize(- vec3(eyeSpacePosition));
        vec3 h = normalize(l + e);
        
        float intSpec = max(dot(h, n), 0.0);
        spec = specular * pow(intSpec, 50);
    }*/
    vec4 position = texture(position_sampler, uv);
    vec4 normal = texture(normal_sampler, uv);
    vec4 depth = texture(depth_sampler, uv);
    
    // Materials
    vec4 diffuse = texture(diffuse_sampler, uv);
    vec4 ambient = texture(ambient_sampler, uv);
    vec4 specular = texture(specular_sampler, uv);
    vec4 shininess = texture(shininess_sampler, uv);
    
    // Linearize depth
    float z = (2 * nearZ) / (farZ + nearZ - depth.x * (farZ - nearZ));
    
    outColor = vec4(z);//max(diffuse * intensity +  spec, ambient*diffuse);
}