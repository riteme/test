#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE, _sz;
char _buf[BUFFERSIZE];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        _sz = fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _pos < _sz ? _buf[_pos++] : 0;
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getc(); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
}

#define NMAX 10000

int n, q, cur;
vector<int> G[NMAX + 10];
int in[NMAX + 10], out[NMAX + 10];
int top[NMAX + 10], fa[NMAX + 10];
int dep[NMAX + 10];

void dfs(int x, int f) {
    in[x] = ++cur;
    top[x] = 1;
    for (int v : G[x]) if (v != f) {
        fa[v] = x;
        dep[v] = dep[x] + 1;
        dfs(v, x);
        top[x] += top[v];
    }
    out[x] = cur;
}

void decompose(int x, int f) {
    int u = 0;
    for (int v : G[x])
    if (v != f && top[v] > top[u]) u = v;
    if (u) {
        top[u] = top[x];
        decompose(u, x);
    }
    for (int v : G[x]) if (v != f && v != u) {
        top[v] = v;
        decompose(v, x);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

bool onpath(int u, int v, int x) {
    int p = lca(u, v);
    return in[p] <= in[x] && in[x] <= out[p] &&
        ((in[x] <= in[u] && in[u] <= out[x]) ||
         (in[x] <= in[v] && in[v] <= out[x]));
}

void initialize() {
    read(n);
    for (int i = 1; i <= n; i++)
        G[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u); read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dep[1] = 1;
    dfs(1, 0);
    top[1] = 1;
    decompose(1, 0);
}

int main() {
    int T;
    read(T);
    for (int _t = 1; _t <= T; _t++) {
        printf("Case %d:\n", _t);
        initialize();
        read(q);

        while (q--) {
            int K;
            read(K);
            int u, v;
            read(u); read(v);
            for (int i = 1; i < K; i++) {
                int x, y;
                read(x); read(y);

                if (!u) continue;
                int p1 = lca(u, x);
                int p2 = lca(u, y);
                int p3 = lca(v, x);
                int p4 = lca(v, y);
                int u0 = 0, v0 = 0;
                auto add = [&u0, &v0](int p) {
                    if (dep[p] > dep[u0]) {
                        v0 = u0;
                        u0 = p;
                    } else if (dep[p] > dep[v0])
                        v0 = p;
                };
                add(p1); add(p2); add(p3); add(p4);

                if (u0 != v0 || (onpath(u, v, u0) && onpath(x, y, u0))) {
                    u = u0;
                    v = v0;
                } else u = 0;
            }

            if (!u) puts("0");
            else {
                int p = lca(u, v);
                printf("%d\n", dep[u] + dep[v] - 2 * dep[p] + 1);
            }
        }
    }

    return 0;
}