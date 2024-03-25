#version 460 core

layout(location = 0) out vec4 fragColor;
layout(location = 1) out int fragColor1;

in vec3 v_FragPos;
in vec2 v_TexCoord;
in vec3 v_FragColor;
in flat int v_TextureIndex;

uniform int u_SelectedObjId;

void main() {
    int id = u_SelectedObjId;

    vec2 uv = v_TexCoord - 0.5;

    vec3 c = v_FragColor;

    if (v_TextureIndex > 0 && v_TextureIndex == id &&
            (abs(uv.x) > 0.48 || abs(uv.y) > 0.48)) {
        c = vec3(0);
    }

    fragColor = vec4(c, 1.f);
    fragColor1 = v_TextureIndex;
}
