#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;

out vec3 outColor;
out vec2 outTexcoord;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
    outColor = color;
    outTexcoord = vec2(texcoord.x, 1.0 - texcoord.y);
    gl_Position = projection * view * model * vec4(position, 1.0);
}
