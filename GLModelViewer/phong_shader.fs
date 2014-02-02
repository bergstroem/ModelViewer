#version 150

uniform mat4 view;

layout (std140) uniform Material {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    float shininess;
};

out vec4 outColor;
out vec4 outNormal;

in VertexData {
    vec3 normal;
    vec4 eyeSpacePosition;
} VertexIn;

void main() {
    vec4 spec = vec4(0.0);
    
    vec3 n = normalize(VertexIn.normal);
    
    // Calculate direction to light
    vec3 l = normalize((view * vec4(1.0, 1.0, 1.0, 1.0)) - VertexIn.eyeSpacePosition).xyz;
    
    float intensity = max(dot(n, l), 0.0);
    
    if(intensity > 0.0) {
        // Vector to camera
        vec3 e = normalize(- vec3(VertexIn.eyeSpacePosition));
        vec3 h = normalize(l + e);
        
        float intSpec = max(dot(h, n), 0.0);
        spec = specular * pow(intSpec, shininess);
        outColor = vec4(pow(intSpec, shininess), 0.0, 0.0, 1.0);
    } else {
    outColor = vec4(0.0);
    }//max(diffuse * intensity +  spec, ambient*diffuse);
}