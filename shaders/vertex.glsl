#version 410 core
layout (location = 0) in vec2 inPos;
layout (location = 1) in float inAlpha;

uniform mat4 uProjection;

out float vAlpha;

void main()
{
    gl_Position = uProjection * vec4(inPos, 0.0, 1.0);
    gl_PointSize = 5.0;
    vAlpha = inAlpha;
}
