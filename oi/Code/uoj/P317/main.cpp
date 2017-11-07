/**
 * TODO:
 *     1. 2-SAT: scc & construct
 *     2. Randomized test (about 200 times)
 */

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define TMAX 200

#define A 'a'
#define B 'b'
#define C 'c'
#define X 'x'
#define T 0
#define F 1

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

static stack<int> stk;
static bool marked[NMAX + 10];
static int dfn[NMAX + 10], low[NMAX + 10], cur;
static int id[NMAX + 10], cnt;

void _scc(int x) {
    dfn[x] = low[x] = ++cur;
    stk.push(x);

    for (int v : G[x]) {
        if (marked[v])
            continue;
        if (!dfn[v])
            _scc(v);
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

void scc(int x) {
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(marked, 0, sizeof(marked));
    cur = 0;
    _scc(x);
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
    T.link(p(i, c, F), p(i, c, T));
    switch (c) {
        case A: {
            T.bilink(p(i, B, T), p(i, C, F));
            T.bilink(p(i, C, T), p(i, B, F));
        } break;

        case B: {
            T.bilink(p(i, A, T), p(i, C, F));
            T.bilink(p(i, C, T), p(i, A, F));
        } break;

        case C: {
            T.bilink(p(i, A, T), p(i, B, F));
            T.bilink(p(i, B, T), p(i, A, F));
        } break;
    }
}

void initialize() {
    srand(time(0));
    scanf("%d%d%s%d", &n, &d, S, &m);

    for (int i = 1; i <= n; i++) {
        if (S[i] == X)
            continue;

        setup(N, i, S[i]);
    }
}

int main() {
    initialize();

    bool found = false;
    for (int i = 0; i < TMAX; i++) {
        G = N;

        for (int u = 1; u <= n; u++) {
            if (S[u] != X)
                continue;

            char c = randchr();
            setup(G, u, c);
        }

        for (int u = 1; u <= n; u++) {
            if (!dfn[u])
                scc(u);
        }

        if (invalid())
            continue;

        // TODO: Construction
    }

    if (!found)
        puts("-1");

    return 0;
}
