#pragma comment(linker, "/STACK:102400000,102400000")

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Interval {
    Interval() : l(0), r(0) {}
    Interval(int x) : l(x), r(x) {}
    Interval(int _l, int _r) : l(_l), r(_r) {}

    int l, r;

    int len() const {
        assert(l <= r);
        return r - l + 1;
    }

    bool operator<(const Interval &b) const {
        return l < b.l;
    }
};

typedef set<Interval>::iterator iter_t;

static int n;
static vector<int> G[NMAX + 10];
static int in[NMAX + 10], out[NMAX + 10], cur;
static int id[NMAX + 10];

void dfs(int u, int f) {
    in[u] = ++cur;
    id[cur] = u;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == f)
            continue;

        dfs(v, u);
    }

    out[u] = cur;
}

void initialize() {
    scanf("%d", &n);

    int u, v;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);
}

static set<Interval> s;
static bool marked[NMAX + 10];
static int pos[NMAX + 10];

i64 sqr(i64 x) {
    return x * x;
}

i64 update(int x) {
    iter_t rt = s.upper_bound(Interval(x));
    iter_t lt = prev(rt);
    int l = lt->r, r = rt->l;
    assert(l < x);
    assert(x < r);
    i64 ret = sqr(x - l - 1) + sqr(r - x - 1) - sqr(r - l - 1);

    int nl = x, nr = x;
    if (l && l + 1 == x) {
        nl = lt->l;
        ret -= sqr(lt->len());
        s.erase(lt);
    }

    if (r <= n && r - 1 == x) {
        nr = rt->r;
        ret -= sqr(rt->len());
        s.erase(rt);
    }

    Interval ni(nl, nr);
    ret += sqr(ni.len());
    s.insert(ni);

    return ret;
}

i64 solve(int l, int r) {
    if (l == r)
        return marked[l] ? 0 : sqr(id[l] - 1) + sqr(n - id[l]) + 1;

    int m = (l + r) >> 1, p;
    for (int i = l; i <= m; i++) {
        p = out[id[i]];
        if (!marked[i] && m < p && p <= r) {
            pos[i] = p;
            marked[i] = true;
        } else
            pos[i] = 0;
    }

    i64 sum = n * n, ret = 0;
    p = m + 1;
    s.clear();
    s.insert(Interval(0));
    s.insert(Interval(n + 1));
    for (int i = m; i >= l; i--) {
        sum += update(id[i]);
        if (!pos[i])
            continue;
        assert(p - 1 <= pos[i]);
        for (; p <= pos[i]; p++)
            sum += update(id[p]);
        ret += sum;
    }

    return ret + solve(l, m) + solve(m + 1, r);
}

int main() {
    // freopen("B.in", "r", stdin);
    initialize();
    printf("%lld\n", ((i64) n * n * n - solve(1, n)) / 2);

    return 0;
}
