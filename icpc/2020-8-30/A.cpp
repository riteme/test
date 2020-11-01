#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long long i64;

int n;
int a[NMAX + 10][NMAX + 10];
int b[NMAX + 10][NMAX + 10];
int c[NMAX + 10][NMAX + 10];
int bit[NMAX + 10];

void add(int x, int v) {
    for ( ; x <= n; x += x & -x) {
        bit[x] += v;
    }
}

int query(int x) {
    int r = 0;
    for ( ; x; x -= x & -x) {
        r += bit[x];
    }
    return r;
}

struct Event {
    int t, x, v;

    bool operator<(const Event &z) const {
        return t < z.t || (t == z.t && v < z.v);
    }
};

int cnt;
Event ev[NMAX * 2 + 10];

i64 scan(int sx, int sy, int len) {
    cnt = 0;
    memset(bit + 1, 0, sizeof(int) * n);
    for (int i = 1; i <= len; i++) {
        int tx = sx + i - 1, ty = sy + i - 1;
        ev[cnt++] = {i, i, +1};
        ev[cnt++] = {i + c[tx][ty], i, -1};
    }
    sort(ev, ev + cnt);

    i64 rax = 0, sum = 0;
    for (int i = 1, j = 0; i <= len; i++) {
        for ( ; j < cnt && ev[j].t == i; j++) {
            add(ev[j].x, ev[j].v);
            sum += ev[j].v;
        }

        int tx = sx + i - 1, ty = sy + i - 1;
        rax += sum - query(i - b[tx][ty]);
    }

    return rax;
}

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        scanf("%d", a[i] + j);
    }

    for (int i = 1; i <= n; i++) {
        b[i][n + 1] = 0;
        c[i][n + 1] = 0;
    }
    for (int j = 1; j <= n; j++) {
        b[n + 1][j] = 0;
        c[n + 1][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            b[i][j] = a[i][j] ? b[i][j - 1] + 1 : 0;
        }
        for (int j = n; j >= 1; j--) {
            c[i][j] = a[i][j] ? c[i][j + 1] + 1 : 0;
        }
    }

    for (int j = 1; j <= n; j++) {
        int s = 0;
        for (int i = 1; i <= n; i++) {
            s = a[i][j] ? s + 1 : 0;
            b[i][j] = min(b[i][j], s);
        }
        s = 0;
        for (int i = n; i >= 1; i--) {
            s = a[i][j] ? s + 1 : 0;
            c[i][j] = min(c[i][j], s);
        }
    }

    i64 ans = 0;
    ans += scan(1, 1, n);
    for (int i = 2; i <= n; i++) {
        ans += scan(i, 1, n - i + 1);
    }
    for (int j = 2; j <= n; j++) {
        ans += scan(1, j, n - j + 1);
    }
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case %d: ", i);
        _main();
    }
    return 0;
}
