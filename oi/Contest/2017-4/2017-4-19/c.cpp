// #define NDEBUG
// #define USE_FILE_IO

#include <cassert>
#include <cstdio>
#include <cstring>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 600

static int n, m;
static vector<int> G[NMAX + 10];
static int match[NMAX + 10];

#define ODD 1
#define EVEN 2

static deque<int> q;
static int set[NMAX + 10];
static int link[NMAX + 10];
static int mark[NMAX + 10];
static char type[NMAX + 10];

inline int id(int u) {
    return set[u] ? set[u] = id(set[u]) : u;
}

inline void union_set(int x, int y) {
    x = id(x);
    y = id(y);

    if (x != y)
        set[x] = y;
}

inline int evaluate_lca(int u, int v) {
    static int t = 0;
    t++;
    while (true) {
        if (u) {
            u = id(u);
            if (mark[u] == t)
                return u;
            mark[u] = t;
            u = link[match[u]];
        }

        swap(u, v);
    }
}

inline void process(int u, int p) {
    while (u != p) {
        int a = match[u], b = link[a];

        if (id(b) != p)
            link[b] = a;

        if (type[a] == ODD) {
            type[a] = EVEN;
            q.push_back(a);
        }
        assert(type[b] == EVEN);
        union_set(u, a);
        union_set(a, b);
        u = b;
    }
}

bool bfs(int s) {
    memset(set, 0, sizeof(set));
    memset(link, 0, sizeof(link));
    memset(type, 0, sizeof(type));
    q.clear();
    q.push_back(s);
    type[s] = EVEN;

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        for (int v : G[u]) {
            if (!type[v]) {
                type[v] = ODD;
                link[v] = u;

                if (match[v]) {
                    int p = match[v];
                    type[p] = EVEN;
                    q.push_back(p);
                } else {
                    // printf("--- PATH BEGIN ---\n");
                    while (u) {
                        int nv = match[u];
                        // printf("u = %d, v = %d\n", u, v);
                        match[u] = v;
                        match[v] = u;
                        v = nv;
                        u = link[v];
                    }
                    // printf("--- PATH END ---\n");

                    return true;
                }
            } else if (type[v] == EVEN && id(u) != id(v)) {
                int p = evaluate_lca(u, v);

                if (id(u) != p)
                    link[u] = v;
                if (id(v) != p)
                    link[v] = u;

                process(u, p);
                process(v, p);
            }
        }
    }

    return false;
}

int blossom_algorithm() {
    int ret = 0;
    for (int u = 1; u <= n; u++) {
        if (!match[u] && bfs(u))
            ret++;
    }

    return ret;
}

void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

static char s[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (s[i] == '(' && s[j] == ')')
                add_edge(i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        
        for (int j = 1; j <= m; j++) {
            if (s[j] == '1')
                add_edge(i, n + j);
        }
    }

    int tmp = n;
    n = n + m;
    m = tmp;

    for (int i = 1; i <= n; i++) {
        random_shuffle(G[i].begin(), G[i].end());
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif
    initialize();

    blossom_algorithm();
    for (int i = 1; i <= m; i++) {
        if (match[i] > m)
            printf("%d\n", match[i] - m);
        else
            puts("-1");
    }

    return 0;
}
