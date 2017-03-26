#define NDEBUG

#define NAME "c"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define PMAX 10000000

static int n, P;
static vector<int> G[NMAX + 10];
static int val[NMAX + 10];
static i64 answer;

void initialize() {
    scanf("%d%d", &n, &P);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", val + i);
    }
}

static bool marked[NMAX + 10];
static int size[NMAX + 10];
static int vsum[NMAX + 10];
static int vmax[NMAX + 10];
static int tail;
static int seq[NMAX + 10];
static int cnt[PMAX];

void eval_size(int u, int f) {
    size[u] = 1;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (v == f || marked[v])
            continue;

        eval_size(v, u);
        size[u] += size[v];
    }
}

int select_center(int u, int f, int std) {
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (v == f || marked[v])
            continue;

        if (size[v] > std)
            return select_center(v, u, std);
    }

    return u;
}

void dfs(int u, int f) {
    vsum[u] = (vsum[f] + val[u]) % P;
    vmax[u] = max(vmax[f], val[u]);
    seq[tail++] = u;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (v == f || marked[v])
            continue;

        dfs(v, u);
    }
}

bool cmp(const int a, const int b) {
    return vmax[a] < vmax[b];
}

i64 evaluate(int d) {
    sort(seq, seq + tail, cmp);
    i64 ret = 0;

    for (int i = 0; i < tail; i++) {
        int u = seq[i];
        if (vsum[u] < 0)
            vsum[u] += P;

        int target = (vmax[u] - vsum[u] + d) % P;
        if (target < 0)
            target += P;
        ret += cnt[target];
        cnt[vsum[u]]++;
    }

    for (int i = 0; i < tail; i++) {
        cnt[vsum[seq[i]]] = 0;
    }

    return ret;
}

void process(int u, int d, int _sum, int _max, int f) {
    tail = 0;
    vsum[0] = _sum;
    vmax[0] = _max;
    dfs(u, 0);
    answer += f * evaluate(d);
}

void solve(int u) {
    eval_size(u, 0);
    int p = select_center(u, 0, size[u] / 2);
    process(p, val[p], 0, 0, 1);

    marked[p] = true;
    for (size_t i = 0; i < G[p].size(); i++) {
        int v = G[p][i];

        if (marked[v])
            continue;

        process(v, val[p], val[p], val[p], -1);
        solve(v);
    }
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();
    solve(1);
    printf("%lld\n", answer + n);

    return 0;
}
