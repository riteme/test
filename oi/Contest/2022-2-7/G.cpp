#include <cstdio>

int main() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%d ", __builtin_popcount(i & j) % 2);
        }
        puts("");
    }
    return 0;
}
