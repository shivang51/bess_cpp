#version 460 core

in vec3 a_vertex;
in vec3 a_Color;

out vec3 v_FragPos;
out vec3 v_FragColor;

void main() {
    v_FragPos = a_vertex;
    v_FragColor = a_Color;
    gl_Position = vec4(a_vertex, 1.0);
}
