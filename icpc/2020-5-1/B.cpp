#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 998244353
#define LMAX 128
#define SIGMA 26

int n, m = 1, K;
char s[LMAX];
int ch[LMAX][SIGMA];
int fail[LMAX];
bool mark[LMAX];

struct Matrix {
    Matrix() {
        memset(v, 0, sizeof(v));
    }

    i64 v[LMAX][LMAX];

    Matrix &operator+=(const Matrix &z) {
        for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            v[i][j] = (v[i][j] + z.v[i][j]) % MOD;
        return *this;
    }

    Matrix &operator*=(const Matrix &z) {
        static i64 c[LMAX][LMAX];
        memset(c, 0, sizeof(c));

        for (int i = 1; i <= m; i++)
        for (int k = 1; k <= m; k++)
        for (int j = 1; j <= m; j++)
            c[i][j] = (c[i][j] + v[i][k] * z.v[k][j]) % MOD;

        memcpy(v, c, sizeof(v));
        return *this;
    }
};

int go(int x, int c) {
    while (x != 1 && !ch[x][c])
        x = fail[x];
    if (ch[x][c])
        x = ch[x][c];
    return x;
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);

        int x = 1;
        for (int j = 0; s[j]; j++) {
            int c = s[j] - 'a';
            if (!ch[x][c])
                ch[x][c] = ++m;
            x = ch[x][c];
        }
        mark[x] = true;
    }

    queue<int> q;
    fail[1] = 1;
    for (int c = 0; c < SIGMA; c++) {
        int x = ch[1][c];
        if (x == 0) continue;
        fail[x] = 1;
        q.push(x);
    }
    do {
        int u = q.front();
        q.pop();

        for (int c = 0; c < SIGMA; c++) if (ch[u][c]) {
            int v = ch[u][c];
            int y = fail[u];
            while (y != 1 && !ch[y][c])
                y = fail[y];
            if (ch[y][c])
                y = ch[y][c];
            fail[v] = y;
            if (mark[y])
                mark[v] = true;
            q.push(v);
        }
    } while (!q.empty());

    for (int i = 1; i <= m; i++) if (mark[i])
    for (int c = 0; c < SIGMA; c++)
        ch[i][c] = i;

    Matrix T;
    for (int i = 1; i <= m; i++)
    for (int c = 0; c < SIGMA; c++)
        T.v[go(i, c)][i]++;

    Matrix R, A = T;
    for (int i = 1; i <= m; i++)
        R.v[i][i] = 1;
    for ( ; K; K >>= 1) {
        if (K & 1) {
            R *= A;
        }
        A *= A;
    }

    i64 ans = 0;
    for (int i = 1; i <= m; i++) if (!mark[i])
        ans = (ans + R.v[i][1]) % MOD;

    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);

    return 0;
}