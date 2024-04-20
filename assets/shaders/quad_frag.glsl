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
    float r = 0.1f;

    vec3 c = v_FragColor;
    
    float l = length(max(abs(uv) - 0.5 + r, 0.0)) - r;
    float fade = 0.002;
    float alpha = smoothstep(fade, -fade, l);

    if(alpha == 0) discard; 


    if (v_TextureIndex > 0 && v_TextureIndex == id ) {
        float v = smoothstep(fade, -fade, abs(l) - thickness);
        c = mix(c, vec3(0.75), v);
    }

    fragColor = vec4(c, alpha);
    fragColor1 = v_TextureIndex;
}
