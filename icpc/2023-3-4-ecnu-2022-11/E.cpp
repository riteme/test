#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;
constexpr int DMAX = 100;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int v, w;
};

using Tree = vector<Edge>[NMAX + 10];

int n;

void read(Tree T) {
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        T[u].push_back({v, w});
        T[v].push_back({u, w});
    }
}

int s[NMAX + 10];
bool mark[NMAX + 10];

void dfs1(Tree T, int u, int p) {
    s[u] = 1;
    for (auto &e : T[u]) {
        int v = e.v;
        if (mark[v] || v == p)
            continue;
        dfs1(T, v, u);
        s[u] += s[v];
    }
}

int center(Tree T, int u, int p, int maxs) {
    int maxv = 0;
    for (auto &e : T[u]) {
        int v = e.v;
        if (mark[v] || v == p)
            continue;
        if (s[v] > s[maxv])
            maxv = v;
    }
    return s[maxv] * 2 > maxs ? center(T, maxv, u, maxs) : u;
}

void dfs2(Tree T, int u, int p, int i, i64 s, i64 *d, int *k) {
    d[u] = s;
    k[u] = i;
    for (auto &e : T[u]) {
        int v = e.v;
        if (mark[v] || v == p)
            continue;
        dfs2(T, v, u, i, s + e.w, d, k);
    }
}

i64 dist[DMAX][NMAX + 10];
int k[DMAX][NMAX + 10];

int m, maxr;

int build(Tree T, int x, int r) {
    maxr = max(maxr, r);
    int i = ++m;
    dfs1(T, x, 0);
    int u = center(T, x, 0, s[x]);
    dfs2(T, u, 0, i, 0, dist[r], k[r]);
    mark[u] = true;
    for (auto &e : T[u]) {
        int v = e.v;
        if (mark[v])
            continue;
        build(T, v, r + 1);
    }
    return i;
}

Tree T[2];
int minr;
i64 mi[NMAX + 10];
i64 ans[NMAX + 10];
int a[NMAX + 10];

void solve(int ry, int beg, int end, int step) {
    for (int _i = beg; _i != end; _i += step) {
        int i = a[_i];
        for (int rx = 0; rx < minr; rx++) {
            int x = k[rx][i];
            if (x == 0)
                break;
            i64 s = dist[rx][i] + dist[ry][i];
            ans[i] = min(ans[i], s + mi[x]);
            mi[x] = min(mi[x], s);
        }
    }

    for (int _i = beg; _i != end; _i += step) {
        int i = a[_i];
        for (int rx = 0; rx < minr; rx++) {
            int x = k[rx][i];
            if (x == 0)
                break;
            mi[x] = INF;
        }
    }
}

int cnt[NMAX + 10];

// #include <chrono>

int main() {
    // using c = chrono::steady_clock;
    // auto t0 = c::now();

    scanf("%d", &n);
    read(T[0]);
    read(T[1]);
    build(T[0], 1, 0);
    memset(mark, 0, sizeof(mark));
    minr = maxr + 1;
    build(T[1], 1, minr);

    // auto t1 = c::now();
    // fprintf(stderr, "%ld\n", (t1 - t0).count());

    memset(ans, 0x3f, sizeof(ans));
    memset(mi, 0x3f, sizeof(mi));
    // iota(a + 1, a + n + 1, 1);
    for (int ry = minr; ry <= maxr; ry++) {
        // sort(a + 1, a + n + 1, [&](int u, int v) { return k[ry][u] < k[ry][v]; });
        auto K = [&](int i) {
            int v = k[ry][i];
            return v ? v - n : 0;
        };
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) {
            cnt[K(i)]++;
        }
        partial_sum(cnt, cnt + n + 10, cnt);
        for (int i = 1; i <= n; i++) {
            a[cnt[K(i)]--] = i;
        }

        for (int i = 1, j; i <= n; i = j) {
            for (j = i; j <= n && k[ry][a[j]] == k[ry][a[i]]; j++) {}
            if (k[ry][a[i]] > 0) {
                solve(ry, i, j, +1);
                solve(ry, j - 1, i - 1, -1);
            }
        }
    }

    // t1 = c::now();
    // fprintf(stderr, "%ld\n", (t1 - t0).count());

    for (int i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}
