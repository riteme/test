// #define NDEBUG
// #define INITIAL_MATCH
// #define USE_FILE_IO

#include <cassert>
#include <cstdio>
#include <cstring>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500

static int n, m;
static vector<int> G[NMAX + 10];
static int match[NMAX + 10];

#define ODD 1
#define EVEN 2

static deque<int> q;
static int set[NMAX + 10];    // 并查集
static int link[NMAX + 10];   // 双向链表
static int mark[NMAX + 10];   // 用于求LCA
static char type[NMAX + 10];  // 顶点类型（奇点还是偶点），0表示未访问

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
    // 标记路径的方法来求LCA
    static int t = 0;
    t++;
    while (true) {
        if (u) {
            u = id(u);  // 注意花已经缩成一个点了
            if (mark[u] == t)
                return u;
            mark[u] = t;
            u = link[match[u]];
        }

        swap(u, v);  // u和v轮流走
    }
}

inline void process(int u, int p) {
    // 缩花
    while (u != p) {
        int a = match[u], b = link[a];

        if (id(b) != p)
            link[b] = a;

        // 原先的奇点变为偶点
        if (type[a] == ODD) {
            type[a] = EVEN;
            q.push_back(a);
        }

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

                // 有匹配则继续走
                if (match[v]) {
                    int p = match[v];
                    type[p] = EVEN;
                    q.push_back(p);
                } else {
                    // 没有匹配说明找到了增广路径
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
            } else if (type[v] == EVEN && id(u) != id(v)) {  // 注意是不是在一朵花内
                // 连接两个偶点，进行缩花
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

void initialize() {
    scanf("%d%d", &n, &m);

#ifdef INITIAL_MATCH
    int c;
    scanf("%d", &c);
#endif

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

#ifdef INITIAL_MATCH
    for (int i = 0; i < c; i++) {
        int u, v;
        scanf("%d%d", &u, &v); 
        match[u] = v;
        match[v] = u;
    }
#endif
}

int main() {
#ifdef USE_FILE_IO
    freopen("data.in", "r", stdin);
#endif
    initialize();

    printf("%d\n", blossom_algorithm());
    for (int u = 1; u <= n; u++) {
        printf("%d ", match[u]);
    }
    printf("\n");

    return 0;
}
