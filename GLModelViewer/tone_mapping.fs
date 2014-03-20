#version 150

in vec2 uv;

out vec4 outColor;

uniform sampler2D color_sampler;

uniform float exposure;

#define A 0.15
#define B 0.50
#define C 0.10
#define D 0.20
#define E 0.02
#define F 0.30
#define W 11.2

vec4 tonemap(vec4 x) {
    return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

void main()
{
    // Account for gamma (2.2)
    vec4 texColor = texture(color_sampler, uv);
    if(texColor.w == 0.0) {
        discard;
    }
    texColor *= exposure;
    float ExposureBias = 0.2f;
    vec4 curr = tonemap(ExposureBias*texColor);
    
    vec4 whiteScale = 1.0f/tonemap(vec4(W));
    vec4 color = curr*whiteScale;
    
    // Account for gamma (2.2)
    outColor = vec4(pow(color,vec4(1/2.2)));
}
