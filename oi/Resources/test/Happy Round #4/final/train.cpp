#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

#define NMAX 100000
#define MMAX 300000
#define INFTY 2000000000000.0

struct Edge {
    int u;
    int v;
    double w;

    int another(int x) {
        return x == u ? v : u;
    }
};  // struct Edge

static int n;
static int m;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int set[NMAX + 10];
static double f[NMAX + 10][3];
static queue<int, deque<int>> q;
static bool marked[NMAX + 10];

template <typename T>
inline T abs(const T &a) {
    return a > 0 ? a : -a;
}

inline double w(double a, int cnt) {
    cnt %= 3;
    switch (cnt) {
        case 0: return a;
        case 1: return abs(1 / (1 - a));
        case 2: return abs((a - 1) / a);
    }  // switch to cnt

    return 233.3333;
}

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    set[find_set(x)] = find_set(y);
}

void initialize() {
    scanf("%d%d", &n, &m);

    make_set();
    for (int i = 0; i < m; i++) {
        int u, v;
        double a;
        scanf("%d%d%lf", &u, &v, &a);

        union_set(u, v);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = a;
        G[u].push_back(&edges[i]);
        G[v].push_back(&edges[i]);
    }

    memset(marked, false, sizeof(marked));
}

void spfa() {
    q.push(n);
    marked[n] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        marked[u] = false;

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->another(u);
            bool flag = false;

            if (f[v][0] > f[u][1] + w(e->w, 0)) {
                f[v][0] = f[u][1] + w(e->w, 0);
                flag = true;
            }

            if (f[v][1] > f[u][2] + w(e->w, 1)) {
                f[v][1] = f[u][2] + w(e->w, 1);
                flag = true;
            }

            if (f[v][2] > f[u][0] + w(e->w, 2)) {
                f[v][2] = f[u][0] + w(e->w, 2);
                flag = true;
            }

            if (flag and !marked[v]) {
                q.push(v);
                marked[v] = true;
            }
        }  // for
    }      // while
}

int main() {
    freopen("train.in", "r", stdin);
    freopen("train.out", "w", stdout);
    initialize();

    if (find_set(1) != find_set(n)) {
        printf("-1");
        return 0;
    }

    f[n][0] = f[n][1] = f[n][2] = 0.0;
    for (int i = 1; i < n; i++) {
        f[i][0] = f[i][1] = f[i][2] = INFTY;
    }  // for

    spfa();

    printf("%.3lf", f[1][0]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
