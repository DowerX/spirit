#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normCoord;
layout(location = 2) in vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 in_normal;
out vec2 tex_coord;
out vec3 frag_pos;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  frag_pos = vec3(model * vec4(aPos, 1.0));
  in_normal = normCoord;
  tex_coord = textCoord;
}