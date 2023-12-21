#version 330 core

#define MAX_LIGHTS 10

in vec3 normal;
in vec2 tex_coord;
in vec3 frag_pos;

uniform vec3 view_pos;
uniform sampler2D texture0;

struct Light {
  vec3 position;
  vec3 color;
  int type;
};

uniform Light[MAX_LIGHTS] lights;
uniform int light_count;

uniform float shininess = 32;
uniform float specular_strenght = 0.5;

out vec4 FragColor;

vec3 calc_light(Light light) {
  vec3 light_dir = normalize(light.position - frag_pos);
  vec3 view_dir = normalize(view_pos - frag_pos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  float diffuse = max(dot(normal, light_dir), 0.0);
  float specular = pow(max(dot(view_dir, reflect_dir), 0.0), shininess) * specular_strenght;

  return (diffuse + specular) * light.color / max(pow(length(light.position - frag_pos), 2), 1);
}

void main() {
  vec3 result = vec3(0);
  for (int i = 0; i < light_count; i++) {
    result += calc_light(lights[i]);
  }

  FragColor = texture(texture0, tex_coord) * vec4(result, 1.0f);
}