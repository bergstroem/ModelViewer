#version 150

in vec2 uv;

out vec4 outColor;

uniform sampler2D color_sampler;

#define A 0.15
#define B 0.50
#define C 0.10
#define D 0.20
#define E 0.02
#define F 0.30
#define W 11.2

vec3 tonemap(vec3 x) {
    return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

vec3 avg_luminance() {
    float i, j;
    vec3 luminance = vec3(0.0);
    
    for(i = 0.0; i < 1.0; i += 0.2) {
        for(j = 0.0; j < 1.0; j += 0.2) {
            luminance += texture(color_sampler, vec2(i, j)).xyz;
        }
    }
    luminance /= 25;
    return vec3(luminance);
}

void main()
{
    // Account for gamma (2.2)
    vec3 texColor = texture(color_sampler, uv).xyz;
    texColor *= 64;//1/tonemap(avg_luminance()).x;
    float ExposureBias = 0.2f;
    vec3 curr = tonemap(ExposureBias*texColor);
    
    vec3 whiteScale = 1.0f/tonemap(vec3(W));
    vec3 color = curr*whiteScale;
    
    // Account for gamma (2.2)
    outColor = vec4(pow(color,vec3(1/2.2)), 1.0);
}
