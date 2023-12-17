#version 410 core

in vec3 norm_c;
in vec3 text_c;

out vec4 FragColor;

void main() {
  FragColor = vec4(norm_c, 1.0f);
}