// void add() {
//     long a, b;
//     a += b;
// }

// long switch_eg(long x, long y, long z) {
//     switch (x) {
//         case 1:
//             y += z;
//         case 2:
//             y -= z;
//             break;
//         case 5:
//             y *= z;
//         case 6:
//         case 7:
//             y /= z;
//             break;
//         default:
//             y &= z;
//             break;
//     }
//     return y;
// }

// long foo() {
//     int a = 123;
//     long b = a;
//     return b;
// }

#include <stdint.h>

uint64_t mul(uint16_t x, uint16_t y) {
    uint32_t z = x * y;
    return z;
}