#version 150

in vec3 position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
}