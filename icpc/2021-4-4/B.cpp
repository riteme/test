#include <cstdio>
#include <cassert>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 3000;
constexpr int EMAX = 100000;
constexpr int INF = 0x3f3f3f3f;

int ecnt;
struct Edge {
    int u, v, c, w;
    Edge *rev;
} es[EMAX + 10];

bool is_rev(Edge *e) {
    int i = e - es;
    return i & 1;
}

int q, K, n, s, t, r;
vector<Edge *> G[NMAX + 10];
int mark[NMAX + 10];

void link(int u, int v, int c, int w) {
    // printf("%d->%d, c=%d, w=%d\n", u, v, c, w);

    auto e1 = &es[ecnt++];
    auto e2 = &es[ecnt++];
    *e1 = {u, v, c, w};
    *e2 = {v, u, 0, -w};
    e1->rev = e2;
    e2->rev = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

void link(int u, int v, int l, int r, int w) {
    link(s, v, l, 0);
    link(u, v, r - l, w);
    link(u, t, l, 0);
}

bool in[NMAX + 10];
int dist[NMAX + 10];
Edge *pa[NMAX + 10];

bool spfa() {
    memset(in, 0, sizeof(in));
    memset(dist, 0x3f, sizeof(dist));
    in[s] = true;
    dist[s] = 0;

    queue<int> q;
    q.push(s);

    do {
        int u = q.front();
        q.pop();
        in[u] = false;

        for (auto e : G[u]) if (e->c > 0) {
            int v = e->v;
            if (dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;
                pa[v] = e;

                if (!in[v]) {
                    q.push(v);
                    in[v] = false;
                }
            }
        }
    } while (q.size());

    return dist[t] < INF;
}

int mcmf() {
    int rax = 0;
    while (spfa()) {
        int x = t, flow = INF;

        do {
            auto e = pa[x];
            flow = min(flow, e->c);
            x = e->u;
        } while (x != s);

        rax += flow * dist[t];

        x = t;
        do {
            auto e = pa[x];
            e->c -= flow;
            e->rev->c += flow;
            x = e->u;
        } while (x != s);
    }

    return rax;
}

std::vector<char> seq, stk;

int dfs(int u, int maxflow = INF) {
    if (maxflow <= 0)
        return 0;
    if (u == n) {
        seq.insert(seq.end(), stk.rbegin(), stk.rend());
        return 1;
    }

    int sum = 0;
    for (auto e : G[u]) if (is_rev(e) && e->c > 0) {
        int v = e->v;
        if (v >= r)
            continue;

        char p = -1;
        if (n <= v && v < r && u < n) {
            int d = u ^ (v - n);
            for (int i = 0; i < K; i++) {
                if (d == (1 << i)) {
                    p = '0' + i;
                    break;
                }
            }
            assert(p != -1);
        }

        if (p >= 0)
            stk.push_back(p);

        int flow = min(e->c, maxflow - sum);
        flow = dfs(v, flow);
        e->c -= flow;
        sum += flow;

        if (p >= 0)
            stk.pop_back();
    }

    return sum;
}

int main() {
    scanf("%d%d", &K, &q);
    n = 1 << K;
    r = 2 * n;
    s = r + 1;
    t = s + 1;

    for (int i = 0; i < q; i++) {
        char buf[32];
        scanf("%s", buf);

        int A = 0;
        for (int j = 0; j < K; j++) {
            if (buf[j] == '1')
                A |= 1 << j;
        }

        mark[A] = 1;
    }

    for (int A = 0; A < n; A++) {
        if (mark[A])
            link(A, n + A, 1, INF, 0);
        else
            link(A, n + A, INF, 0);

        link(n + A, r, INF, 1);
    }
    link(r, n, INF, 0);

    for (int A = 0; A < n; A++)
    for (int i = 0; i < K; i++)
    if (!((A >> i) & 1)) {
        int B = A | (1 << i);
        link(n + A, B, INF, 1);
    };

    int ans = mcmf();

    printf("%d\n", ans - 1);
    seq.reserve(ans);
    stk.reserve(ans);

    for (int A = 0; A < n; A++) if (mark[A])
    for (auto e : G[n + A]) if (e->v == A) {
        e->c++;
        break;
    }

    stk.push_back('R');
    dfs(r);
    assert(seq.size() == ans);

    for (int i = 0; i + 1 < seq.size(); i++) {
        printf("%c ", seq[i]);
    }
    puts("");

    return 0;
}