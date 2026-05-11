#version 330 core

layout (location = 0) in vec2 aPos;

out vec3 vColor;

uniform vec3 color;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
   gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
   vColor = color;
}