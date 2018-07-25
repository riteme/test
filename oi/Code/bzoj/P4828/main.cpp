#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>

#include <algorithm>

using namespace std;

#define NMAX 200
#define INFTY 0x3f3f3f3f

typedef long long i64;

static int n, m, mc;
static int a[NMAX + 10];
static int w[NMAX + 10];
static int f[NMAX + 10][NMAX + 10];
static int minday[NMAX + 10];

inline void chkmin(int &dest, int src) {
    if (src < dest)
        dest = src;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &mc);

    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", w + i);
    }

    memset(f, 0x3f, sizeof(f));
    memset(minday, 0x3f, sizeof(minday));
    f[1][mc] = 0;
    for (int i = 1; i < n; i++) {
        for (int c = 0; c <= mc; c++) {
            if (f[i][c] >= INFTY)
                continue;
            if (c >= a[i + 1])
                chkmin(f[i + 1][c - a[i + 1]], f[i][c]);
            if (min(mc, c + w[i]) >= a[i + 1])
                chkmin(f[i + 1][min(mc, c + w[i]) - a[i + 1]], f[i][c] + 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        int mind = INFTY;
        for (int c = 0; c <= mc; c++) {
            chkmin(mind, f[i][c]);
        }

        for (int j = 1; j <= i - mind; j++) {
            chkmin(minday[j], i);
        }
    }
}

#define CHECK(statement) if (statement) return true;

bool dfs(int day, int cnt, i64 F, i64 L, i64 T) {
    if (day + T <= n && minday[day + T] <= n)
        return true;
    if (minday[day] > n)
        return false;

    if (cnt) {
        CHECK(dfs(day + 1, cnt, F, L + 1, T));
        if (L > 1 && F * L <= T)
            CHECK(dfs(day + 1, cnt, F * L, L, T));
        if (F <= T)
            CHECK(dfs(day + 1, cnt - 1, 1, 0, T - F));
    }

    return false;
}

int main() {
    initialize();

    i64 t;
    while (m--) {
        scanf("%lld", &t);
        puts(dfs(1, 2, 1, 0, t) ? "1" : "0");
    }

    return 0;
}

