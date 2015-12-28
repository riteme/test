// NOIP2015 运输计划
// TODO(riteme): O(n^2): Compute every LCA?

#include <cstdio>
#include <cstring>
#include <vector>
#include <random>
#include <queue>
#include <algorithm>

using namespace std;

typedef int ntype;

constexpr char LCA_NOTMARKED = false;
constexpr char LCA_VISITED = true;
constexpr char LCA_PROCESSED = true + 1;

constexpr ntype NMAX = 300000;
constexpr ntype MMAX = 300000;

struct Plan {
    Plan() : s(0), t(0), ancestor(0) {}
    Plan(const ntype _s, const ntype _t) : s(_s), t(_t), ancestor(0) {}

    ntype s, t;
    ntype ancestor;
};  // struct Plan

struct Edge {
    Edge() : u(0), v(0), w(0) {}
    Edge(const ntype _u, const ntype _v, const ntype _w)
            : u(_u), v(_v), w(_w) {}

    ntype u;
    ntype v;
    ntype w;

    auto another(const ntype x) -> ntype { return x == u ? v : u; }
};  // struct Edge

static ntype n, m;
static ntype answer;
static vector<Edge *> G[NMAX + 1];
static Edge E[NMAX];
static Plan P[MMAX];
static char marked[NMAX + 1];

// Union-Find requested:
static ntype s[NMAX + 1];  // set
static ntype r[NMAX + 1];  // rank

// Tarjan-LCA requested:
static ntype root;
static ntype ancestor[NMAX + 1];

// Extend-Weight requested:
static ntype dist[NMAX + 1];

void initialize();
void quit();

void lca(const ntype u);
void extend_weight(const ntype x);

inline auto read() -> ntype {
    ntype number = 0;
    char ch = getchar();
    while (ch < '0' or ch > '9') ch = getchar();
    while ('0' <= ch and ch <= '9')
        number = number * 10 + (ch - '0'), ch = getchar();

    return number;
}

inline auto random_root(const ntype max_index) -> ntype {
    random_device rd;

    return (rd() + 1) % (max_index + 1);
}

// Union-Find:
inline void make_set(const ntype n_max) {
    ntype cnt = 1;
    generate_n(&s[1], n_max, [&cnt]() { return cnt++; });
    fill_n(r + 1, n_max, 0);
}

inline auto find_set(const ntype a) -> ntype {
    if (s[a] != a) s[a] = find_set(s[a]);

    return s[a];
}

inline void union_set(ntype a, ntype b) {
    a = find_set(a);
    b = find_set(b);

    if (r[a] == r[b]) {
        s[b] = a;
        r[a]++;
    } else if (r[a] < r[b])
        s[a] = b;
    else
        s[b] = a;
}

inline void prepare_lca() {
    memset(marked, LCA_NOTMARKED, sizeof(bool) * (n + 1));
    memset(ancestor, 0, sizeof(ntype) * (n + 1));
}

inline auto distance_of(const Plan &p) -> ntype {
    return dist[p.s] - dist[p.ancestor] + dist[p.t] - dist[p.ancestor];
}

int main() {
    initialize();

    for (ntype i = 0; i < n - 1; i++) {
        Edge &e = E[i];
        ntype ans = 0;

        for (ntype j = 0; j < m; j++) {
            if (find_set(e.u) == P[j].ancestor and
                find_set(e.v) == P[j].ancestor)
                ans = max(ans, distance_of(P[i]) - e.w);
            else
                ans = max(ans, distance_of(P[i]));

            printf(
                "P[j]: {s = %d, t = %d, ancestor = %d}, e: {u = %d, v = %d, w "
                "= %d}, ans = %d\n",
                P[j].s, P[j].t, P[j].ancestor, e.u, e.v, e.w, ans);
        }  // for

        answer = min(answer, ans);
        printf("answer = %d\n", answer);
    }  // for

    quit();
    return 0;
}  // function main

// Tarjan-LCA:
void lca(const ntype u) {
    marked[u] = LCA_VISITED;
    ancestor[find_set(u)] = u;

    for (auto e : G[u]) {
        ntype v = e->another(u);

        if (marked[v] == LCA_NOTMARKED) {
            lca(v);
            union_set(u, v);
            ancestor[find_set(u)] = u;
        }
    }  // foreach in G[u]

    for (ntype i = 0; i < m; i++) {
        if (P[i].s == P[i].t and P[i].s == u) {
            P[i].ancestor = u;
        } else if (P[i].t == u and marked[P[i].s] == LCA_PROCESSED) {
            P[i].ancestor = ancestor[find_set(P[i].s)];

            printf("%d and %d's LCA is %d.\n", P[i].s, P[i].t, P[i].ancestor);
        } else if (P[i].s == u and marked[P[i].t] == LCA_PROCESSED) {
            P[i].ancestor = ancestor[find_set(P[i].t)];

            printf("%d and %d's LCA is %d.\n", P[i].s, P[i].t, P[i].ancestor);
        }
    }  // for

    marked[u] = LCA_PROCESSED;
}

void extend_weight(const ntype x) {
    memset(marked, false, sizeof(bool) * (n + 1));

    queue<ntype> q;
    q.push(x);
    marked[x] = true;
    dist[x] = 0;

    while (!q.empty()) {
        ntype u = q.front();
        q.pop();

        for (auto e : G[u]) {
            ntype v = e->another(u);

            if (!marked[v]) {
                marked[v] = true;
                dist[v] = dist[u] + e->w;

                q.push(v);
            }
        }  // foreach in G[u]
    }      // while

    for (ntype i = 1; i <= n; i++) {
        printf("Node %d's weight is %d.\n", i, dist[i]);
    }  // for
}

void initialize() {
    n = read();
    m = read();
    answer = INT_MAX;

    for (ntype i = 0; i < n - 1; i++) {
        E[i].u = read();
        E[i].v = read();
        E[i].w = read();

        G[E[i].u].push_back(&E[i]);
        G[E[i].v].push_back(&E[i]);
    }  // for

    for (ntype i = 0; i < m; i++) {
        P[i].s = read();
        P[i].t = read();
    }  // for

    make_set(n);
    prepare_lca();
    // root = random_root(n);
    root = 1;
    lca(root);

    extend_weight(root);
}

void quit() { printf("%d", answer); }
