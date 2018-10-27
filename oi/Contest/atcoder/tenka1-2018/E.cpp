// Fake!
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 2000
#define S 1000

static int H, W;
static int s1[NMAX + 10][NMAX + 10], s2[NMAX + 10][NMAX + 10];
static char buf[NMAX + 10];

#define S1(i, j) s1[S + (i)][S + (j)]
#define S2(i, j) s2[S + (i)][S + (j)]

inline i64 cnt(int x, int y, int r) {
    return S1(x - r, y) - S1(x, y - r) +
           S1(x + 1, y + r - 1) - S1(x + r + 1, y - 1) +
           S2(x, y + r) - S2(x - r, y) +
           S2(x + r - 1, y - 1) - S2(x - 1, y - r - 1);
}

inline i64 c2(i64 n) {
    return n * (n - 1) >> 1;
}

int main() {
    scanf("%d%d", &H, &W);
    i64 n = 0;
    for (int i = 1; i <= H; i++) {
        scanf("%s", buf + 1);
        for (int j = 1; j <= W; j++)
            if (buf[j] == '#') {
                S1(i, j) = S2(i, j) = 1;
                n++;
            }
    }
    for (int i = 1; S + i <= NMAX; i++) for (int j = 1; S + j <= NMAX && S + i - j + 1 >= 1; j++)
        S1(i - j + 1, j) += S1(i - j + 2, j - 1);
    for (int i = 1 - S; S + i <= NMAX; i++) for (int j = 1; S + j <= NMAX && S + i + j - 1 <= NMAX; j++)
        S2(i + j - 1, j) += S2(i + j - 2, j - 1);

    i64 A = 0, B = 0;
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) for (int r = 1; r <= H + W; r++) {
        i64 p = cnt(i, j, r);
        A += c2(p);
        B += (n - 1 - p) * p;
    }
    printf("%lld\n", (2 * A - B) / 6);

    return 0;
}
