#version 150

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normal_matrix;

uniform float nearZ;
uniform float farZ;

in vec3 position;
in vec3 normal;

out VertexAttribute {
    vec4 viewModelPosition;
    vec4 normal;
} VertexOut;

void main()
{
    vec3 _normal = normalize(normal_matrix * normal);
    VertexOut.normal = vec4(_normal, 0.0);
    VertexOut.viewModelPosition = proj * view * model * vec4(position, 1.0);
    gl_Position = VertexOut.viewModelPosition;
}