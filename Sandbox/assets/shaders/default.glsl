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
    // Index into our array using gl_VertexID
    
    gl_Position = vertices[gl_VertexID] + offset;
    vs_out.color = color;
}

#shader tessellation-control
#version 460 core
layout (vertices = 3) out;

void main(void)
{
    // Only if I am invocation 0 ...
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 5.0;
        gl_TessLevelOuter[0] = 5.0;
        gl_TessLevelOuter[1] = 5.0;
        gl_TessLevelOuter[2] = 5.0;
    }
    // Everybody copies their input to their output
    gl_out[gl_InvocationID].gl_Position =
        gl_in[gl_InvocationID].gl_Position;
}

#shader tessellation-evaluation
#version 460 core

layout (triangles, equal_spacing, cw) in;
void main(void)
{
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
                   gl_TessCoord.y * gl_in[1].gl_Position +
                   gl_TessCoord.z * gl_in[2].gl_Position);
}

#shader geometry
#version 460 core

layout (triangles) in;
layout (points, max_vertices = 3) out;

void main(void)
{
    int i;
    for (i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
}

#shader fragment
#version 460 core

// in VS_OUT {
//     vec4 color;
// } fs_in;


out vec4 color;

void main()
{
    color = vec4(0.0, 0.8, 0.5, 1.0);
}