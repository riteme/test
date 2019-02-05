//#define NDEBUG

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 400
#define MOD 1000000007LL
#define INV2 500000004LL

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define clear(arr) rep(j, l, r - 1) rep(k, j, r) arr[j][k] = 0;
#define clear2(arr) rep(j, l, r - 1) rep(k, j, r) arr[k][j] = 0;

typedef long long i64;

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

inline i64 C(int n) {
    return n * (n + 1) * INV2 % MOD;
}

static int n, Q, seq[NMAX + 10], last[NMAX + 10];
static bool mark[NMAX + 10];
static i64 A[NMAX + 10], ans[NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10], g[NMAX + 10][NMAX + 10];
static i64 row[NMAX + 10][NMAX + 10], col[NMAX + 10][NMAX + 10];

#ifndef NDEBUG
void print(i64 f[][NMAX + 10], int l, int r) {
    rep(i, 1, n) fprintf(stderr, mark[i] ? "+" : ".");
    fputc('\n', stderr);
    fprintf(stderr, "l = %d, r = %d\n", l, r);
    fprintf(stderr, "j\\k");
    rep(k, l, r) fprintf(stderr, " %3d", k);
    fputc('\n', stderr);
    rep(j, l, r) {
        fprintf(stderr, " %d ", j);
        rep(k, l, r)
            if (f[j][k]) fprintf(stderr, " %3lld", f[j][k]);
            else fprintf(stderr, "    ");
        fputc('\n', stderr);
    }
}
#else
#define print(...)
#endif

inline void inc(int l, int r, i64 v) {
    if (r < l) return;
    add(ans[l ? l : 1], v);
    add(ans[r + 1], MOD - v);
}

int main() {
    scanf("%d%d", &n, &Q);
    rep(i, 1, n) {
        seq[i] = i;
        scanf("%lld", A + i);
    }
    sort(seq + 1, seq + n + 1, [](int x, int y) { return A[x] > A[y]; });
    i64 p = 1;
    rep(i, 1, Q) p = p * C(n) % MOD;
    rep(i, 1, n) {
        int x = seq[i];
        int l = x, r = x;
        while (l && !mark[l]) l--;
        while (r <= n && !mark[r]) r++;
        i64 delta = A[last[l]] - A[x];
        inc(l + 1, r - 1, f[l][l] * delta % MOD);
        rep(j, l, r) rep(k, j + 2, r) {
            inc(l + 1, j, f[j][k] * delta % MOD);
            inc(k, r - 1, f[j][k] * delta % MOD);
        }
        mark[x] = true;
        inc(x, x, p * A[x] % MOD);
        for (r = x; l <= x; l = r++) {
            while (r <= n && !mark[r]) r++;
            if (l + 1 == r) continue;
            last[l] = x;
            clear(f);
            f[l][r] = 1;
            rep(q, 0, Q - 1) {
                g[l][l] = f[l][l] * C(n) % MOD;
                rep(j, l, r) rep(k, j + 2, r) {
                    add(g[j][k], f[j][k] * (C(j) + C(n - k + 1) + C(k - j - 1)) % MOD);
                    add(g[l][l], f[j][k] * ((j + 1) * (n - k + 2) - 1) % MOD);
                    add(row[j][j + 2], f[j][k] * (n - k + 1) % MOD);
                    add(row[j][k], MOD - f[j][k] * (n - k + 1) % MOD);
                    add(col[k][j + 1], f[j][k] * j % MOD);
                    add(col[k][k - 1], MOD - f[j][k] * j % MOD);
                }
                rep(j, l, r - 1) rep(k, j, r) {
                    add(row[j][k], row[j][k - 1]);
                    add(col[k][j], col[k][j - 1]);
                    f[j][k] = (g[j][k] + row[j][k] + col[k][j]) % MOD;
                }
                clear(g); clear(row); clear2(col);
            }
        }
    }
    rep(i, 1, n) {
        add(ans[i], ans[i - 1]);
        printf("%lld ", ans[i]);
    }

    return 0;
}
