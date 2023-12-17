#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normCoord;
layout(location = 2) in vec2 textCoord;

out vec3 norm_c;
out vec2 text_c;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  // gl_Position = vec4(aPos.x*3/4/10, aPos.yz/10, 1.0);
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  text_c = textCoord;
  norm_c = normCoord;
}