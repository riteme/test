#version 330 core

in vec3 outColor;
in vec2 outTexcoord;

out vec4 finalColor;

uniform sampler2D texture1;

void main() {
    // finalColor = vec4(outColor, 1.0);
    finalColor = vec4(outColor, 1.0f) * texture(texture1, outTexcoord);
    // finalColor = vec4(texture(texture1, outTexcoord).yzx, 1.0);
}
