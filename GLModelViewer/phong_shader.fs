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
    vec3 color; // Not used anymore
    vec4 eye;
} VertexIn;

void main() {
    vec4 spec = vec4(0.0);
    vec3 l_dir = (view * vec4(1.0, 0.0, 2.0, 0.0)).xyz;
    
    // Normalize input, since it is interpolated
    vec3 e = normalize(vec3(VertexIn.eye));
    vec3 n = normalize(VertexIn.normal);
    
    float intensity = max(dot(n, normalize(l_dir)), 0.0);
    
    if(intensity > 0.0) {
        vec3 h = normalize(normalize(l_dir) + e);
        
        float intSpec = max(dot(h, n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }
    
    outColor =  max(intensity * diffuse + spec, ambient).xyz;
    outNormal = VertexIn.normal;
}