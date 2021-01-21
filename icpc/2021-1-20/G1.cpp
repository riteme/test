#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using u64 = unsigned long long;

constexpr u64 MOD = 1000000007;

int n, m;
int tb[100][100] = {
{0},
{0,2,4,6,10,16,26,42,68,110,178,0},
{0,4,16,36,100,256,676,1764,4624,12100,31684,0},
{0,6,36,32,44,64,104,164,264,424,684,0},
{0,10,100,44,18,14,14,14,14,14,14,0},
{0,16,256,64,14,8,8,8,8,8,8,0},
{0,26,676,104,14,8,8,8,8,8,8,0},
{0,42,1764,164,14,8,8,8,8,8,8,0},
{0,68,4624,264,14,8,8,8,8,8,8,0},
{0,110,12100,424,14,8,8,8,8,8,8,0},
{0,178,31684,684,14,8,8,8,8,8,8,0}
};
bool a[100][100];

bool chk(int i, int j) {
    bool found = false;
    if (i >= 3)
        found |= a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j];
    if (j >= 3)
        found |= a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2];
    if (i >= 3 && j >= 3)
        found |= a[i][j] == a[i - 1][j - 1] && a[i][j] == a[i - 2][j - 2];
    if (i >= 3 && j + 2 <= m)
        found |= a[i][j] == a[i - 1][j + 1] && a[i][j] == a[i - 2][j + 2];
    return !found;
}

int cnt[512];

void dfs(int i, int j) {
    if (i >= n + 1) {
        int A = 0;
        for (int p = 1; p <= n; p++)
        for (int q = 1; q <= m; q++) {
            A |= int(a[p][q]) << ((p - 1) * m + q - 1);
        }
        cnt[A]++;
        return;
    }
    if (j >= m + 1) {
        dfs(i + 1, 1);
        return;
    }

    a[i][j] = 0;
    if (chk(i, j))
        dfs(i, j + 1);
    a[i][j] = 1;
    if (chk(i, j))
        dfs(i, j + 1);
}

void eval(int _n, int _m) {
    n = _n;
    m = _m;
    memset(cnt, 0, sizeof(cnt));
    dfs(1, 1);
}

bool check(int _n, int _m) {
    n = _n;
    m = _m;
    bool ok = true;
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        ok &= chk(i, j);
    }
    return ok;
}

void add(u64 &a, u64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

struct mat {
    u64 a[512][512];

    void reset() {
        memset(a, 0, sizeof(a));
    }

    u64 *operator[](int i) {
        return a[i];
    }

    mat &operator*=(mat &b) {
        u64 c[512][512];
        memset(c, 0, sizeof(c));
        for (int i = 0; i < 512; i++)
        for (int k = 0; k < 512; k++)
        for (int j = 0; j < 512; j++) {
            c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
        }
        memcpy(a, c, sizeof(c));
        return *this;
    }

    mat &operator+=(mat &b) {
        for (int i = 0; i < 512; i++)
        for (int j = 0; j < 512; j++) {
            add(a[i][j], b[i][j]);
        }
        return *this;
    }
};

void qpow(mat &T, mat &R, int k) {
    R.reset();
    for (int i = 0; i < 512; i++) {
        R[i][i] = 1;
    }
    for ( ; k; k >>= 1) {
        if (k & 1)
            R *= T;
        T *= T;
    }
}

mat T, R;

void solve(int n, int m) {
    T.reset();
    int s = 3 * m;
    for (int A = 0; A < (1 << s); A++)
    for (int b = 0; b < (1 << m); b++) {
        for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= m; j++) {
            a[i][j] = (A >> ((i - 1) * m + j - 1)) & 1;
        }
        for (int j = 1; j <= m; j++) {
            a[4][j] = (b >> (j - 1)) & 1;
        }
        int B = (b << (2 * m)) | (A >> m);

        if (check(4, m)) {
            //printf("%d -> %d\n", A, B);
            T[B][A]++;
        }
    }

    eval(3, m);

    qpow(T, R, n - 3);

    u64 ans = 0;
    for (int i = 0; i < (1 << s); i++)
    for (int j = 0; j < (1 << s); j++) {
        ans = (ans + R[i][j] * cnt[j]) % MOD;
    }

    printf("%llu\n", ans);
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n, m;
        scanf("%d%d", &n, &m);

        if (m > n)
            swap(n, m);

        if (m <= 3) {
            solve(n, m);
        } else if (n <= 10 && m <= 10)
            printf("%d\n", tb[n][m]);
        else
            puts("8");
    }
    return 0;
}
