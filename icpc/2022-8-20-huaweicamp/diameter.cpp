#include <cstdio>
#include <cstring>
#include <cassert>

#include <vector>

using namespace std;

constexpr int NMAX = 11000;
constexpr int MMAX = 32000;
constexpr int QMAX = 10010;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
    int i, g, u, v, d, c;

    int to(int x) const {
        return u == x ? v : u;
    }
};

struct Flow {
    int i, u, v, f;
};

int n, m, K, q;
Edge es[MMAX];
Flow fs[QMAX];
vector<Edge *> G[NMAX];
int que[NMAX], head, tail;
int dis[NMAX];

int bfs(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    que[0] = s;
    head = 0;
    tail = 1;
    while (head < tail) {
        int u = que[head++];
        for (auto e : G[u]) {
            int v = e->to(u);
            if (dis[v] >= INF) {
                dis[v] = dis[u] + 1;
                que[tail++] = v;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dis[i]);
    }
    return ans;
}

Edge *fe[NMAX];

bool find_any(int s, int t, int f) {
    memset(dis, 0x3f, sizeof(dis));
    fe[s] = fe[t] = NULL;
    dis[s] = 0;
    que[0] = s;
    head = 0;
    tail = 1;
    while (head < tail) {
        int u = que[head++];
        for (auto e : G[u]) {
            if (e->c < f)
                continue;
            int v = e->to(u);
            if (dis[v] >= INF) {
                dis[v] = dis[u] + 1;
                fe[v] = e;
                que[tail++] = v;
            }
        }
    }
    return fe[t] != NULL;
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &K, &q);
    for (int i = 0; i < m; i++) {
        int _, g, u, v, d, c;
        scanf("%d%d%d%d%d%d", &_, &g, &u, &v, &d, &c);
        es[i] = {i, g, u, v, d, c};
        G[u].push_back(es + i);
        G[v].push_back(es + i);
    }
    for (int i = 0; i < K; i++) {
        int u, a, b;
        scanf("%d%d%d", &u, &a, &b);
    }
    for (int i = 0; i < q; i++) {
        int _, u, v, f;
        scanf("%d%d%d%d", &_, &u, &v, &f);
        fs[i] = {i, u, v, f};
    }
}

vector<vector<int>> ans;

int main() {
    initialize();

    int dia = 0;
    for (int i = 0; i < n && i < 2000; i++) {
        dia = max(dia, bfs(i));
    }
    fprintf(stderr, "diameter=%d\n", dia);
    assert(dia < 200);

    for (int i = 0; i < q && i < 2; i++) {
        if (find_any(fs[i].u, fs[i].v, fs[i].f)) {
            vector<Edge *> stk;
            int x = fs[i].v;
            while (x != fs[i].u) {
                auto e = fe[x];
                stk.push_back(e);
                x = e->to(x);
            }
            vector<int> p;
            p.push_back(i);
            for (int i = stk.size() - 1; i >= 0; i--) {
                p.push_back(stk[i]->i);
            }
            ans.push_back(move(p));
        }
    }

    printf("%zu\n", ans.size());
    for (auto &p : ans) {
        for (int x : p) {
            printf("%d ", x);
        }
        puts("");
    }

    return 0;
}
