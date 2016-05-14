#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#pragma comment(linker, "/STACK:102400000,102400000")

#define NMAX 100000

static int n;
static vector<int> G[NMAX + 10];

#define BUFFERSIZE 1024
static unsigned _p = BUFFERSIZE;
static char _buffer[BUFFERSIZE];
inline char _getchar() {
    if (_p == BUFFERSIZE) {
        fread(_buffer, 1, BUFFERSIZE, stdin);
        _p = 0;
    }

    return _buffer[_p++];
}

inline int readint() {
    char c = _getchar();
    int x = 0;
    while (c < '0' || c > '9') {
        c = _getchar();
    }  // while
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = _getchar();
    }  // while
    return x;
}

static void read_graph() {
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for
}

static void initialize() {
    // scanf("%d", &n);
    n = readint();

    read_graph();
}

typedef long long ntype;
static ntype size[NMAX + 10];
static ntype sum[NMAX + 10];
static bool marked[NMAX + 10];
static ntype answer[NMAX + 10];

static void dfs1(int x) {
    marked[x] = true;
    size[x] = 1;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            dfs1(v);

            size[x] += size[v];
            sum[x] += sum[v] + size[v];
        }
    }  // for
}

inline void rotate(int p, int x) {
    size[p] -= size[x];
    sum[p] -= sum[x] + size[x];
    size[x] += size[p];
    sum[x] += sum[p] + size[p];
}

static void dfs2(int x) {
    marked[x] = true;
    answer[x] = sum[x];

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            rotate(x, v);
            dfs2(v);
            rotate(v, x);
        }
    }  // for
}

int main() {
    initialize();

    dfs1(1);
    memset(marked, false, sizeof(marked));
    dfs2(1);

    for (int i = 1; i <= n; i++) {
        printf("%lld\n", answer[i]);
    }  // for

    return 0;
}  // function main
