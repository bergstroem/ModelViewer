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

out vec4 outDiffuse;
out vec4 outNormal;
out vec4 outAmbient;
out vec4 outSpecular;
out vec4 outShininess;

void main()
{
    outNormal = vec4(normalize(VertexIn.normal), 1.0);
    outDiffuse = diffuse;
    outAmbient = ambient;
    outSpecular = specular;
    outShininess.x = shininess;
}
