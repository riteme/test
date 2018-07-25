#include <cctype>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long u64;

#define INPUT_BUFFERSIZE 65536
static size_t ipos = INPUT_BUFFERSIZE;
static char ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (ipos == INPUT_BUFFERSIZE) {
        ipos = 0;
        fread(ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return ibuffer[ipos++];
}

template <typename TReturn>
inline TReturn read() {
    TReturn x = 0;
    char c = _getchar();

    while (!isdigit(c)) {
        c = _getchar();
    }  // while

    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }  // while

    return x;
}

#define OUTPUT_BUFFERSIZE 4000000
static size_t opos;
static char obuffer[OUTPUT_BUFFERSIZE];

inline void put_u64(u64 u) {
    opos += sprintf(obuffer + opos, "%llu\n", u);
}

inline void flush_to_stdout() {
    fwrite(obuffer, 1, opos, stdout);
}

#define NMAX 20000
#define SPACESIZE 61

struct Basis {
    void append(u64 u) {
        for (int i = SPACESIZE - 1; i >= 0; i--) {
            if ((u >> i) & 1) {
                if (vec[i])
                    u ^= vec[i];
                else {
                    vec[i] = u;
                    break;
                }
            }
        }  // for
    }

    u64 max() {
        u64 u = 0;
        for (int i = SPACESIZE - 1; i >= 0; i--) {
            if (((~u) >> i) & 1)
                u ^= vec[i];
        }  // for

        return u;
    }

    Basis &operator+=(const Basis &b) {
        for (int i = 0; i < SPACESIZE; i++) {
            if (b.vec[i])
                append(b.vec[i]);
        }  // for

        return *this;
    }

    u64 vec[SPACESIZE];
};  // struct Basis

struct TimelinedBasis {
    void append(u64 u, int t) {
        for (int i = SPACESIZE - 1; i >= 0; i--) {
            if ((u >> i) & 1) {
                if (vec[i]) {
                    u64 v = vec[i];

                    if (t > timestamp[i]) {
                        vec[i] = u;
                        swap(timestamp[i], t);
                    }

                    u ^= v;
                } else {
                    vec[i] = u;
                    timestamp[i] = t;
                    break;
                }
            }
        }  // for
    }

    Basis cut(int t) {
        Basis b;

        for (int i = 0; i < SPACESIZE; i++) {
            b.vec[i] = timestamp[i] >= t ? vec[i] : 0;
        }  // for

        return b;
    }

    u64 vec[SPACESIZE];
    int timestamp[SPACESIZE];
};  // struct Basis

static int n, m;
static u64 w[NMAX + 10];
static vector<int> G[NMAX + 10];
static int depth[NMAX + 10];
static int size[NMAX + 10];
static int father[NMAX + 10];
static int top[NMAX + 10];
static TimelinedBasis pre[NMAX + 10];

void dfs(int x, int f) {
    size[x] = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f)
            continue;

        depth[v] = depth[x] + 1;
        pre[v] = pre[x];
        pre[v].append(w[v], depth[v]);
        father[v] = x;

        dfs(v, x);

        size[x] += size[v];
    }  // for
}

void decompose(int x, int f) {
    int nxt = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f)
            continue;

        if (size[v] > size[nxt])
            nxt = v;
    }  // for

    if (nxt) {
        top[nxt] = top[x];
        decompose(nxt, x);
    }

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == nxt || v == f)
            continue;

        top[v] = v;
        decompose(v, x);
    }  // for
}

inline int evaluate_lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = father[top[u]];
        else
            v = father[top[v]];
    }  // while

    return depth[u] < depth[v] ? u : v;
}

void initialize() {
    // scanf("%d%d", &n, &m);
    n = read<int>();
    m = read<int>();

    for (int i = 1; i <= n; i++) {
        // scanf("%llu", w + i);
        w[i] = read<u64>();
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = read<int>();
        v = read<int>();

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    depth[1] = 1;
    memset(pre + 1, 0, sizeof(TimelinedBasis));
    pre[1].append(w[1], 1);
    dfs(1, 0);
    top[1] = 1;
    decompose(1, 0);
}

int main() {
    initialize();

    while (m--) {
        int u, v, p;
        // scanf("%d%d", &u, &v);
        u = read<int>();
        v = read<int>();
        p = evaluate_lca(u, v);

        Basis v1 = pre[u].cut(depth[p]);
        v1 += pre[v].cut(depth[p]);
        // printf("%llu\n", v1.max());
        put_u64(v1.max());
    }  // while

    flush_to_stdout();

    return 0;
}  // function main
