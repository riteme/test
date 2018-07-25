// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define KMAX 2000
#define S 5000000
#define MOD 116099

typedef long long i64;

template <typename TPolicy>
struct HashTable {
    typedef typename TPolicy::TKey TKey;
    typedef typename TPolicy::TVal TVal;
    typedef pair<TKey, TVal> Data;

    vector<Data> bucket[MOD];

    int get_pos(int key) {
        int pos = key % MOD;
        return pos < 0 ? pos + MOD : pos;
    }

    void insert(TKey key, TVal val) {
        bucket[get_pos(TPolicy::hash(key))].push_back(Data(key, val));
    }

    bool query(TKey key, TVal &val) {
        int pos = get_pos(TPolicy::hash(key));

        for (auto e : bucket[pos]) {
            if (e.first == key) {
                val = e.second;
                return true;
            }
        }

        return false;
    }
};

struct PrePolicy {
    typedef int TKey;
    typedef int TVal;

    static int hash(int x) {
        return x;
    }
};

static int c[S + 10];
static int p[S + 10];
static HashTable<PrePolicy> mu;

int pre(int n) {
    if (n <= S)
        return p[n];

    int ret = 1;
    if (mu.query(n, ret))
        return ret;

    for (int i = 2, last = 2; i <= n; i = last + 1) {
        last = n / (n / i);
        ret -= (last - i + 1) * pre(n / i);
    }

    mu.insert(n, ret);
    return ret;
}

struct Key {
    int n, m, k;

    bool operator==(const Key &b) const {
        return n == b.n && m == b.m && k == b.k;
    }
};

struct DpPolicy {
    typedef Key TKey;
    typedef i64 TVal;

    static int hash(const TKey &x) {
        return (x.n ^ x.m) * x.k;
    }
};

static vector<int> d[KMAX + 10];
static HashTable<DpPolicy> mem;

i64 dp(int n, int m, int k) {
    if (n == 0 || m == 0)
        return 0;

    Key key = {n, m, k};
    i64 ret = 0;
    if (mem.query(key, ret))
        return ret;

    for (int i = 1, last = 1; i <= n && i <= m; i = last + 1) {
        last = min(n / (n / i), m / (m / i));
        i64 sum = pre(last) - pre(i - 1); 
        ret += sum * (n / i) * (m / i);
    }

    for (int i : d[k]) {
        ret += c[i] * dp(m / i, n, i);
    }

    mem.insert(key, ret);
    return ret;
}

static int n, m, k;
static bool marked[S + 10];
static int prime[S + 10], cnt;

void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    c[1] = p[1] = 1;
    for (int i = 2; i <= S; i++) {
        if (!marked[i]) {
            c[i] = -1;
            prime[++cnt] = i;
        }

        p[i] = p[i - 1] + c[i];
        for (int j = 1; i * prime[j] <= S; j++) {
            int p = prime[j];
            marked[i * p] = true;

            if (i % p == 0) {
                c[i * p] = 0;
                break;
            } else
                c[i * p] = -c[i];
        }
    }

    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= i; j++) {
            if (c[j] && i % j == 0)
                d[i].push_back(j);
        }
    }
}

int main() {
    // freopen("cyclic.in", "r", stdin);
    initialize();
    printf("%lld\n", dp(n, m, k));

    return 0;
}
