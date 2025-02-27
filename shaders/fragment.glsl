#version 410 core
in float vAlpha;
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.84, 0.0, vAlpha);
}
