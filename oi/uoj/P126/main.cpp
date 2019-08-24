// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

template <typename T>
inline void chkmax(T &dest, T src) {
    if (src > dest)
        dest = src;
}

template <typename T>
inline void chkmin(T &dest, T src) {
    if (src < dest)
        dest = src;
}

struct Edge {
    Edge(int _u, int _v, i64 _w)
        : u(_u), v(_v), w(_w) {}

    int u, v;
    i64 w;

    int either(int x) {
        return u == x ? v : u;
    }
};

static int n, s;
static double answer = LLONG_MAX;
static vector<Edge *> G[NMAX + 10];
static vector<Edge *> T[NMAX + 10];
static bool marked[NMAX + 10];

static i64 len[NMAX + 10];
static i64 dis[NMAX + 10];
static i64 maxdist[NMAX + 10];
static i64 maxson[NMAX + 10];
static int nxt[NMAX + 10];
static int pre[NMAX + 10];

inline i64 dist(int u, int v) {
    if (dis[u] < dis[v])
        swap(u, v);

    return min(dis[u] - dis[v], dis[s] - dis[u] + dis[v]);
}

i64 get_weight(int u, int f) {
    for (auto e : T[u]) {
        int v = e->either(u);

        if (v == f)
            continue;

        chkmax(maxson[u], get_weight(v, u) + e->w);
    }

    return maxson[u];
}

bool find_loop(int u, int f) {
    marked[u] = true;

    bool flag = false;
    for (auto e : G[u]) {
        int v = e->either(u);

        if (v == f)
            continue;

        if (marked[v]) {
            if (s)
                continue;

            s = v;
            len[u] = dis[u] = e->w;
            nxt[u] = v;
            pre[v] = u;
            flag = true;
        } else if (find_loop(v, u)) {
            len[u] = e->w;
            dis[u] = dis[v] + e->w;
            nxt[u] = v;
            pre[v] = u;

            if (s != u)
                flag = true;
        } else {
            T[u].push_back(e);
            T[v].push_back(e);
        }
    }

    return flag;
}


void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int u, v;
        i64 w;
        scanf("%d%d%lld", &u, &v, &w);
        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }

    find_loop(1, 0);

    int u = s;
    do {
        maxson[u] = get_weight(u, 0);
        u = nxt[u];
    } while (u != s);
}

inline void pop_deque(deque<int> &q, int s, int v) {
    while (!q.empty() &&
           maxson[q.back()] + dist(q.back(), s) <=
           maxson[v] + dist(v, s)) {
        q.pop_back();
    }
}

static int u, v, p;
static double w, last, mid;
static deque<int> ql, qr;

inline void update_answer1() {
    if (mid >= last) {
        if (!ql.empty() && !qr.empty()) {
            double du = dist(u, qr.front()) + maxson[qr.front()];
            double dp = dist(p, ql.front()) + maxson[ql.front()];
            double x = (du - dp + w) * 0.5;

            chkmin(x, mid);
            chkmax(x, last);
            chkmin(answer, max(dp + x, du + w - x));
        }

        last = mid;
    }
}

inline void update_qr() {
    v = nxt[v];
    mid = (dist(u, v) - dist(p, v) + w) * 0.5;
    chkmin(mid, w);
    update_answer1();

    pop_deque(qr, u, v);
    qr.push_back(v);

    if (ql.front() == v)
        ql.pop_front();
}

void dfs(int u, int f, i64 d) {
    vector<i64> dpre(T[u].size() + 1);
    vector<i64> dsuf(T[u].size() + 1);

    for (size_t i = 0; i < T[u].size(); i++) {
        Edge *e = T[u][i];
        int v = e->either(u);

        if (v == f)
            dpre[i + 1] = dpre[i];
        else
            dpre[i + 1] = max(dpre[i], maxson[v] + e->w);
    }

    for (int i = T[u].size() - 1; i >= 0; i--) {
        Edge *e = T[u][i];
        int v = e->either(u);

        if (v == f)
            dsuf[i] = dsuf[i + 1];
        else
            dsuf[i] = max(dsuf[i + 1], maxson[v] + e->w);
    }

    for (size_t i = 0; i < T[u].size(); i++) {
        Edge *e = T[u][i];
        int v = e->either(u);

        if (v == f)
            continue;

        i64 maxd = max(d, max(dpre[i], dsuf[i + 1]));
        double x = (maxson[v] - maxd + e->w) * 0.5;
        chkmax(x, 0.0);
        chkmin(x, static_cast<double>(e->w));
        chkmin(answer, max(maxd + x, maxson[v] + e->w - x));

        dfs(v, u, maxd + e->w);
    }
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    p = pre[s], v = p;
    while (dist(p, nxt[v]) == dist(p, v) + len[v]) {
        v = nxt[v];
        pop_deque(qr, p, v);
        qr.push_back(v);
    }

    u = v, v = nxt[v];
    while (v != p) {
        pop_deque(ql, p, v);
        ql.push_back(v);
        v = nxt[v];
    }

    pop_deque(ql, p, p);
    ql.push_back(p);

    v = u, u = s;
    do {
        p = pre[u];
        w = len[p];
        last = 0.0;

        if (nxt[v] == u) {
            update_qr();
        }

        while (dist(nxt[v], u) == dist(v, u) + len[v]) {
            update_qr();
        }

        mid = w;
        update_answer1();

        if (qr.front() == u)
            qr.pop_front();

        if (!ql.empty())
            chkmax(maxdist[u], dist(ql.front(), u) + maxson[ql.front()]);
        if (!qr.empty())
            chkmax(maxdist[u], dist(qr.front(), u) + maxson[qr.front()]);

        pop_deque(ql, u, u);
        ql.push_back(u);

        u = nxt[u];
    } while (u != s);

    u = s;
    do {
        dfs(u, 0, maxdist[u]);
        u = nxt[u];
    } while (u != s);

    printf("%.1lf\n", answer);

    return 0;
}
