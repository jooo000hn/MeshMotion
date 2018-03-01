#version 430
layout(location = 1) uniform float iTime;
layout(location = 2) uniform vec2 iResolution;
layout(location = 3) uniform vec2 iMouse;
layout(location = 4)uniform vec4 fcolor;

in vec2 texture_coord;
in vec4 normal_coord;
out vec4 fragColor;

void main()
{
    fragColor = vec4(0.8);
}