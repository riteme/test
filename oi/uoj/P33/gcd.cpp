// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <array>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define S 100

template <typename T>
struct ReversedVector {
    vector<T> data;

    size_t size() const {
        return data.size();
    }

    void extend() {
        data.push_back(T());
    }

    T &operator[](const size_t i) {
        return data[data.size() - i];
    }

    const T &operator[](const size_t i) const {
        return data[data.size() - i];
    }
};

typedef array<i64, S + 1> SArray;

struct Data {
    ReversedVector<SArray> dp;

    size_t size() const {
        return dp.size();
    }

    void extend() {
        dp.extend();

        for (int i = 0; i <= S; i++) {
            if (i < dp.size())
                dp[1][i] = dp[1 + i][i] + 1;
            else
                dp[1][i] = 1;
        }
    }

    i64 query(int x, int d) {
        if (d <= S)
            return dp[x][d];

        i64 ret = 0;
        for (; x <= dp.size(); x += d) {
            ret += dp[x][0];
        }

        return ret;
    }

    Data &operator+=(const Data &b) {
        for (int i = 1; i <= b.size(); i++) {
            for (int j = 0; j <= S; j++) {
                dp[i][j] += b.dp[i][j];
            }
        }

        return *this;
    }
};

static int n;
static vector<int> G[NMAX + 10];
static int father[NMAX + 10];
static int dep[NMAX + 10];
static int top[NMAX + 10];
static int nxt[NMAX + 10];
static Data dat[NMAX + 10];
static i64 ans[NMAX + 10];
static i64 suf[NMAX + 10];

void dfs(int u, int dist) {
    suf[dist]++;

    for (int v : G[u]) {
        dfs(v, dist + 1);
        dep[u] = max(dep[u], dep[v] + 1);
    }
}

void decompose(int u) {
    nxt[u] = 0;
    for (int v : G[u]) {
        if (dep[v] + 1 == dep[u]) {
            nxt[u] = v;
            break;
        }
    }

    if (nxt[u]) {
        top[nxt[u]] = top[u];
        decompose(nxt[u]);
    }

    for (int v : G[u]) {
        if (v == nxt[u])
            continue;

        top[v] = v;
        decompose(v);
    }
}

void initialize() {
    scanf("%d", &n);

    for (int v = 2; v <= n; v++) {
        int u;
        scanf("%d", &u);

        father[v] = u;
        G[u].push_back(v);
    }

    dfs(1, 0);
    top[1] = 1;
    decompose(1);
}

void solve(int u) {
    if (nxt[u])
        solve(nxt[u]);

    Data &cur = dat[top[u]];
    for (int v : G[u]) {
        if (v == nxt[u])
            continue;

        solve(v);

        for (int d = 1; d <= dat[v].size(); d++) {
            ans[d] += dat[v].query(d, d) * cur.query(d, d);
        }

        cur += dat[v];
    }

    cur.extend();
}

int main() {
    // freopen("gcd.in", "r", stdin);
    initialize();

    solve(1);

    for (int i = n - 1; i >= 1; i--) {
        suf[i] += suf[i + 1];

        for (int j = i + i; j < n; j += i) {
            ans[i] -= ans[j];
        }
    }

    for (int i = 1; i < n; i++) {
        printf("%lld\n", ans[i] + suf[i]);
    }

    return 0;
}

