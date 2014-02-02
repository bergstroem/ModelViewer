#version 150

layout (std140) uniform Material {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    float shininess;
};

in VertexAttribute {
    vec4 viewModelPosition;
    vec3 normal;
} VertexIn;

out vec3 outColor;
out vec3 outNormal;
out vec3 outPosition;
out vec3 outAmbient;
out vec3 outSpecular;
out vec3 outShininess;

void main()
{
    outColor = diffuse.xyz;
    outNormal = VertexIn.normal;
    outPosition = VertexIn.viewModelPosition.xyz;
    outAmbient = ambient.xyz;
    outSpecular = specular.xyz;
    outShininess.x = 0.5;
}
