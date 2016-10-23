#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define NMAX 20000
#define MMAX 1000000
#define NO_COLOR 0
#define WHITE 1
#define BLACK 2

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u;
    int v;
    int w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];
static char color[NMAX + 10];
static int vcnt;
static int values[MMAX + 10];

inline int rev(int c) {
    if (c == WHITE)
        return BLACK;
    else
        return WHITE;
}

static bool coloring(int x, int maxw) {
    queue<int> q;
    q.push(x);
    color[x] = WHITE;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (e->w <= maxw)
                continue;

            if (color[v]) {
                if (color[v] != rev(color[u]))
                    return false;
            } else {
                color[v] = rev(color[u]);
                q.push(v);
            }
        }  // for
    }      // while

    return true;
}

static bool test(int maxw) {
    memset(color, 0, sizeof(color));

    for (int i = 1; i <= n; i++) {
        if (!color[i])
            if (!coloring(i, maxw))
                return false;
    }  // for

    return true;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        Edge *e = new Edge(u, v, w);

        G[u].push_back(e);
        G[v].push_back(e);
        values[i] = w;
    }  // for

    sort(values + 1, values + m + 1);
    vcnt = unique(values + 1, values + m + 1) - values - 1;
}

int main() {
    initialize();

    int left = 0, right = vcnt;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (test(values[mid]))
            right = mid;
        else
            left = mid;
    }  // while

    if (left != right && !test(values[left]))
        left = right;

    printf("%d\n", values[left]);

    return 0;
}  // function main
