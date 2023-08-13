#shader vertex
#version 460 core

layout (location = 0) in vec4 offset;
layout (location = 1) in vec4 color;

out VS_OUT {
    vec4 color;
} vs_out;


void main()
{
    // Declare a hard-coded array of positions
    const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),
                                    vec4(-0.25, -0.25, 0.5, 1.0),
                                    vec4(0.25, 0.25, 0.5, 1.0));

    const vec4 colors[] = vec4[3](vec4(1.0, 0.0, 0.0, 1.0),
                                  vec4(0.0, 1.0, 0.0, 1.0),
                                  vec4(0.0, 0.0, 1.0, 1.0));

    // Index into our array using gl_VertexID
    
    gl_Position = vertices[gl_VertexID] + offset;
    vs_out.color = colors[gl_VertexID];
}

#shader fragment
#version 460 core

in VS_OUT {
    vec4 color;
} fs_in;


out vec4 color;

void main()
{
    color = fs_in.color;
}