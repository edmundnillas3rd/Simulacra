#shader vertex
#version 460 core
// This is the default screen to render for framebuffers

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoords = aTex;
}

#shader fragment
#version 460 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 texCol = texture(screenTexture, TexCoords).rgb;
    color = vec4(texCol, 1.0);
} 