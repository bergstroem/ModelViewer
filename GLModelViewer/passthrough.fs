#version 150

in vec2 uv;

out vec4 outColor;

uniform sampler2D color_sampler;

void main()
{
    outColor = texture(color_sampler, uv);
}
