#version 150

#define M_PI 3.1415926535897932384626433832795

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 mvp;
uniform mat3 normal_matrix;
uniform mat4 light_mvp;

uniform sampler2D shadow_sampler;

layout (std140) uniform Material {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    float shininess;
};

layout (std140) uniform Light {
    vec4 position;
    vec4 intensity;
    vec4 direction;
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
    vec3 modelPosition;
} VertexIn;


uniform float nearZ;
uniform float farZ;

void main() {
    
    // Retrieve coordinates from light perspective
    vec4 projectedPosLightPov = (light_mvp * vec4(VertexIn.modelPosition, 1.0));
    vec3 projectedPosLightPovNormal = projectedPosLightPov.xyz/projectedPosLightPov.w;
    vec3 shadow_coords = projectedPosLightPovNormal;
    
    // Starting color
    vec4 color = vec4(0.0);
    
    // Calculate direction to light
    vec3 n = normalize(VertexIn.normal);
    vec3 l = ((view * LightIn.position) - VertexIn.eyeSpacePosition).xyz;
    
    // Get distance to light before normalizing
    float lightDistance = length(l);
    l = normalize(l);
    
    float intensity = max(dot(n, l), 0.0);
    if(intensity > 0.0) {
        
        // Depth test for shadow
        float visibility = 1.0;
        float bias = 0.001;
        if ( texture( shadow_sampler, shadow_coords.xy ).x  <  shadow_coords.z - bias) {
            visibility = 0.0;
        }
        
        // Get light direction in eye space
        vec4 viewLightDir = view * LightIn.direction;
        
        // Determine if spot angle is larger than the 'spot cone's' angle
        float spotEffect = dot(normalize(viewLightDir.xyz), normalize(-l));
        float cosCutOff = cos(LightIn.angle*M_PI/180);
        
        if (spotEffect > cosCutOff) {
            // Calculate Light
            spotEffect = pow(spotEffect, LightIn.spotExponent);
            
            // Calculated light attenuation
            float att = spotEffect / (LightIn.constantAtt + LightIn.linearAtt*lightDistance + LightIn.exponentialAtt*lightDistance*lightDistance);
            
            // Diffuse light
            color += att * diffuse * intensity * LightIn.intensity * visibility;
            
            // Vector to camera
            vec3 e = normalize(- vec3(VertexIn.eyeSpacePosition));
            vec3 h = normalize(l + e);
            float intSpec = max(dot(h, n), 0.0);
            
            // Specular light
            color += specular * pow(intSpec, shininess) * att * LightIn.intensity * visibility;
        }
    }
    
    outColor = max(color, ambient);
}

