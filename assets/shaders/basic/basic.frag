#version 330 core

in vec3 norm_c;
in vec2 text_c;

uniform sampler2D texture0;

out vec4 FragColor;

void main() {
  FragColor = mix(texture(texture0, text_c), vec4(norm_c, 1.0f), 0.7 * sqrt((0.5 - text_c.x) * (0.5 - text_c.x) + (0.5 - text_c.y) * (0.5 - text_c.y)));
}