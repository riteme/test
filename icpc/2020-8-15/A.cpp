#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 64

int a[NMAX];
int p[NMAX], r[NMAX], t[NMAX];

void _main() {
    for (int i = 1; i <= 52; i++) {
        scanf("%d", a + i);
        r[i] = i;
    }
    int n, L, R;
    scanf("%d%d%d", &n, &L, &R);
    int len = R - L + 1;
    for (int i = 1; i <= len; i++) {
        p[i] = L + i - 1;
    }
    for (int i = len + 1; i <= R; i++) {
        p[i] = i - len;
    }
    for (int i = R + 1; i <= 52; i++) {
        p[i] = i;
    }

    for ( ; n; n >>= 1) {
        if (n & 1) {
            for (int i = 1; i <= 52; i++) {
                t[i] = r[p[i]];
            }
            memcpy(r, t, sizeof(t));
        }

        for (int i = 1; i <= 52; i++) {
            t[i] = p[p[i]];
        }
        memcpy(p, t, sizeof(t));
    }

    for (int i = 1; i <= 52; i++) {
        printf(i < 52 ? "%d " : "%d\n", a[r[i]]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        _main();
    }
    return 0;
}
