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

out vec3 outDiffuse;
out vec3 outNormal;
out vec3 outPosition;
out vec3 outAmbient;
out vec3 outSpecular;
out vec3 outShininess;

void main()
{
    outNormal = VertexIn.normal;
    outDiffuse = diffuse.xyz;
    outPosition = VertexIn.viewModelPosition.xyz;
    outAmbient = ambient.xyz;
    outSpecular = specular.xyz;
    outShininess.x = shininess;
}
