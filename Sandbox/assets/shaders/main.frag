#version 460 core

in vec2 TexCoord;
out vec4 OutColor;

uniform sampler2D s_TextureSlots[16];

void main()
{
    // OutColor = Color;
    OutColor = texture(s_TextureSlots[0], TexCoord.xy);
}