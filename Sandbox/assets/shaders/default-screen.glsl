#shader vertex
#version 460 core
void main(void)
{
    gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
}

#shader fragment
#version 460 core
out vec4 color;

void main()
{
    color = vec4(0.0, 0.8, 1.0, 1.0);
} 