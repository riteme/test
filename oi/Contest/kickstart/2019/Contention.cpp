#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 30000
#define INF 0x3f3f3f3f

struct Edge {
    bool init;
    int v, c;
    Edge *rev;
};

struct Node {
    int l, r, id;
    Node *lch = NULL, *rch = NULL;
};

constexpr int s = 1, t = 2;
static int n, m, cnt = 2;
static vector<Edge *> G[NMAX * 3 + 10];

void link(int u, int v, int c) {
    Edge *e = new Edge{true, v, c};
    Edge *re = new Edge{false, u, 0};
    e->rev = re; re->rev = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

Node *build(int l, int r) {
    Node *x = new Node{l, r, ++cnt};
    if (l < r) {
        int m = (l + r) >> 1;
        x->lch = build(l, m);
        x->rch = build(m + 1, r);
        link(x->id, x->lch->id, INF);
        link(x->id, x->rch->id, INF);
    } else link(cnt, t, 1);
    return x;
}

void cover(Node *x, int p, int l, int r) {
    if (l <= x->l && x->r <= r) link(p, x->id, INF);
    else {
        int m = (x->l + x->r) >> 1;
        if (l <= m) cover(x->lch, p, l, r);
        if (r > m) cover(x->rch, p, l, r);
    }
}

void reset(int K) {
    for (auto e : G[s]) {
        e->c = K;
        e->rev->c = 0;
    }
    for (int u = t + 1; u <= cnt; u++) for (auto e : G[u]) if (e->init) {
        e->c += e->rev->c;
        e->rev->c = 0;
    }
}

static int lev[NMAX * 3 + 10];
static size_t pos[NMAX * 3 + 10];

bool bfs() {
    memset(lev, 0, sizeof(lev));
    queue<int> q;
    q.push(s);
    lev[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto e : G[u]) if (!lev[e->v] && e->c) {
            lev[e->v] = lev[u] + 1;
            q.push(e->v);
        }
    }
    return lev[t];
}

int dfs(int x, int maxf = INF) {
    if (x == t) return maxf;
    int cur = 0;
    for (size_t &i = pos[x]; i < G[x].size(); i++) {
        auto e = G[x][i];
        int v = e->v;
        if (lev[x] + 1 != lev[v] || !e->c) continue;
        int flow = min(e->c, maxf - cur);
        flow = dfs(v, flow);
        cur += flow;
        e->c -= flow;
        e->rev->c += flow;
        if (cur == maxf) break;
    }
    return cur;
}

int dinic() {
    int ret = 0;
    while (bfs()) {
        memset(pos + 1, 0, sizeof(size_t) * cnt);
        ret += dfs(s);
    }
    return ret;
}

int main() {
    Node *net = build(1, NMAX);
    int head = cnt;

    int T;
    scanf("%d", &T);
    for (int id = 1; id <= T; id++) {
        scanf("%d%d", &n, &m);
        cnt = head;
        for (int i = 1; i <= m; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            cover(net, ++cnt, l, r);
            link(s, cnt, 0);
        }

        int l = 0, r = NMAX / m + 1;
        while (l < r) {
            int K = ((l + r) >> 1) + 1;
            reset(K);
            int w = dinic();
            if (w == m * K) l = K;
            else r = K - 1;
        }
        printf("Case #%d: %d\n", id, l);
        G[s].clear();
        for (int i = 1; i <= m; i++) G[head + i].clear();
        for (int i = t + 1; i <= head; i++)
            while ((*G[i].rbegin())->v > head) G[i].pop_back();
    }
    return 0;
}
