#version 150

in vec3 position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 mvp;

out vec4 projectedPosition;

void main()
{
    projectedPosition = mvp * vec4(position, 1.0);
    gl_Position = projectedPosition;
}