#version 460 core

in vec2 TexCoord;
in flat float TexIndex;

out vec4 OutColor;

uniform sampler2D u_TextureSlots[16];

void main()
{
    vec4 color = vec4(1.0);


    switch (int(TexIndex))
    {
        case  0: color *= texture(u_TextureSlots[ 0], TexCoord.xy); break;
        case  1: color *= texture(u_TextureSlots[ 1], TexCoord.xy); break;
        case  2: color *= texture(u_TextureSlots[ 2], TexCoord.xy); break;
        case  3: color *= texture(u_TextureSlots[ 3], TexCoord.xy); break;
        case  4: color *= texture(u_TextureSlots[ 4], TexCoord.xy); break;
        case  5: color *= texture(u_TextureSlots[ 5], TexCoord.xy); break;
        case  6: color *= texture(u_TextureSlots[ 6], TexCoord.xy); break;
        case  7: color *= texture(u_TextureSlots[ 7], TexCoord.xy); break;
        case  8: color *= texture(u_TextureSlots[ 8], TexCoord.xy); break;
        case  9: color *= texture(u_TextureSlots[ 9], TexCoord.xy); break;
        case 10: color *= texture(u_TextureSlots[10], TexCoord.xy); break;
        case 11: color *= texture(u_TextureSlots[11], TexCoord.xy); break;
        case 12: color *= texture(u_TextureSlots[12], TexCoord.xy); break;
        case 13: color *= texture(u_TextureSlots[13], TexCoord.xy); break;
        case 14: color *= texture(u_TextureSlots[14], TexCoord.xy); break;
        case 15: color *= texture(u_TextureSlots[15], TexCoord.xy); break;
    }

    OutColor = color;

}