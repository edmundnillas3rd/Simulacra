#version 460 core

in vec4 FragColor;
out vec4 OutColor;

void main()
{
    OutColor = vec4(FragColor);
}