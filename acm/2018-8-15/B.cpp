// #define NDEBUG
#include <cassert>
#include <cstdio>

#ifndef NDEBUG
#define DEBUG(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__)
#else
#define DEBUG(...)
#endif

#define NMAX 5000

enum Verdict {
    FAR = 1, NEAR = 2, SAME = 4
};

void left() {
    puts("left");
    fflush(stdout);
}

void right() {
    puts("right");
    fflush(stdout);
}

Verdict shit() {
    puts("forward");
    fflush(stdout);
    char buf[32];
    scanf("%s", buf);
    if (buf[0] == 'f') return FAR;
    else if (buf[0] == 'c') return NEAR;
    return SAME;
}

void fuck() {
    puts("dig");
    fflush(stdout);
}

void back() {
    left(); left();
    shit();
}

static int str[NMAX + 10], pre[NMAX + 10], n;

int main() {
    while (true) {
        int d;
        for (d = 0; d < 4; d++) {
            Verdict v = shit();
            if (v == NEAR || v == SAME) break;
            back();
            right();
        }
        if (d == 4) break;
    }
    DEBUG("%s", "Stage 1 accomplished.");
    int mask = 0, j = 0;
    while (true) {
        int c = shit();
        str[n++] = c;
        mask |= c;
        if (n == 1) continue;
        while (j && str[j] != c) j = pre[j - 1];
        if (str[j] == c) j++;
        pre[n - 1] = j;
        if ((mask & 3) == 3 && j >= (n + 1) / 2) break;
    }
    DEBUG("n = %d", n);
    int p, q;
    for (p = 0; str[p] == FAR || str[p] == SAME; p++) ;
    for (q = p; str[q] == NEAR || str[q] == SAME; q++) ;
    DEBUG("p = %d, q = %d", p, q);
    if (p < q - p) for (int i = 0; i < q; i++) shit();
    fuck();
    return 0;
}
