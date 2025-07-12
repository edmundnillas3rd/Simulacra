#version 460 core

layout (location = 0) in vec3 a_Position;

out vec4 FragColor;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
    FragColor = vec4(0.99, 0.44, 0.66, 1.0);
}