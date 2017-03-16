#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;
typedef unsigned int u32;

#define NMAX 2100000
// #define NMAX 100

#define PRIME 2338003
class HashTable {
 public:
    void insert(u32 key, i64 val) {
        bucket[key % PRIME].push_back(make_pair(key, val));
    }

    i64 query(u32 key) {
        u32 pos = key % PRIME;
        for (size_t i = 0; i < bucket[pos].size(); i++) {
            if (bucket[pos][i].first == key)
                return bucket[pos][i].second;
        }

        return -1;
    }

 private:
    typedef pair<u32, i64> Data;
    vector<Data> bucket[PRIME];
};

static bool marked[NMAX + 10];
static int cnt;
static int primes[NMAX + 10];
static i64 phi[NMAX + 10];
static i64 mu[NMAX + 10];
static HashTable tbphi, tbmu;

void initialize() {
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= NMAX; i++) {
        if (!marked[i]) {
            primes[++cnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= cnt && i * primes[j] <= NMAX; j++) {
            int p = primes[j];
            marked[i * p] = true;

            if (i % p == 0) {
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
                break;
            } else {
                mu[i * p] = mu[i] * mu[p];
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }

    for (int i = 1; i <= NMAX; i++) {
        phi[i] += phi[i - 1];
        mu[i] += mu[i - 1];
    }
}

void evaluate(u32 n, i64 &phians, i64 &muans) {
    if (n <= NMAX) {
        phians = phi[n];
        muans = mu[n];
    } else {
        phians = tbphi.query(n);
        if (phians >= 0) {
            muans = tbmu.query(n);
            return;
        }

        phians = (i64) n * ((i64) n + 1) / 2;
        muans = (n >= 1 ? 1 : 0);
        u32 last = 1;
        for (u32 i = 2; i <= n; i = last + 1) {
            last = n / (n / i);
            i64 phisum, musum;
            evaluate(n / i, phisum, musum);
            phians -= (last - i + 1) * phisum;
            muans -= (last - i + 1) * musum;
        }

        tbphi.insert(n, phians);
        tbmu.insert(n, muans);
    }
}

int main() {
    initialize();

    int t;
    scanf("%d", &t);
    while (t--) {
        u32 n;
        scanf("%u", &n);

        i64 ans1, ans2;
        evaluate(n, ans1, ans2);
        printf("%lld %lld\n", ans1, ans2);
    }

    return 0;
}
