#version 150

in vec2 uv;

out vec4 outColor;

uniform sampler2D texture_sampler;
uniform int direction;

const float blurSize = 1.0/512.0;

void main()
{
    vec4 sum = vec4(0.0);
    
        if(direction == 0) {
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x - 4.0*blurSize, uv.y)) - vec4(1.0)) * 0.05;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x - 3.0*blurSize, uv.y)) - vec4(1.0)) * 0.09;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x - 2.0*blurSize, uv.y)) - vec4(1.0)) * 0.12;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x - blurSize, uv.y)) - vec4(1.0)) * 0.15;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x, uv.y)) - vec4(1.0)) * 0.16;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x + blurSize, uv.y)) - vec4(1.0)) * 0.15;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x + 2.0*blurSize, uv.y)) - vec4(1.0)) * 0.12;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x + 3.0*blurSize, uv.y)) - vec4(1.0)) * 0.09;
            sum += max(vec4(0.0), texture(texture_sampler, vec2(uv.x + 4.0*blurSize, uv.y)) - vec4(1.0)) * 0.05;
        } else {
            sum += texture(texture_sampler, vec2(uv.x, uv.y - 4.0*blurSize)) * 0.05;
            sum += texture(texture_sampler, vec2(uv.x, uv.y - 3.0*blurSize)) * 0.09;
            sum += texture(texture_sampler, vec2(uv.x, uv.y - 2.0*blurSize)) * 0.12;
            sum += texture(texture_sampler, vec2(uv.x, uv.y - blurSize)) * 0.15;
            sum += texture(texture_sampler, vec2(uv.x, uv.y)) * 0.16;
            sum += texture(texture_sampler, vec2(uv.x, uv.y + blurSize)) * 0.15;
            sum += texture(texture_sampler, vec2(uv.x, uv.y + 2.0*blurSize)) * 0.12;
            sum += texture(texture_sampler, vec2(uv.x, uv.y + 3.0*blurSize)) * 0.09;
            sum += texture(texture_sampler, vec2(uv.x, uv.y + 4.0*blurSize)) * 0.05;
            sum *= 20;
        }
    
    outColor = sum;
    outColor.a = 1.0;
}