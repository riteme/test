#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define TMAX 50

#define A 'a'
#define B 'b'
#define C 'c'
#define X 'x'

inline char randchr() {
    return A + rand() % 3;
}

struct Graph {
    vector<int> G[NMAX + 10];

    void link(int u, int v) {
        G[u].push_back(v);
    }

    void bilink(int u, int v) {
        link(u, v);
        link(v, u);
    }

    vector<int> &operator[](int x) {
        return G[x];
    }
};

static int n, m, d;
static char S[NMAX + 10];
static Graph N, G;

inline int p(int x, int c, int t) {
    return (x - 1) * 6 + (c - A + 1) + t * 3;
}

inline int inv(int x) {
    return (x - 1) % 6 < 3 ? x + 3 : x - 3;
}

static stack<int> stk;
static bool marked[NMAX + 10];
static int dfn[NMAX + 10], low[NMAX + 10], cur;
static int id[NMAX + 10], cnt;

void scc(int x) {
    dfn[x] = low[x] = ++cur;
    stk.push(x);

    for (int v : G[x]) {
        if (marked[v])
            continue;
        if (!dfn[v])
            scc(v);
        low[x] = min(low[x], low[v]);
    }

    if (low[x] == dfn[x]) {
        cnt++;
        while (true) {
            int u = stk.top();
            stk.pop();
            id[u] = cnt;
            marked[u] = true;

            if (u == x)
                break;
        }
    }
}

bool invalid() {
    for (int i = 1; i <= n; i++) {
        for (char c = A; c <= C; c++) {
            if (id[p(i, c, 0)] == id[p(i, c, 1)])
                return true;
        }
    }

    return false;
}

inline void setup(Graph &T, int i, char c) {
    T.link(p(i, c, 0), p(i, c, 1));

    switch (c) {
        case A: {
            T.bilink(p(i, B, 0), p(i, C, 1));
            T.bilink(p(i, C, 0), p(i, B, 1));
        } break;

        case B: {
            T.bilink(p(i, A, 0), p(i, C, 1));
            T.bilink(p(i, C, 0), p(i, A, 1));
        } break;

        case C: {
            T.bilink(p(i, A, 0), p(i, B, 1));
            T.bilink(p(i, B, 0), p(i, A, 1));
        } break;
    }
}

void initialize() {
    srand(time(0));
    scanf("%d%d%s%d", &n, &d, S + 1, &m);

    for (int i = 1; i <= n; i++) {
        if (S[i] == X)
            continue;

        setup(N, i, S[i]);
    }

    int a, c;
    char b[4], d[4];
    for (int i = 0; i < m; i++) {
        scanf("%d%s%d%s", &a, b, &c, d);
        N.link(p(a, b[0] + 32, 0), p(c, d[0] + 32, 0));
        N.link(p(c, d[0] + 32, 1), p(a, b[0] + 32, 1));
    }
}

#define SELECT 1
#define CANCEL 2

static Graph T, V;
static int in[NMAX + 10], topo[NMAX + 10];
static char col[NMAX + 10];

void build_network() {
    for (int u = 1; u <= 6 * n; u++) {
        V.link(id[u], u);

        for (int v : G[u]) {
            if (id[u] != id[v]) {
                T.link(id[v], id[u]);
                in[id[u]]++;
            }
        }
    }
}

void toposort() {
    queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        if (!in[i])
            q.push(i);
    }

    int tail = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo[tail++] = u;

        for (int v : T[u]) {
            in[v]--;

            if (!in[v])
                q.push(v);
        }
    }
}

void mark(int x) {
    col[x] = CANCEL;

    for (int v : T[x]) {
        if (!col[v])
            mark(v);
    }
}

void coloring() {
    for (int i = 1; i <= cnt; i++) {
        int u = topo[i];

        if (!col[u]) {
            col[u] = SELECT;

            for (int v : V[u]) {
                col[id[inv(v)]] = CANCEL;
            }
        } else if (col[u] == CANCEL)
            mark(u);
    }
}

int main() {
    initialize();

    bool found = false;
    for (int i = 0; !found && i < TMAX; i++) {
        G = N;

        for (int u = 1; u <= n; u++) {
            if (S[u] != X)
                continue;

            char c = randchr();
            setup(G, u, c);
        }

        memset(id, 0, sizeof(id));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(marked, 0, sizeof(marked));
        cur = cnt = 0;
        for (int u = 1; u <= 6 * n; u++) {
            if (!dfn[u])
                scc(u);
        }

        if (invalid())
            continue;

        found = true;
        build_network();
        toposort();
        coloring();

        for (int i = 1; i <= n; i++) {
            for (char c = A; c <= C; c++) {
                if (col[id[p(i, c, 0)]] == SELECT)
                    putchar(c - 32);
            }
        }
        putchar('\n');
    }

    if (!found)
        puts("-1");

    return 0;
}
