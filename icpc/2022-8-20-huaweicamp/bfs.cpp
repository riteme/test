#include <cstdio>
#include <cstring>
#include <cassert>

#include <set>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

using Ep = pair<int, int>;
using i64 = long long;

constexpr int NMAX = 11000;
constexpr int MMAX = 32000;
constexpr int QMAX = 10010;
constexpr int GMAX = 14100;
constexpr int LMAX = 550;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
    int i, g, u, v, d, c;

    int to(int x) const {
        return u == x ? v : u;
    }
};

struct Flow {
    int i, u, v, f, hop;

    i64 bdp() const {
        return i64(f) * hop;
    }

    bool operator<(const Flow &z) const {
        return bdp() < z.bdp();
        // return hop < z.hop || (hop == z.hop && f < z.f);
    }
};

struct Group {
    int c;
};

struct Node {
    int c;
    set<Ep> fset;

    void fuck(int a, int b) {
        if (a > b)
            swap(a, b);
        fset.insert({a, b});
    }

    bool fucked(int a, int b) {
        if (fset.empty())
            return false;
        if (a > b)
            swap(a, b);
        return fset.find({a, b}) != fset.end();
    }
};

int n, m, K, q;
Edge es[MMAX];
Flow fs[QMAX];
Node ns[NMAX];
Group gs[GMAX];
vector<Edge *> G[NMAX];
int que[NMAX], head, tail;
int dis[NMAX];
Edge *fe[NMAX];
int land[LMAX][NMAX];

void bfs(int i, int s) {
    memset(land[i], 0x3f, sizeof(land[i]));
    land[i][s] = 0;
    que[0] = s;
    head = 0;
    tail = 1;
    while (head < tail) {
        int u = que[head++];
        for (auto e : G[u]) {
            int v = e->to(u);
            if (land[i][v] >= INF) {
                land[i][v] = land[i][u] + 1;
                que[tail++] = v;
            }
        }
    }
}

int estimate(int u, int v) {
    int ans = INF;
    for (int i = 0; i < LMAX; i++) {
        ans = min(ans, land[i][u] + land[i][v]);
    }
    return ans;
}

bool find_any(int s, int t, int f) {
    if (ns[s].c < 1 || ns[t].c < 1)
        return false;

    memset(dis, 0x3f, sizeof(dis));
    fe[s] = fe[t] = NULL;
    dis[s] = 0;
    que[0] = s;
    head = 0;
    tail = 1;
    while (head < tail) {
        int u = que[head++];
        for (auto e : G[u]) {
            int v = e->to(u);
            if (e->c < f || gs[e->g].c < 1 || ns[v].c < 1 ||
                (fe[u] && ns[u].fucked(fe[u]->i, e->i)))
                continue;
            if (dis[v] >= INF) {
                dis[v] = dis[u] + 1;
                fe[v] = e;
                que[tail++] = v;
                if (v == t)
                    goto out;
            }
        }
    }

out:
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
    for (int i = 0; i < n; i++) {
        sort(G[i].begin(), G[i].end(), [](Edge *a, Edge *b) {
            return a->d < b->d;
        });
    }

    mt19937 gen(0x233324322);
    for (int i = 0; i < LMAX; i++) {
        int s = gen() % n;
        bfs(i, s);
    }

    for (int i = 0; i < K; i++) {
        int u, a, b;
        scanf("%d%d%d", &u, &a, &b);
        ns[u].fuck(a, b);
    }

    for (int i = 0; i < q; i++) {
        int _, u, v, f;
        scanf("%d%d%d%d", &_, &u, &v, &f);
        fs[i] = {i, u, v, f, estimate(u, v)};
    }
    shuffle(fs, fs + q, mt19937(0x192360817));
    sort(fs, fs + q);

    for (auto &no : ns) {
        no.c = 200;
    }
    for (auto &g : gs) {
        g.c = 100;
    }
}

vector<vector<int>> ans;

int main() {
    using clock = chrono::steady_clock;
    auto begin_ts = clock::now();

    initialize();

    set<int> fp;
    for (int i = 0; i < q; i++) {
        fp.insert(fs[i].u);
        fp.insert(fs[i].v);
    }
    assert(fp.size() < 5000);

    for (int i = 0; i < q; i++) {
        auto &f = fs[i];
        if (find_any(f.u, f.v, f.f)) {
            vector<Edge *> stk;
            int x = f.v;
            while (x != f.u) {
                ns[x].c--;
                auto e = fe[x];
                gs[e->g].c--;
                e->c -= f.f;
                stk.push_back(e);
                x = e->to(x);
            }
            ns[x].c--;
            vector<int> p;
            p.push_back(f.i);
            for (int i = stk.size() - 1; i >= 0; i--) {
                p.push_back(stk[i]->i);
            }
            ans.push_back(move(p));

            auto t = chrono::duration_cast<chrono::milliseconds>(clock::now() - begin_ts).count();
            if (t > 1950)
                break;
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
