#define NDEBUG

#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#ifndef NDEBUG
#include <chrono>
using namespace std::chrono;
#endif

#define NMAX 5000000
#define HNMAX 100000
#define KMAX 200
#define MOD 1000000007
#define INV2 500000004
#define INV3 333333336
#define INV6 166666668

typedef long long i64;

inline i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; k >>= 1, a = a * a % MOD)
        if (k & 1) r = r * a % MOD;
    return r;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a <= -MOD) a += MOD;
}

static bool _initialized;
static int _cnt;
static i64 _fi[KMAX + 10], _tmp[KMAX + 10];
struct PowerSeries {
    static void init() {
        _fi[0] = 1;
        for (int i = 2; i <= KMAX + 1; i++) _fi[0] = _fi[0] * i % MOD;
        _fi[KMAX + 1] = qpow(_fi[0], MOD - 2);
        for (int i = KMAX; i >= 0; i--) _fi[i] = _fi[i + 1] * (i + 1) % MOD;
        _initialized = true;
    }
    int K; i64 *f;
    PowerSeries() : PowerSeries(_cnt++) {}
    PowerSeries(int _K) : K(_K) {
        if (!_initialized) init();
        f = new i64[K + 2]; f[0] = 0;
        for (int i = 1; i <= K + 1; i++) f[i] = (f[i - 1] + qpow(i, K)) % MOD;
    }
    ~PowerSeries() { delete[] f; }
    i64 operator()(i64 n) const {
        n %= MOD; _tmp[K + 2] = 1;
        for (int i = K + 1; i >= 1; i--) _tmp[i] = _tmp[i + 1] * (n - i) % MOD;
        i64 ret = 0, pre = 1;
        for (int i = 0, b = K & 1 ? 1 : -1; i <= K + 1; i++, b = -b) {
            ret = (ret + b * f[i] * pre % MOD * _tmp[i + 1] % MOD * _fi[i] % MOD * _fi[K + 1 - i]) % MOD;
            pre = pre * (n - i) % MOD;
        } return ret;
    }
    i64 eval(i64 n) const { return (*this)(n); }
};

static PowerSeries F[KMAX + 1];
static bool mark[NMAX + 10];
static int pr[NMAX + 10], cnt, phi[NMAX + 10];
static signed char mu[NMAX + 10];
static i64 pw[HNMAX + 10], n;

static i64 F0[HNMAX + 10], F1[HNMAX + 10];
inline i64 Fp(i64 m, int K) {
    i64 &ret = m <= HNMAX ? F0[m] : F1[n / m];
    if (ret) return ret;
    return ret = F[K](m);
}

static int G0[NMAX + 10], G1[NMAX + 10];
inline i64 c2(i64 x) {
    x %= MOD;
    return x * (x + 1) % MOD * (2 * x + 1);
}
inline i64 G(i64 m) {
    if (m <= NMAX) return G0[m];
    int &ret = G1[n / m];
    if (ret) return ret;
    ret = m % MOD;
    ret = i64(ret) * (ret + 1) % MOD * INV2 % MOD;
    ret = i64(ret) * ret % MOD;
    for (i64 i = 2, l; i <= m; i = l + 1) {
        i64 p = m / i;
        l = m / p;
        //add(ret, (F[2](i - 1) - F[2](l)) * G(p) % MOD);
        ret = (ret + (c2(i - 1) - c2(l)) % MOD * INV6 % MOD * G(p)) % MOD;
    }
    return ret;
}

int main() {
#ifndef NDEBUG
    auto t1 = high_resolution_clock::now();
#endif
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= NMAX; i++) {
        if (!mark[i]) {
            pr[++cnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int j = 1; pr[j] * i <= NMAX; j++) {
            int t = pr[j] * i;
            mark[t] = true;
            if (i % pr[j]) {
                mu[t] = -mu[i];
                phi[t] = phi[i] * (pr[j] - 1);
            } else {
                mu[t] = 0;
                phi[t] = phi[i] * pr[j];
                break;
            }
        }
    }
    for (int i = 1; i <= NMAX; i++)
        G0[i] = (G0[i - 1] + i64(i) * i % MOD * phi[i]) % MOD;
#ifndef NDEBUG
    auto t2 = high_resolution_clock::now();
    printf("setup: %.2lf\n", duration<double>(t2 - t1).count());
#endif

    int T;
    scanf("%d", &T);
    while (T--) {
#ifndef NDEBUG
        t1 = high_resolution_clock::now();
#endif
        memset(G1, 0, sizeof(G1));
        memset(F0, 0, sizeof(F0));
        memset(F1, 0, sizeof(F1));
        int K;
        scanf("%lld%d", &n, &K);
        pw[1] = 1;
        for (int i = 2; i <= HNMAX; i++) {
            if (!mark[i]) pw[i] = qpow(i, K + 1);
            for (int j = 1; pr[j] * i <= HNMAX; j++) {
                int t = pr[j] * i;
                pw[t] = pw[i] * pw[pr[j]] % MOD;
                if (i % pr[j] == 0) break;
            }
        }
#ifndef NDEBUG
        t2 = high_resolution_clock::now();
        printf("prepare: %.2lf\n", duration<double>(t2 - t1).count());
#endif

#ifndef NDEBUG
        t1 = high_resolution_clock::now();
#endif
        static i64 H0[HNMAX + 10], H1[HNMAX + 10];
        i64 d;
        for (d = 1; d * d <= n; d++) {
            H0[d] = Fp(d, K + 1);
            H1[d] = Fp(n / d, K + 1);
        }
        for (int i = 1, j; pr[i] < d; i++) {
            i64 p2 = i64(pr[i]) * pr[i], ph = H0[pr[i] - 1];
            for (j = 1; j * pr[i] < d; j++)
                H1[j] = (H1[j] - pw[pr[i]] * (H1[j * pr[i]] - ph)) % MOD;
            for ( ; j * p2 <= n && j < d; j++)
                H1[j] = (H1[j] - pw[pr[i]] * (H0[n / j / pr[i]] - ph)) % MOD;
            for (j = d - 1; j >= p2; j--)
                H0[j] = (H0[j] - pw[pr[i]] * (H0[j / pr[i]] - ph)) % MOD;
        }
#ifndef NDEBUG
        t2 = high_resolution_clock::now();
        printf("eratos: %.2lf\n", duration<double>(t2 - t1).count());
#endif

#ifndef NDEBUG
        t1 = high_resolution_clock::now();
#endif
        i64 ans = 0;
        for (i64 i = 1; i < d; i++)
            add(ans, (G(i) * (H1[i] - (i + 1 == d ? H0[n / d] : H1[i + 1]))) % MOD);
#ifndef NDEBUG
        t2 = high_resolution_clock::now();
        printf("part 1: %.2lf\n", duration<double>(t2 - t1).count());
#endif

#ifndef NDEBUG
        t1 = high_resolution_clock::now();
#endif
        for (int i = 1; d * pr[i] <= n; i++)
            add(ans, pw[pr[i]] * G(n / pr[i]) % MOD);
        if (ans < 0) ans += MOD;
#ifndef NDEBUG
        t2 = high_resolution_clock::now();
        printf("part 2: %.2lf\n", duration<double>(t2 - t1).count());
#endif

        printf("%lld\n", ans);
        /*
        i64 std = 0;
        for (int i = 1; pr[i] <= n; i++) add(std, pw[pr[i]] * G(n / pr[i]) % MOD);
        if (std < 0) std += MOD;
        fprintf(stderr, "std = %lld\n", std);
        */
    }
    return 0;
}
