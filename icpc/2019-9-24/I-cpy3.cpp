#include <cstdio>
#include <cstring>

#include <random>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define NMAX 50
#define BASE 19260817

typedef unsigned char u8;
typedef unsigned long long u64;

static u64 w[NMAX];
inline u64 H(int n, const u8 *s) {
    u64 r = 0;
    for (int i = 0; i < n; i++)
        r += s[i] * w[i];
    return r;
}

struct HashSet {
    static constexpr u64 BUCSIZE = 4999999;
    static constexpr int CMAX = 4000000;

    u64 key[BUCSIZE + 50];
    size_t pos[CMAX + 10], cnt;

    void insert(u64 x) {
        size_t p = x % BUCSIZE;
        for ( ; key[p]; p++)
            if (key[p] == x) return;
        //pos[cnt++] = p;
        cnt++;
        key[p] = x;
    }

    void clear() {
        memset(key, 0, sizeof(key));
        //for (int i = 0; i < cnt; i++)
        //    key[pos[i]] = 0;
        cnt = 0;
    }

    int size() const {
        return cnt;
    }
};

static int n, m, _;
static int u[NMAX], v[NMAX];
static u8 s[NMAX];
static u64 X;

static HashSet tb;
void dfs(int i) {
    if (i == m) tb.insert(X);
    else if (s[u[i]] < s[v[i]]) {
        dfs(i + 1);

        u64 X0 = X;
        X += s[u[i]] * (w[v[i]] - w[u[i]]) + s[v[i]] * (w[u[i]] - w[v[i]]);
        swap(s[u[i]], s[v[i]]);
        dfs(i + 1);
        X = X0;
        swap(s[u[i]], s[v[i]]);
    }
}

inline void reset(int len) {
    for (int i = 0; i < len; i++)
        s[i] = i + 1;
}

int solve() {
    unordered_set<u64> used;
    reset(n);
    tb.clear();
    auto proc = [&used]() {
        X = H(n, s);
        if (!used.count(X)) {
            used.insert(X);
            dfs(0);
        }
    };
    proc();
    for (int i = 0; i < n; i++) {
        reset(n);
        for (int j = i - 1; j >= 0; j--) {
            swap(s[j], s[j + 1]);
            proc();
        }

        reset(n);
        for (int j = i + 1; j < n; j++) {
            swap(s[j], s[j - 1]);
            proc();
        }
    }

    return tb.size();
}

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    for (int i = 0; i < NMAX; i++)
        w[i] = gen();

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &_);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", u + i, v + i);
            u[i]--;
            v[i]--;
        }
        reverse(u, u + m);
        reverse(v, v + m);

        printf("%d\n", solve());
    }

    return 0;
}
