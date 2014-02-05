#version 150

uniform mat4 view;

layout (std140) uniform Material {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    float shininess;
};

layout (std140) uniform Light {
    vec4 position;
    vec4 intensity;
    struct {
        float constant;
        float linear;
        float exponential;
    } Attenuation;
} LightIn;

out vec4 outColor;

in VertexData {
    vec3 normal;
    vec4 eyeSpacePosition;
} VertexIn;


void main() {
    vec4 spec = vec4(0.0);
    
    vec3 n = normalize(VertexIn.normal);
    
    // Calculate direction to light
    vec3 l = ((view * LightIn.position) - VertexIn.eyeSpacePosition).xyz;
    
    // Get distance to light before normalizing
    float lightDistance = length(l);
    float att = 1 / (LightIn.Attenuation.constant + LightIn.Attenuation.linear*lightDistance + LightIn.Attenuation.exponential*lightDistance*lightDistance);

    l = normalize(l);
    
    float intensity = max(dot(n, l), 0.0);
    
    if(intensity > 0.0) {
        // Vector to camera
        vec3 e = normalize(- vec3(VertexIn.eyeSpacePosition));
        vec3 h = normalize(l + e);
        
        float intSpec = max(dot(h, n), 0.0);
        spec = specular * pow(intSpec, shininess);
    }
    
    vec4 totalColor = (diffuse * intensity +  spec) * att * LightIn.intensity;
    
    outColor = max(totalColor, ambient*diffuse * att);
}

