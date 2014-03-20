#version 150

in vec3 position;
in vec3 normal;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 mvp;
uniform mat4 normal_matrix;

out vec3 vCubeMap;

void main()
{
    vec3 vVertex = vec3(view * model * vec4(position, 1.0));
    
    vCubeMap = vec3(position) - vec3(0.5);
    
    gl_Position = mvp * vec4(position, 1.0);
}