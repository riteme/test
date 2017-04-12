#define rson(n) ((n << 1) | 1)

// int rson(int n) {
//     return (n << 1) | 1;
// }

int main() {
    int sum = 0;
    for (int i = 1; i <= 100000000; i++) {
        sum += rson(i);
    }

    return 0;
}
