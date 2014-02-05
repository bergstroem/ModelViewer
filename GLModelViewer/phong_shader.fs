#version 150

#define M_PI 3.1415926535897932384626433832795

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
    vec3 direction;
    float angle;
    float spotExponent;
    float constantAtt;
    float linearAtt;
    float exponentialAtt;
} LightIn;

out vec4 outColor;

in VertexData {
    vec3 normal;
    vec4 eyeSpacePosition;
} VertexIn;


void main() {
    vec4 color = vec4(0.0);
    
    vec3 n = normalize(VertexIn.normal);
    
    // Calculate direction to light
    vec3 l = ((view * LightIn.position) - VertexIn.eyeSpacePosition).xyz;
    
    // Get distance to light before normalizing
    float lightDistance = length(l);
    float att = 1 / (LightIn.constantAtt + LightIn.linearAtt*lightDistance + LightIn.exponentialAtt*lightDistance*lightDistance);
    
    l = normalize(l);
    
    float intensity = max(dot(n, l), 0.0);
    
    if(intensity > 0.0) {
        
        vec4 viewSpaceLightDir = view * vec4(LightIn.direction, 0.0);
        
        float spotEffect = dot(normalize(viewSpaceLightDir.xyz), normalize(-l));
        
        float cosCutOff = cos(LightIn.angle*M_PI/180);
        
        if (spotEffect > cosCutOff) {
            // Calculate Light
            
            spotEffect = pow(spotEffect, LightIn.spotExponent);
            att = att * spotEffect;
            
            color += att * diffuse * intensity * LightIn.intensity;
            
            // Vector to camera
            vec3 e = normalize(- vec3(VertexIn.eyeSpacePosition));
            vec3 h = normalize(l + e);
            
            float intSpec = max(dot(h, n), 0.0);
            color += specular * pow(intSpec, shininess) * att * LightIn.intensity;
        }
    }
    
    outColor = max(color, ambient);
}

