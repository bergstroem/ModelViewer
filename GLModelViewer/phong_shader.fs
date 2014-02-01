#version 150

uniform mat4 view;

layout (std140) uniform Material {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    float shininess;
};

out vec3 outColor;
out vec3 outNormal;

in VertexData {
    vec3 normal;
    vec4 eyePosition;
} VertexIn;

void main() {
    vec4 spec = vec4(0.0);
    
    vec3 n = normalize(VertexIn.normal);
    
    // Calculate direction to light
    vec3 l = normalize((view * vec4(-1.0, 1.0, 1.0, 1.0)) - VertexIn.eyePosition).xyz;
    
    float intensity = max(dot(n, l), 0.0);
    
    if(intensity > 0.0) {
        // Vector to camera
        vec3 e = normalize(- vec3(VertexIn.eyePosition));
        vec3 h = normalize(l + e);
        
        float intSpec = max(dot(h, n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }
    
    outColor = max(diffuse * intensity +  spec, vec4(0.0)).xyz;
    
    
    outNormal = VertexIn.normal;
}