#version 150

#define M_PI 3.1415926535897932384626433832795


in vec2 uv;

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

uniform mat4 proj;
uniform mat4 view;
uniform mat4 inverse_proj;

uniform sampler2D normal_sampler;
uniform sampler2D depth_sampler;

//Material
uniform sampler2D diffuse_sampler;
uniform sampler2D ambient_sampler;
uniform sampler2D specular_sampler;
uniform sampler2D shininess_sampler;



out vec4 outColor;

void main() {
    vec4 color = vec4(0.0);
    
    vec3 normal = normalize(texture(normal_sampler, uv).xyz);
    float depth = texture(depth_sampler, uv).x * 2.0 -1.0;
    
    if(depth == 1.0) {
        outColor = vec4(0.0,0.0,0.0,1.0);
        return;
    }
    
    // Materials
    vec4 diffuse = texture(diffuse_sampler, uv);
    vec4 ambient = texture(ambient_sampler, uv);
    vec4 specular = texture(specular_sampler, uv);
    float shininess = texture(shininess_sampler, uv).x;
    
    // Restore eye space position
    vec3 viewSpace;
    viewSpace.xy = uv * 2.0 -1.0; // uv coords are in [0-1], we need [-1, 1] for screen coords
    viewSpace.z=depth;
    vec4 worldSpace = inverse_proj * vec4(viewSpace,1.0);
    worldSpace.xyz/=worldSpace.w;
    
    //Lighting
    vec4 spec = vec4(0.0);
    
    vec3 l = ((view * LightIn.position) - worldSpace).xyz;
    
    float lightDistance = length(l);
    
    
    l = normalize(l);
    
    float intensity = max(dot(l, normal), 0.0);
    if(intensity > 0.0f) {
        vec4 viewSpaceLightDir = view * LightIn.direction;
        float spotEffect = dot(normalize(viewSpaceLightDir.xyz), normalize(-l));
        float spotCutOff = cos(LightIn.angle*M_PI/180);
        
        if(spotEffect > spotCutOff) {
            spotEffect = pow(spotEffect, LightIn.spotExponent);
            float att = spotEffect / (LightIn.constantAtt + LightIn.linearAtt*lightDistance + LightIn.exponentialAtt*lightDistance*lightDistance);
            
            color += diffuse * intensity * att * LightIn.intensity;
            
            vec3 e = normalize(- vec3(worldSpace));
            vec3 h = normalize(l + e);
        
            float intSpec = max(dot(h, normal), 0.0);
            color += specular * pow(intSpec, shininess) * att * LightIn.intensity;
        }
    }
    
    outColor = max(color, ambient);
}

