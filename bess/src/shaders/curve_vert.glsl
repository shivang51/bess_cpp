
#version 460 core

layout(location = 0) in vec3 a_Vertex;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TextureIndex;

struct Vertex {
    vec3 color;
    vec2 texCoord;
    int textureIndex;
};

out Vertex v_info;

uniform mat4 u_mvp;

void main() {
    v_info.color = a_Color;
    v_info.texCoord = a_TexCoord;
    v_info.textureIndex = a_TextureIndex;
    gl_Position = u_mvp * vec4(a_Vertex, 1.0);
}
