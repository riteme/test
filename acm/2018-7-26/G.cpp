#include <cstdio>

#define TARGET 200

static int H[10];
static char name[2000];
static int cnt, pos[2000];

inline void put(char s, int p) {
    name[cnt] = s;
    pos[cnt++] = p;
}

int main() {
    for (int i = 0; i <= 9; i++)
        scanf("%d", H + i);
    for (int i = 0 ; i <= 8; i++) {
        while (H[i] % 4) {
            H[i + 1]++;
            H[i] += 3;
            put('G', i + 1);
        }
        while (H[i] < TARGET) {
            H[i] += 4;
            put('A', i + 1);
        }
    }
    if (H[9] % 4 == 2) {
        H[9] += 3;
        H[8]++;
        put('E', 9);
    }
    while (H[9] < H[8]) {
        H[9] += 4;
        put('A', 10);
    }
    while (H[7] < H[8]) {
        put('B', 1);
        put('B', 5);
        H[7]++;
    }

    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
        printf("%c %d\n", name[i], pos[i]);
    return 0;
}
