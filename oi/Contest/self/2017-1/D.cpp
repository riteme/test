#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c)) {
        c = _getchar();
    }

    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 5000000
#define MMAX 1000

static int n, m;
static vector<int> G[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static int father[NMAX + 10];
static int depth[NMAX + 10];
static int size[NMAX + 10];
static int top[NMAX + 10];

static void dfs(int x) {
    in[x] = ++timestamp;
    size[x] = 1;

    for (auto v : G[x]) {
        depth[v] = depth[x] + 1;
        dfs(v);
        size[x] += size[v];
    }
    out[x] = timestamp;
}

static void decompose(int x) {
    int next = 0;
    for (int v : G[x]) {
        if (size[v] > size[next])
            next = v;
    }

    if (next) {
        top[next] = top[x];
        decompose(next);
    }

    for (int v : G[x]) {
        if (v != next) {
            top[v] = v;
            decompose(v);
        }
    }
}

inline int evaluate_lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = father[top[u]];
        else
            v = father[top[v]];
    }

    if (depth[u] < depth[v])
        return u;
    return v;
}

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        G[u].push_back(v);
        father[v] = u;
    }

    dfs(1);
    top[1] = 1;
    decompose(1);
}

int main() {
    initialize();

    in[n + 1] = INT_MAX;
    in[n + 2] = INT_MIN;
    while (m--) {
        int k;
        k = readint();

        int left = n + 1;
        int right = n + 2;
        for (int i = 1; i <= k; i++) {
            int x;
            x = readint();

            if (in[x] < in[left])
                left = x;
            if (out[x] > out[right])
                right = x;
        }

        printf("%d\n", evaluate_lca(left, right));
    }

    return 0;
}

