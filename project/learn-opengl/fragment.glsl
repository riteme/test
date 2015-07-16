#version 150

in vec3 vertexColor;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main() { outColor = texture(tex, Texcoord) * vec4(vertexColor, 1.0); }
