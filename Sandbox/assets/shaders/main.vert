#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in float a_TexIndex;

uniform mat4 u_ViewProjMat;

out vec2 TexCoord; 
out flat float TexIndex;

void main()
{
    gl_Position = u_ViewProjMat * vec4(a_Position, 1.0);
    TexCoord = a_TexCoord;
    TexIndex = a_TexIndex;
}