#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 1000000007
#define INV2 500000004

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

#define ACM_BEGIN
#define S 17000000  // for F(10^10)
static int pc, pr[S + 10];
static i64 phi[S + 10];
static unordered_map<i64, i64> dat;
inline void sub(i64 &a, i64 b) { a -= b; if (a < 0) a += MOD; }
inline i64 c2(i64 n) { n %= MOD; return n * (n + 1) % MOD * INV2 % MOD; }
i64 F(i64 n) {  // 杜教筛
    if (n <= S) return phi[n];
    if (dat.count(n)) return dat[n];
    i64 &r = dat[n] = c2(n);
    for (i64 i = 2, l; i <= n; i = l + 1) {
        i64 p = n / i;
        l = n / p;
        sub(r, (l - i + 1) * F(p) % MOD);  // (l - i + 1) % MOD?
    }
    return r;
}
#define ACM_END

int main() {
#define ACM_BEGIN
phi[1] = 1;  // 线性筛
for (int i = 2; i <= S; i++) {
    if (!phi[i]) {
        pr[pc++] = i;
        phi[i] = i - 1;
    }
    for (int j = 0; pr[j] * i <= S; j++) {
        int p = pr[j];
        if (i % p) phi[i * p] = phi[i] * (p - 1);
        else {
            phi[i * p] = phi[i] * p;
            break;
}}}
for (int i = 2; i <= S; i++) add(phi[i], phi[i - 1]);
#define ACM_END
    i64 n;
    scanf("%lld", &n);
    printf("%lld\n", F(n));
    return 0;
}
