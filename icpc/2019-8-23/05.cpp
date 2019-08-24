#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 1000000007
#define INV2 500000004
#define INV6 166666668
#define INF 0x3f3f3f3f

template <typename T>
inline void add(T &a, i64 b) {
    a = (a + b) % MOD;
}

#define S 2300000
static int pc, pr[S + 10];

inline i64 c2(i64 n) { return n * (n + 1) % MOD * INV2 % MOD; }
inline i64 c3(i64 n) { return n * (n + 1) % MOD * (2 * n + 1) % MOD * INV6 % MOD; }

static int N;
static int P0[S + 10], P1[S + 10];
int Phi(int n) {  // 杜教筛
    if (n <= S) return P0[n];
    int p = N / n;
    if (P1[p] < INF) return P1[p];
    int &r = P1[p] = c3(n);
    for (int i = 2, l; i <= n; i = l + 1) {
        p = n / i;
        l = n / p;
        add(r, -(c2(l) - c2(i - 1)) * Phi(p));
    }
    return r;
}

static int M0[S + 10], M1[S + 10];
int Mu(int n) {  // 杜教筛
    if (n <= S) return M0[n];
    int p = N / n;
    if (M1[p] < INF) return M1[p];
    int &r = M1[p] = 1;
    for (int i = 2, l; i <= n; i = l + 1) {
        int p = n / i;
        l = n / p;
        add(r, -(c2(l) - c2(i - 1)) * Mu(p));
    }
    return r;
}

int main() {
    int T;
    scanf("%d", &T);
    P0[1] = 1;  // 线性筛
    M0[1] = 1;
    for (int i = 2; i <= S; i++) {
        if (!P0[i]) {
            pr[pc++] = i;
            P0[i] = i - 1;
            M0[i] = -1;
        }
    for (int j = 0; pr[j] * i <= S; j++) {
        int p = pr[j];
        if (i % p) {
            P0[i * p] = P0[i] * (p - 1);
            M0[i * p] = -M0[i];
        } else {
            P0[i * p] = P0[i] * p;
            M0[i * p] = 0;
            break;
    }}}
    for (int i = 1; i <= S; i++) {
        P0[i] = (P0[i - 1] + i64(i) * P0[i]) % MOD;
        M0[i] = (M0[i - 1] + i64(i) * M0[i]) % MOD;
    }

    while (T--) {
        i64 n, a, b;
        scanf("%lld%lld%lld", &n, &a, &b);
        if (n > S) {
            memset(P1, 0x3f, sizeof(P1));
            memset(M1, 0x3f, sizeof(M1));
        }
        N = n;
        i64 ans = (2 * Phi(n) - 1) % MOD;
        for (int i = 1, l; i <= n; i = l + 1) {
            int p = n / i;
            l = n / p;
            add(ans, -i64(Mu(l) - Mu(i - 1)) * p % MOD * p % MOD * (p + 1) % MOD * INV2);
        }
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
