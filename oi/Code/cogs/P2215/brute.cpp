#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#pragma GCC optimize(2)
#define NMAX 100000
#define LOGN 18
#define MMAX 200000
#define ADD 0
#define DEL 1
#define BRK 2

struct Connection {
    int u;
    int v;
    int lca;
    int importance;
    bool finished;
};

int n, m;
vector<int> G[NMAX + 10];
int father[NMAX + 10];
int dist[NMAX + 10];
bool marked[NMAX + 10];
int root = 1;
int f[NMAX + 10][LOGN + 10];
Connection conn[MMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // Randmize root
    srand(233);
    root = (abs(rand()) % n) + 1;
    //    printf("%d\n",root);

    dist[root] = 0;
    father[root] = root;
    f[root][0] = root;
    memset(marked, 0, sizeof(marked));
    memset(f, 0, sizeof(f));
    marked[root] = true;
    queue<int> q;
    q.push(root);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (unsigned i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (!marked[v]) {
                marked[v] = true;
                father[v] = u;
                f[v][0] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
    //    for(int i=1;i<=n;i++){
    //  for(int j=0;j<=LOGN;j++){
    //      printf("f[%d][%d] = %d\n",i,j,f[i][j]);
    //  }
    //    }
}

int lca(int u, int v) {
    if (dist[u] < dist[v]) {
        swap(u, v);
    }

    int d = dist[u] - dist[v];
    for (int i = LOGN; i >= 0; i--) {
        if (d & (1 << i)) {
            u = f[u][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }

    return father[u];
}

inline bool is_broken(Connection *c, int x) {
    //    return lca(c->u,x)==x || lca(c->v, x)==x;
    return (lca(c->u, x) == x && lca(c->v, x) == c->lca) ||
           (lca(c->v, x) == x && lca(c->u, x) == c->lca);
}

vector<Connection *> current;
int answer(int x) {
    int vmax = -1;
    //    puts("Find max...");
    for (unsigned i = 0; i < current.size(); i++) {
        Connection *c = current[i];
        if (c->finished)
            continue;
        if (is_broken(c, x))
            continue;

        vmax = max(vmax, c->importance);
    }
    //    puts("Found.");
    return vmax;
}

int main() {
    freopen("network.in", "r", stdin);
    freopen("brute.out", "w", stdout);
    initialize();

    //    for(int i=1;i<=n;i++){
    //  for(int j=i;j<=n;j++){
    //      printf("LCA(%d, %d) = %d\n",i,j,lca(i,j));
    //  }
    //    }

    bool special = false;
    Connection *mconn;
    for (int timestamp = 1; timestamp <= m; timestamp++) {
        int type;
        scanf("%d", &type);

        switch (type) {
            case ADD: {
                int a, b, v;
                scanf("%d%d%d", &a, &b, &v);

                Connection &c = conn[timestamp];
                c.u = a;
                c.v = b;
                c.lca = lca(a, b);
                c.importance = v;
                c.finished = false;
                current.push_back(&c);

                if (v == 1000000000) {
                    special = true;
                    mconn = &c;
                }
            } break;
            case DEL: {
                int t;
                scanf("%d", &t);
                conn[t].finished = true;
            } break;
            case BRK: {
                int x;
                scanf("%d", &x);

                if (special) {
                    if (!is_broken(mconn, x)) {
                        printf("%d\n", 1000000000);
                        continue;
                    }
                }

                printf("%d\n", answer(x));
            } break;
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
