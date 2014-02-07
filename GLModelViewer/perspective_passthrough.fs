#version 150

in vec4 projectedPosition;

out vec4 outColor;

uniform float nearZ;
uniform float farZ;

void main()
{
    outColor = vec4(1.0);
}
