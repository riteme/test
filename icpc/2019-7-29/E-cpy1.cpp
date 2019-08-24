#include <cstdio>
#include <cstring>

#include <tr1/unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 10000000
#define HNMAX 100000
#define KMAX 200
#define MOD 1000000007

typedef long long i64;
typedef tr1::unordered_map<i64, i64> Map;

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
            add(ret, b * f[i] * pre % MOD * _tmp[i + 1] % MOD * _fi[i] % MOD * _fi[K + 1 - i] % MOD);
            pre = pre * (n - i) % MOD;
        } return ret;
    }
    i64 eval(i64 n) const { return (*this)(n); }
};

static PowerSeries F[KMAX + 1];
static bool mark[NMAX + 10];
static int pr[NMAX + 10], cnt;
static int mu[NMAX + 10], phi[NMAX + 10];
static i64 pw[NMAX + 10];

static Map F0;
inline i64 Fp(i64 n, int K) {
    Map::iterator it = F0.find(n);
    if (it != F0.end()) return it->second;
    i64 ret = F[K](n);
    F0[n] = ret;
    return ret;
}

static i64 Gp[NMAX + 10];
static Map G0;
inline i64 G(i64 n) {
    if (n <= NMAX) return Gp[n];
    Map::iterator it = G0.find(n);
    if (it != G0.end()) return it->second;
    i64 ret = F[3](n);
    for (i64 i = 2, l; i <= n; i = l + 1) {
        i64 p = n / i;
        l = n / p;
        add(ret, ((F[2](i - 1) - F[2](l)) * G(p)) % MOD);
    }
    return ret;
}

static i64 Hp[HNMAX + 10];
static Map H0[HNMAX + 10];
inline i64 H(int i, i64 n, int K) {
    if (n == 0) return 0;
    if (i == 0) return Fp(n, K + 1);
    Map::iterator it = H0[i].find(n);
    if (it != H0[i].end()) return it->second;
    H0[i][n] = (H(i - 1, n, K) - pw[pr[i]] * pr[i] % MOD * H(i - 1, n / pr[i], K)) % MOD;
    //printf("H(%d, %lld, %d) = %lld\n", i, n, K, H0[i][n]);
    return H0[i][n];
}

inline i64 H(i64 n, int K) {
    int l = 0, r = HNMAX;
    while (l < r) {
        int m = ((l + r) >> 1) + 1;
        if (1LL * pr[m] * pr[m] > n) r = m - 1;
        else l = m;
    }
    return (H(l, n, K) + Hp[pr[l]] - 1) % MOD;
}

int main() {
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
        Gp[i] = (Gp[i - 1] + i * i * phi[i]) % MOD;
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n;
        int K;
        scanf("%lld%d", &n, &K);
        pw[1] = 1;
        for (int i = 2; i <= NMAX; i++) {
            if (!mark[i]) pw[i] = qpow(i, K);
            for (int j = 1; pr[j] * i <= NMAX; j++) {
                int t = pr[j] * i;
                pw[t] = pw[i] * pw[pr[j]] % MOD;
                if (i % pr[j] == 0) break;
            }
        }
        for (int i = 2; i <= HNMAX; i++)
            Hp[i] = (Hp[i - 1] + (mark[i] ? 0 : pw[i] * i)) % MOD;
        for (int i = 1; 1LL * pr[i] * pr[i] <= n; i++) H0[i].clear();
        F0.clear();
        i64 ans = 0, d;
        for (d = 1; d * d <= n; d++)
            add(ans, (G(d) * (H(n / d, K) - H(n / (d + 1), K))) % MOD);
        for (int i = 1; d * pr[i] <= n; i++)
            add(ans, pw[pr[i]] * pr[i] % MOD * G(n / pr[i]) % MOD);
        if (ans < 0) ans += MOD;

        i64 std = 0;
        for (int i = 1; pr[i] <= n; i++) add(std, pw[pr[i]] * pr[i] % MOD * G(n / pr[i]) % MOD);
        if (std < 0) std += MOD;
        fprintf(stderr, "std = %lld\n", std);

        printf("%lld\n", ans);
    }
    return 0;
}
