#pragma GCC optimize(9)

#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000000

static bool pm[NMAX + 10];
static int pr[NMAX + 10], pc;

static unordered_map<i64, int> mumap;
inline int mu(i64 n) {
    if (mumap.count(n)) return mumap[n];
    int &ret = mumap[n] = 1;
    for (int i = 0; pr[i] * pr[i] <= n; i++) {
        if (n % (pr[i] * pr[i]) == 0) return ret = 0;
        if (n % pr[i] == 0) {
            ret *= -1;
            n /= pr[i];
        }
    }
    if (n > 1) ret *= -1;
    return ret;
}

static unordered_map<i64, i64> fmap;
i64 F(i64 m, i64 n) {
    if (m == 1) return mu(n);
    i64 key = (m << 30) ^ n ^ (n << 40) ^ m;
    if (fmap.count(key)) return fmap[key];
    i64 &ret = fmap[key];
    if (n == 1) {
        for (int i = 1; i <= m; i++) ret += mu(i);
        return ret;
    }
    for (int d = 1; d * d <= n; d++) {
        if (m % d) continue;
        int v = mu(d);
        if (v) ret += v * F(m / d, d);
        if (d * d == m) continue;
        v = mu(m / d);
        if (v) ret += v * F(d, m / d);
    }
    ret *= mu(n);
    return ret;
}

int main() {
    for (int i = 2; i <= NMAX; i++) {
        if (!pm[i]) pr[pc++] = i;
        for (int j = 0; j < pc && pr[j] * i <= NMAX; j++) {
            pm[pr[j] * i] = true;
            if (i % pr[j] == 0) break;
        }
    }
    i64 m, n;
    scanf("%lld%lld", &m, &n);
    printf("%lld\n", F(m, n));
    return 0;
}
