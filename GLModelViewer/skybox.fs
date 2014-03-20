#version 150

uniform samplerCube cube_map;

in vec3 vCubeMap;

out vec4 outColor;

void main()
{
    outColor = texture(cube_map, vCubeMap); //vec4(vCubeMap, 1.0);
}
