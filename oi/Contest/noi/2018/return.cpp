#define NDEBUG

#define NAME "return"

#include <cstdio>
#include <cstring>
#include <climits>

#include <map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define MMAX 400000

struct Edge {
    int u, v, w, h;

    int either(int x) {
        return u == x ? v : u;
    }

    bool operator<(const Edge &b) const {
        return h > b.h;
    }
};

template <typename T, unsigned N>
struct SuperArray {
    typedef typename map<int, T>::const_iterator iterator_t;

    SuperArray() : cur(0) {}

    int cur;
    map<int, T> arr[N];

    int cat(int i) const {
        return cat(cur, i);
    }

    int &at(int i) {
        return at(cur, i);
    }

    int cat(int ver, int i) const {
        iterator_t iter = arr[i].upper_bound(ver);
        iter--;
        return iter->second;
    }

    int &at(int ver, int i) {
        return arr[i][ver];
    }

    void reset() {
        cur = 0;
        for (size_t i = 0; i < N; i++)
            arr[i].clear();
    }

    void save() {
        cur++;
    }
};

static int n, m, q, K, S;
static int dist[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static Edge edges[MMAX + 10];
static SuperArray<int, NMAX + 10> fa;

int find(int ver, int x) {
    return fa.cat(ver, x) > 0 ? fa.at(ver, x) = find(ver, fa.cat(ver, x)) : x;
}

int find(int x) {
    return fa.cat(x) > 0 ? fa.at(x) = find(fa.cat(x)) : x;
}

void dijkstra() {
    struct State {
        int u, d;

        bool operator<(const State &b) const {
            return d > b.d;
        }
    };

    dist[1] = 0;
    for (int i = 2; i <= n; i++)
        dist[i] = INT_MAX;
    priority_queue<State> q;
    q.push((State){1, 0});
    while (!q.empty()) {
        State s = q.top();
        q.pop();
        if (s.d > dist[s.u]) continue;

        int u = s.u;
        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);
            if (dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;
                q.push((State){v, dist[v]});
            }
        }
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w, h;
        scanf("%d%d%d%d", &u, &v, &w, &h);
        edges[i] = (Edge){u, v, w, h};
        G[u].push_back(edges + i);
        G[v].push_back(edges + i);
    }

    dijkstra();
    for (int i = 1; i <= n; i++)
        fa.at(i) = -dist[i];
    fa.save();

    sort(edges + 1, edges + m + 1);
    for (int i = 1; i <= m; i++) {
        Edge &e = edges[i];
        int u = find(e.u), v = find(e.v);
        if (u != v) {
            fa.at(v) = max(fa.cat(v), fa.cat(u));
            fa.at(u) = v;
        }
        fa.save();
    }

    scanf("%d%d%d", &q, &K, &S);
}

void finalize() {
    fa.reset();
    for (int u = 1; u <= n; u++)
        G[u].clear();
}

bool cmp(const Edge &a, const Edge &b) {
    return a.h > b.h;
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        int lastans = 0;
        while (q--) {
            int v, p;
            scanf("%d%d", &v, &p);
            if (K) {
                v = (v + lastans - 1) % n + 1;
                p = (p + lastans) % (S + 1);
            }

            Edge tmp = (Edge){0, 0, 0, p + 1};
            int ver = upper_bound(edges + 1, edges + m + 1, tmp, cmp) - edges - 1;
            lastans = -fa.cat(ver, find(ver, v));
            printf("%d\n", lastans);
        }

        finalize();
    }

    return 0;
}
