#version 150


uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normal_matrix;

in vec3 position;
in vec3 normal;
in vec3 color;

out VertexData {
    vec3 normal;
    vec4 eyePosition;
} VertexOut;

void main() {
    vec3 _normal = normalize(normal_matrix * normal);
    
    VertexOut.eyePosition = (view * model * vec4(position, 1.0));
    VertexOut.normal = _normal;
    gl_Position = proj * view * model * vec4(position, 1.0);
}