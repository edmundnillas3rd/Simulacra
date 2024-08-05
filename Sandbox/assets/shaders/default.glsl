#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTex;
}

#shader fragment
#version 460 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture1;

void main()
{
    color = texture(texture1, TexCoord);
    // color = vec4(1.0, 1.0, 0.0, 1.0);
} 