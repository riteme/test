#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texGoogle;
uniform sampler2D texBaidu;
uniform float time;

void main() {
    vec4 colGoogle = texture(texGoogle, Texcoord);
    vec4 colBaidu = texture(texBaidu, Texcoord);
    // vec4 mixed = mix(colGoogle, colBaidu, sin(time) / 2.0 + 0.5);
    vec4 mixed;
    if (Texcoord.y < sin(time) / 2.0 + 0.5) {
        mixed = colBaidu;
    } else {
        mixed = colGoogle;
        mixed = texture(texBaidu,
                        vec2(Texcoord.x +
                                 sin(Texcoord.y * 30.0 + time * 5.0) / 100.0,
                             Texcoord.y)) *
                vec4(0.8, 0.8, 0.8, 1.0);
    }
    outColor = mixed * vec4(Color, 1.0);
    // outColor = colBaidu * vec4(Color, 1.0);
    // outColor = colGoogle * vec4(Color, 1.0);
}
