#version 150

in vec3 position;

out vec2 uv;

void main()
{
    vec2 screenCoords = vec2(position.x+1.0, position.y+1.0)/2;
    uv = screenCoords;
    gl_Position = vec4(position, 1.0);
}