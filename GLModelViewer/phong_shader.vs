#version 150


uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 mvp;
uniform mat3 normal_matrix;

in vec3 position;
in vec3 normal;
in vec3 color;

out VertexData {
    vec3 normal;
    vec4 eyeSpacePosition;
} VertexOut;

void main() {
    vec3 _normal = normalize(normal_matrix * normal);
    
    VertexOut.eyeSpacePosition = (view * model * vec4(position, 1.0));
    VertexOut.normal = _normal;
    gl_Position = mvp * vec4(position, 1.0);
}