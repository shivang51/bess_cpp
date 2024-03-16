#version 460 core

out vec4 fragColor;

in vec3 v_FragPos;
in vec3 v_FragColor;

void main() {
    fragColor = vec4(v_FragColor, 1.0);
}
