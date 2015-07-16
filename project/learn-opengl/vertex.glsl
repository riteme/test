#version 150

in vec2 pos;
in vec3 color;
in vec2 texcoord;

out vec3 vertexColor;
out vec2 Texcoord;

void main() {
    vertexColor = color;
    Texcoord = texcoord;
    gl_Position = vec4(pos, 0.0, 1.0);
}
