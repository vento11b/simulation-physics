#version 330 core

in vec3 vColor;
out vec4 FragColor;

void main() {
   FragColor = vec4(vColor.x/255, vColor.y/255, vColor.z/255, 1.0f);
}