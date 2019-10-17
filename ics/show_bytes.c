#include <stdio.h>

typedef unsigned char *byte_ptr;

void show_bytes(byte_ptr start, size_t len) {
    int i;
    for (i = 0; i < len; i++)
        printf("%.2X", start[i]);
    putchar('\n');
}

void show_float(float x) {
    show_bytes((byte_ptr) &x, sizeof(float));
}

void show_float2(float x) {
    union {
        float input;
        unsigned output;
    } data;
    data.input = x;
    printf("%.8X\n", data.output);
}

int main() {
    //float x;
    //scanf("%f", &x);
    //show_float(x);
    //show_float2(x);
    //short sx = -12345;
    //unsigned uy = sx;
    //show_bytes((byte_ptr) &uy, sizeof(unsigned));
    int ix = 0xFFFF8000;
    short sy = ix;
    show_bytes((byte_ptr) &sy, sizeof(short));
    return 0;
}
