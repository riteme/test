#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 10000;
constexpr int MMAX = 100000;
constexpr int INF = 10000000;

namespace Solver {
    template <typename T>
    T chkmin(T A, T B) {
        return A < B ? A : B;
    }
    static int n, m, s, t, cnt, tot, in[NMAX + 10], id[MMAX + 10];
    static int bgn[NMAX + 10], nxt[MMAX + 10], to[MMAX + 10], c[MMAX + 10], E = 1;
    struct edge {
        int u, v, low, high;
        edge() {}
        edge(int A, int B, int C, int D) : u(A), v(B), low(C), high(D) {}
    } e[MMAX + 10];
    void add_edge(int u, int v, int w) {
        nxt[++E] = bgn[u]; bgn[u] = E; to[E] = v; c[E] = w;
        nxt[++E] = bgn[v]; bgn[v] = E; to[E] = u; c[E] = 0;
    }
    static struct Netflow {
        int n, S, T;
        int cur[NMAX + 10];
        int dis[NMAX + 10];
        void init(int s, int t, int cnt) {
            S = s; T = t; n = cnt;
        }
        bool bfs() {
            memset(dis, 0, n * sizeof(int));
            queue<int> q;
            q.push(S);
            dis[S] = 1;
            while (q.size()) {
                int u = q.front();
                q.pop();
                for (int v, i = bgn[u]; i; i = nxt[i]) {
                    if (c[i] && !dis[v = to[i]]) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                }
            }
            return dis[T] != 0;
        }
        int dfs(int u, int flow) {
            if (u == T)
                return flow;
            int ret = flow;
            for (int v, &i = cur[u]; i; i = nxt[i]) {
                v = to[i];
                if (!(c[i] && dis[v] == dis[u] + 1))
                    continue;
                int f = dfs(v, chkmin(c[i], ret));
                c[i] -= f;
                c[i ^ 1] += f;
                ret -= f;
                if (!ret)
                    return flow;
            }
            return flow - ret;
        }
        int maxflow() {
            int ans = 0;
            while (bfs()) {
                memcpy(cur, bgn, n * sizeof(int));
                ans += dfs(S, INF);
            }
            return ans;
        }
    } dinic;
    void pre(int _n) {
        n = _n;
        m = 0;
        cnt = n;
        s = ++cnt;
        t = ++cnt;
        dinic.init(s, t, ++cnt);
    }
    int add(int A, int B, int C, int D) {
        int i = ++m;
        e[i] = edge(A, B, C, D);
        add_edge(A, B, D - C);
        id[i] = E;
        in[B] += C;
        in[A] -= C;
        return E;
    }
    int post() {
        for (int i = 1; i <= n; i++) {
            if (in[i] < 0)
                add_edge(i, t, -in[i]);
            else if (in[i] > 0)
                add_edge(s, i, in[i]), tot += in[i];
        }
        return dinic.maxflow();
    }
};

int n, m, q;
struct {
    int pa = 0;
    int out = 0;
    int lo = 0, hi = INF;
} a[NMAX + 10];

int root(int u) {
    while (a[u].pa) {
        u = a[u].pa;
    }
    return u;
}

int id[NMAX + 10];
bool removed[NMAX + 10];

int main() {
    scanf("%d%d", &n, &q);
    m = n;
    for (int i = 0; i < q; i++) {
        int op, u;
        scanf("%d%d", &op, &u);
        if (op == 1) {
            int v;
            scanf("%d", &v);
            u = root(u);
            v = root(v);
            int p = ++m;
            a[u].pa = a[v].pa = p;
        } else if (op == 2) {
            int r = root(u);
            int p = ++m;
            a[r].pa = p;
            a[p].out = u;
            removed[u] = true;
        } else {
            int lo, hi;
            scanf("%d%d", &lo, &hi);
            u = root(u);
            a[u].lo = max(a[u].lo, lo);
            a[u].hi = min(a[u].hi, hi);
        }
    }

    int s = m + n + 1;
    int t = s + 1;

    Solver::pre(t);
    Solver::add(t, s, 0, INF);
    for (int i = 1; i <= n; i++) {
        if (!removed[i])
            Solver::add(s, m + i, 0, 1);
        id[i] = Solver::add(m + i, i, 0, 1);
    }
    for (int i = 1; i <= m; i++) {
        int p = a[i].pa;
        if (!p)
            p = t;
        Solver::add(i, p, a[i].lo, a[i].hi);
        int u = a[i].out;
        if (u)
            Solver::add(i, m + u, 0, 1);
    }
    if (Solver::post() == Solver::tot) {
        puts("YES");
        for (int i = 1; i <= n; i++) {
            int c = Solver::c[id[i]];
            putchar(c ? 'R' : 'B');
        }
        puts("");
    } else {
        puts("NO");
    }
    return 0;
}
