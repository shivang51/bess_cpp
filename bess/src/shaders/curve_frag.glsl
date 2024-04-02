#version 460 core

layout(location = 0) out vec4 fragColor;
layout(location = 1) out int fragColor1;

uniform int u_SelectedObjId;

struct Vertex {
    vec3 color;
    vec2 texCoord;
};
in flat int textureIndex;

in Vertex frag_info;

void main() {
    int id = u_SelectedObjId;

    vec3 c = frag_info.color;

    if (id == textureIndex) {
        c = vec3(1, 0, 0);
    }

    fragColor = vec4(c, 1);

    fragColor1 = textureIndex;
}
