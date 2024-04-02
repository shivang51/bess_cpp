#version 440 core

layout(vertices = 4) out;

struct Vertex {
    vec3 color;
    vec2 texCoord;
    int textureIndex;
};

in Vertex v_info[];
out Vertex tc_info[];

void main()
{
    gl_TessLevelOuter[0] = 1;
    gl_TessLevelOuter[1] = 16;

    tc_info[gl_InvocationID] = v_info[gl_InvocationID];
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

