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
    vec4 position = texture(position_sampler, uv);
    vec4 normal = texture(normal_sampler, uv);
    float depth = texture(depth_sampler, uv).x;
    
    // Materials
    vec4 diffuse = texture(diffuse_sampler, uv);
    vec4 ambient = texture(ambient_sampler, uv);
    vec4 specular = texture(specular_sampler, uv);
    float shininess = texture(shininess_sampler, uv).x;
    
    // Linearize depth
    float z = (2 * nearZ) / (farZ + nearZ - depth * (farZ - nearZ));
    
    // Restore eye space position
    vec3 viewSpace ;
    viewSpace .xy = uv *2.0 -1.0;
    viewSpace.z=depth*2.0-1.0;
    vec4 worldSpace = inverse(proj)* vec4(viewSpace,1.0);
    worldSpace.xyz/=worldSpace.w;
    
    //Lighting
    vec4 spec = vec4(0.0);
    
    vec3 l = normalize((view * vec4(1.0, 1.0, 1.0, 1.0)) - worldSpace).xyz;
    float intensity = max(dot(l, normal.xyz), 0.0);
    if(intensity > 0.0f) {
        vec3 e = normalize(- vec3(worldSpace));
        vec3 h = normalize(l + e);
        
        float intSpec = max(dot(h, normal.xyz), 0.0);
        spec = specular * pow(intSpec, 50);
    }
    
    
    outColor = max(diffuse * intensity +  spec, ambient*diffuse);
}

