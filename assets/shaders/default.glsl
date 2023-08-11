#shader vertex
#version 460 core

void main()
{
    gl_Position = vec4(1.0, 1.0, 1.0, 1.0);
}

#shader fragment
#version 460 core

out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}