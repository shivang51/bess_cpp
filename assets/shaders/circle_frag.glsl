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
    float thickness = 0.01;
    float r = 0.5f;

    vec3 col = v_FragColor;

    float alpha = smoothstep(r, r - 0.002, length(uv));

    if (alpha == 0.f) discard;

    bool selected = v_TextureIndex == id;

    r -= thickness;
    float a = smoothstep(r, r - 0.002, length(uv));
    col = mix(col, selected ? vec3(.8, 0.3, 0.3) : vec3(0.1f), a);

    fragColor = vec4(col, alpha);
    fragColor1 = v_TextureIndex;
}
