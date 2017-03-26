// #define NDEBUG

#define NAME "b"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define MOD 1000000007
#define NMAX 100

typedef long long i64;

namespace PhiPresum {

#define TABLE_SIZE 1458337
struct HashTable {
    void insert(int key, i64 val) {
        int pos = key % TABLE_SIZE;
        bucket[pos].push_back(make_pair(key, val));
    }

    i64 query(int key) {
        int pos = key % TABLE_SIZE;
        for (size_t i = 0; i < bucket[pos].size(); i++) {
            Data &d = bucket[pos][i];
            if (d.first == key)
                return d.second;
        }

        return -1;
    }

    typedef pair<int, i64> Data;
    vector<Data> bucket[TABLE_SIZE];
} tb;

#define SMAX 20000000

static int cnt;
static bool marked[SMAX + 10];
static int primes[SMAX + 10];
static i64 phi[SMAX + 10];

void initialize() {
    phi[1] = 1;
    for (int i = 2; i <= SMAX; i++) {
        if (!marked[i]) {
            primes[++cnt] = i;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= cnt && i * primes[j] <= SMAX; j++) {
            int p = primes[j];
            marked[i * p] = true;

            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else
                phi[i * p] = phi[i] * (p - 1);
        }
    }

    for (int i = 1; i <= SMAX; i++) {
        phi[i] += phi[i - 1];
    }
}

i64 evaluate(int n) {
    if (n <= SMAX)
        return phi[n];

    i64 ret = tb.query(n);
    if (ret >= 0)
        return ret;

    ret = (i64) n * (n + 1) / 2 % MOD;
    int last = 2;
    for (int i = 2; i <= n; i = last + 1) {
        last = n / (n / i);
        ret -= (last - i + 1) * evaluate(n / i);
        ret %= MOD;
    }

    tb.insert(n, ret);
    return ret;
}

};

static int t, n, k;
static int f[NMAX + 10][NMAX + 10][NMAX + 10];

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

void initialize() {
    scanf("%d", &t);
}

inline void add(int &dest, int src) {
    dest += src;
    if (dest >= MOD)
        dest -= MOD;
}

int dp(int i, int j, int g) {
    if (i == 0)
        return g == 1;
    if (f[i][j][g])
        return f[i][j][g];

    int &ret = f[i][j][g];
    for (int v = 1; v <= j; v++) {
        add(ret, dp(i - 1, v, gcd(v, g)));
    }

    return ret;
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();
    PhiPresum::initialize();

    while (t--) {
        scanf("%d%d", &n, &k);

        if (k == 2)
            printf("%lld\n", (PhiPresum::evaluate(n) + MOD) % MOD);
        else {
            memset(f, 0, sizeof(f));
            printf("%d\n", dp(k, n, 0));
        }
    }

    return 0;
}
