#define NDEBUG

#include <cassert>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }

    return buffer[pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 250000
#define LOGN 18

typedef long long int64;

struct Edge {
    Edge (int _u, int _v, int64 _w)
        : u(_u), v(_v), w(_w) {}

    int u, v;
    int64 w;

    int either(int x) const {
        return u == x ? v : u;
    }
};

static int n, q;
static vector<Edge *> G[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];
static int64 minv[LOGN + 1][NMAX + 10];
static int timestamp;
static int dfn[NMAX + 10];
static int dist[NMAX + 10];
static bool marked[NMAX + 10];

static void dfs(int x) {
    marked[x] = true;
    dfn[x] = timestamp++;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (!marked[v]) {
            f[0][v] = x;
            minv[0][v] = e->w;
            dist[v] = dist[x] + 1;

            dfs(v);
        }
    }
}

static void initialize() {
    // scanf("%d", &n);
    n = readint();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        int64 w;
        // scanf("%d%d%lld", &u, &v, &w);
        u = readint();
        v = readint();
        w = readint();
        
        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }

    // scanf("%d", &q);
    q = readint();

    dfs(1);
    for (int j = 1;  j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
            minv[j][i] = min(minv[j - 1][i], minv[j - 1][f[j - 1][i]]);
        }
    }

    memset(marked, 0, sizeof(marked));
}

inline int evaluate_lca(int u, int v) {
    if (dist[u] < dist[v])
        swap(u, v);

    int delta = dist[u] - dist[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1) {
            u = f[i][u];
        }
    }

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[i][u] != f[i][v]) {
            u = f[i][u];
            v = f[i][v];
        }
    }

    return f[0][u];
}

inline int64 query_min(int x, int p) {
    int delta = dist[x] - dist[p];
    int64 answer = LLONG_MAX;
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1) {
            answer = min(answer, minv[i][x]);
            x = f[i][x];
        }
    }

    return answer;
}

static int len;
static int P[NMAX + 10];

static bool cmp(const int &a, const int &b) {
    return dfn[a] < dfn[b];
}

#define LAST(s) (s[s.size() - 1])

struct Node {
    Node (int _u)
        : u(_u), dist(0) {}

    int u;
    int64 dist;
    vector<Node *> children;
};

static Node *construct() {
    sort(P + 1, P + len + 1, cmp);

    vector<Node *> stk;
    stk.push_back(new Node(1));
    for (int i = 1; i <= len; i++) {
        int p = P[i];

        if (!stk.empty()) {
            int lca = evaluate_lca(LAST(stk)->u, p);
            assert(lca != p);

            while (stk.size() >= 2) {
                Node *x = LAST(stk);
                stk.pop_back();

                if (dfn[LAST(stk)->u] < dfn[lca]) {
                    Node *nw = new Node(lca);
                    nw->children.push_back(x);
                    stk.push_back(nw);
                    x->dist = query_min(x->u, lca);

                    break;
                } else {
                    LAST(stk)->children.push_back(x);
                    x->dist = query_min(x->u, LAST(stk)->u);

                    if (LAST(stk)->u == lca)
                        break;
                }
            }
        }

        stk.push_back(new Node(p));
    }

    while (stk.size() >= 2) {
        Node *x = LAST(stk);
        stk.pop_back();
        LAST(stk)->children.push_back(x);
        x->dist = query_min(x->u, LAST(stk)->u);
    }

    stk[0]->dist = LLONG_MAX;

    return stk[0];
}

static int64 dp(Node *x) {
    if (marked[x->u])
        return x->dist;

    int64 sum = 0;
    for (size_t i = 0; i < x->children.size(); i++) {
        Node *v = x->children[i];

        sum += dp(v);
    }

    return min(x->dist, sum);
}

static int64 query() {
    for (int i = 1; i <= len; i++) {
        marked[P[i]] = true;
    }

    int64 answer = dp(construct());

    for (int i = 1; i <= len; i++) {
        marked[P[i]] = false;
    }

    return answer;
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    while (q--) {
        // scanf("%d", &len);
        len = readint();

        for (int i = 1; i <= len; i++) {
            // scanf("%d", P + i);
            P[i] = readint();
        }

        printf("%lld\n", query());
    }

    return 0;
}
