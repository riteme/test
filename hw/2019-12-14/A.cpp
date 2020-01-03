#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <list>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 50000

typedef long long i64;

struct Edge;
typedef list<Edge>::iterator iter;

struct Edge {
    int u, v;
    i64 w;
    iter rev;
};

static int n, m;
static i64 A, B;
static struct Item {
    int u, v;
    i64 a, b;

    bool operator<(const Item &z) const  {
        return a < z.a;
    }
} r[MMAX + 10];
static list<Edge> G[NMAX + 10];
static iter nil = G[0].end();

static iter dret;
bool dfs(int x, int f, int t) {
    if (x == t) return true;
    for (iter it = G[x].begin(); it != G[x].end(); it++)
    if (it->v != f && dfs(it->v, x, t)) {
        if (dret == nil || it->w > dret->w)
            dret = it;
        return true;
    }
    return false;
}

int main() {
    scanf("%d%d%lld%lld", &n, &m, &A, &B);
    for (int i = 0; i < m; i++)
        scanf("%d%d%lld%lld", &r[i].u, &r[i].v, &r[i].a, &r[i].b);
    sort(r, r + m);
    i64 ans = LLONG_MAX;
    multiset<i64> q;
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        auto &e = r[i];
        if (e.u == e.v) continue;

        dret = nil;
        bool flag = dfs(e.u, 0, e.v);
        if (flag && e.b < dret->w) {
            int u = dret->u, v = dret->v;
            iter rev = dret->rev;
            auto it = q.find(dret->w);
            q.erase(it);
            G[u].erase(dret);
            G[v].erase(rev);
            flag = false;
            cnt--;
        }
        if (!flag) {
            G[e.u].push_front({e.u, e.v, e.b, nil});
            G[e.v].push_front({e.v, e.u, e.b, nil});
            iter it = G[e.u].begin();
            iter rev = G[e.v].begin();
            it->rev = rev; rev->rev = it;
            q.insert(e.b);
            cnt++;
        }

        if (cnt == n - 1)
            ans = min(ans, e.a * A + *q.rbegin() * B);
    }
    printf("%lld\n", ans == LLONG_MAX ? -1LL : ans);
    return 0;
}
