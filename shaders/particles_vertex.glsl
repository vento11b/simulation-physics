#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 instanceModel;
layout (location = 2) in vec3 instanceColor;

out vec3 vColor;

uniform mat4 projection;
uniform mat4 view;

void main() {
   gl_Position = projection * view * instanceModel * vec4(aPos, 0.0, 1.0);
   vColor = instanceColor;
}