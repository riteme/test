#version 330 core

in vec2 pos;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;

uniform mat4 trans;

void main() {
    Color = color;
    Texcoord = texcoord;
    gl_Position = vec4(pos, 0.0, 1.0);
}
