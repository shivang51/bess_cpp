#version 460 core

out vec4 fragColor;

in vec3 v_FragPos;
in vec3 v_FragColor;

uniform vec4 u_color;

void main() {
    fragColor = u_color;
}
