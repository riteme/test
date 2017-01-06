#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 10000
#define RMMAX 800  // Soft limit

static int n, m;
static int U[MMAX + 10];
static int V[MMAX + 10];
static int tour[NMAX + 10];
static int id[NMAX + 10];
static bool W[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    memset(W, 0, sizeof(W));
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u == v || W[u][v]) {
            i--;
            m--;
        } else {
            U[i] = u;
            V[i] = v;
            W[u][v] = W[v][u] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", tour + i);
        id[tour[i]] = i;
    }
}

#define BLACK 1
#define WHITE -1

static vector<int> G[RMMAX + 10];
static signed char color[RMMAX + 10];

inline bool is_deleted(int p) {
    return id[U[p]] + 1 == id[V[p]] ||
           id[V[p]] + 1 == id[U[p]] ||
           (id[U[p]] == 1 && id[V[p]] == n) ||
           (id[U[p]] == n && id[V[p]] == 1);
}

inline bool in(int l, int r, int p) {
    return l < p && p < r;
}

inline bool out(int l, int r, int p) {
    return p < l || r < p;
}

inline bool is_intersect(int a, int b) {
    int al = min(id[U[a]], id[V[a]]);
    int ar = max(id[U[a]], id[V[a]]);
    int bl = id[U[b]];
    int br = id[V[b]];

    return (in(al, ar, bl) && out(al, ar, br)) ||
           (in(al, ar, br) && out(al, ar, bl));
}

static void setup() {
    for (int i = 1; i <= m; i++) {
        G[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        if (is_deleted(i))
            continue;

        for (int j = i + 1; j <= m; j++) {
            if (is_deleted(j))
                continue;

            if (is_intersect(i, j)) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
}

static bool bfs(int s) {
    queue<int> q;
    q.push(s);
    color[s] = WHITE;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (color[v] != 0) {
                if (color[v] != -color[u])
                    return false;
            } else {
                color[v] = -color[u];
                q.push(v);
           }
        }
    }

    return true;
}

static bool judge() {
    setup();

    memset(color, 0, sizeof(color));
    for (int i = 1; i <= m; i++) {
        if (color[i] == 0 && !bfs(i))
            return false;
    }

    return true;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        if (m > RMMAX) {
            puts("NO");
            continue;
        }
    
        puts(judge() ? "YES" : "NO");
    }

    return 0;
}
