#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000

static int n;
static char S[NMAX + 10], T[NMAX + 10];

inline bool chk(int i, const char *t) {
    return S[i] == t[0] && T[i] == t[1];
}

int main() {
    scanf("%d%s%s", &n, S + 1, T + 1);
    int A = 0, B = 0, C = 0, D = 0;
    for (int i = 1; i <= n; i++) {
        A += chk(i, "00");
        B += chk(i, "01");
        C += chk(i, "10");
        D += chk(i, "11");
    }
    for (int b = 0; b <= B; b++) for (int c = 0; c <= C; c++) {
        int d = B + D - b - c;
        if (d % 2) continue;
        d >>= 1;
        if (d < 0 || d > D) continue;
        int a = n / 2 - b - c - d;
        if (a < 0 || a > A) continue;
        for (int i = 1; i <= n; i++) {
            if (a && chk(i, "00")) printf("%d ", i), a--;
            else if (b && chk(i, "01")) printf("%d ", i), b--;
            else if (c && chk(i, "10")) printf("%d ", i), c--;
            else if (d && chk(i, "11")) printf("%d ", i), d--;
        }
        return 0;
    }
    puts("-1");
    return 0;
}
