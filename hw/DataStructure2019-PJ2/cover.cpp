#include <cstdio>
#include <cctype>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        _getc(c);
    } while (isdigit(c));
}

#define NMAX 5000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

struct Edge {
    int v, w, id;
};

static int n, m;
static vector<Edge> G[NMAX + 10];

void initialize() {
    read(n); read(m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u); read(v); read(w);
        G[u].push_back({v, w, i});
        G[v].push_back({u, w, i});
    }
}

struct Tree {
    int fa[NMAX + 10], len[NMAX + 10];
};

void dijkstra(int s, Tree *tr) {
    struct State {
        int u;
        i64 t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    static i64 dist[NMAX + 10];
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    dist[s] = 0;
    tr->fa[s] = 0;

    priority_queue<State> q;
    q.push({s, 0});
    while (!q.empty()) {
        auto _ = q.top();
        q.pop();
        if (_.t > dist[_.u]) continue;
        int u = _.u;
        for (auto &e : G[u]) {
            int v = e.v;
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                tr->fa[v] = u;
                tr->len[v] = e.w;
                q.push({v, dist[v]});
            }
        }
    }
}

void shortest(int s, Tree *tr) {
    dijkstra(s, tr);
}

static int cnt;
static int num[NMAX + 10];
static int id[NMAX + 10][NMAX + 10];
static vector<Tree*> trs;

static int dep[NMAX + 10];

i64 dist(Tree *tr, int u, int v) {
    i64 ret = 0;
    while (u != v) {
        if (dep[u] < dep[v]) swap(u, v);
        ret += tr->len[u];
        u = tr->fa[u];
    }
    return ret;
}

int cover(int s) {
    // fprintf(stderr, "s = %d\n", s);
    auto tr = new Tree;
    trs.push_back(tr);
    shortest(s, tr);

    cnt++;
    int neo = 0;
    for (int v = 1; v <= n; v++) {
        dep[v] = 1;
        for (int u = tr->fa[v]; u; u = tr->fa[u]) {
            dep[v]++;
            if (!id[u][v]) {
                neo++;
                num[v]++;
                num[u]++;
                id[u][v] = id[v][u] = cnt;
            }
        }
    }

    int rm = 0;
    for (int u = 1; u <= n; u++)
    for (auto &e : G[u]) if (u < e.v) {
        int v = e.v;
        rm += e.w > dist(tr, u, v);
    }
    fprintf(stderr, "[%d] neo = %d, rm = %d ⇒ %d\n", cnt, neo, rm, m - rm);

    // int p = 0;
    // num[0] = n - 1;
    // for (int i = 1; i <= n; i++)
    //     if (num[i] < num[p] ||
    //         (num[i] == num[p] && dep[i] > dep[p]))
    //         p = i;
    // return p;
    return rand() % n + 1;
}

int main() {
    initialize();

    for (int s = 1; /* num[s] < n - 1 */; )
        s = cover(s);
    fprintf(stderr, "cnt = %d\n", cnt);

    int q;
    read(q);
    while (q--) {
        int s, t, c, _;
        read(s); read(t); read(c);
        for (int i = 0; i < c; i++)
            read(_);

        int u = s, v = t;
    }

    return 0;
}