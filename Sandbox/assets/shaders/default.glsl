#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 transform;

out vec2 OutTex;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    OutTex = aTex;
}

#shader fragment
#version 460 core

in vec2 OutTex;

out vec4 color;

uniform sampler2D screenTexture;

void main()
{
    color = texture(screenTexture, OutTex);
} 