#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in float aTexIndex;

// layout (std140) uniform ViewProjMat
// {
//     mat4 ViewProjectionMatrix;
// };

out Tex_Data
{
    vec3 Position;
    vec4 Color;
    vec2 TexCoord;
    float TexIndex;
} tex_out;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    
    tex_out.Color = aColor;
    tex_out.TexCoord = aTex;
    tex_out.TexIndex = aTexIndex;
}

#shader fragment
#version 460 core

in Tex_Data
{
    vec3 Position;
    vec4 Color;
    vec2 TexCoord;
    float TexIndex;
} tex_in ;

out vec4 OutColor;

layout (binding = 0) uniform sampler2D u_Texture[8];

void main()
{
    vec4 color = tex_in.Color;

    switch (int(tex_in.TexIndex))
    {
        case 0: color *= texture(u_Texture[0], tex_in.TexCoord); break;
        case 1: color *= texture(u_Texture[1], tex_in.TexCoord); break;
        case 2: color *= texture(u_Texture[2], tex_in.TexCoord); break;
        case 3: color *= texture(u_Texture[3], tex_in.TexCoord); break;
        case 4: color *= texture(u_Texture[4], tex_in.TexCoord); break;
        case 5: color *= texture(u_Texture[5], tex_in.TexCoord); break;
        case 6: color *= texture(u_Texture[6], tex_in.TexCoord); break;
        case 7: color *= texture(u_Texture[7], tex_in.TexCoord); break;
        // case 8: OutColor = texture(u_Texture8, tex_in.TexCoord); break;
        // case 9: OutColor = texture(u_Texture9, tex_in.TexCoord); break;
        // case 10: OutColor = texture(u_Texture1, tex_in.TexCoord); break;
        // case 11: OutColor = texture(u_Texture11, tex_in.TexCoord); break;
        // case 12: OutColor = texture(u_Texture12, tex_in.TexCoord); break;
        // case 13: OutColor = texture(u_Texture13, tex_in.TexCoord); break;
        // case 14: OutColor = texture(u_Texture14, tex_in.TexCoord); break;
        // case 15: OutColor = texture(u_Texture15, tex_in.TexCoord); break;
    }                   
    OutColor = color;
} 