#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, m;
static int price[NMAX + 10];
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d", price + i);

    for (int i = 0; i < m; i++) {
        int u, v, type;
        scanf("%d%d%d", &u, &v, &type);

        if (u == v)
            continue;

        G[u].push_back(v);
        if (type == 2)
            G[v].push_back(u);
    }
}

struct State {
    State(int _u, int _s)
        : u(_u), s(_s) {}

    int u;
    int s;
};

static bool marked[NMAX][3];
static int dist[NMAX][3];

static void SPFA() {
    for (int i = 1; i <= n; i++) {
        dist[i][0] = dist[i][1] = dist[i][2] = INT_MAX;
    }

    queue<State> q;
    q.push(State(1, 0));
    marked[1][0] = true;
    dist[1][0] = 0;

    while (!q.empty()) {
        State c = q.front();
        q.pop();
        marked[c.u][c.s] = false;

        for (size_t i = 0; i < G[c.u].size(); i++) {
            int v = G[c.u][i];

            if (dist[c.u][c.s] < dist[v][c.s]) {
                dist[v][c.s] = dist[c.u][c.s];

                if (!marked[v][c.s]) {
                    q.push(State(v, c.s));
                    marked[v][c.s] = true;
                }
            }

            if (c.s < 2) {
                int ndist = dist[c.u][c.s];

                if (c.s == 0)
                    ndist += price[c.u];
                if (c.s == 1)
                    ndist -= price[c.u];

                if (ndist < dist[v][c.s + 1]) {
                    dist[v][c.s + 1] = ndist;

                    if (!marked[v][c.s + 1]) {
                        q.push(State(v, c.s + 1));
                        marked[v][c.s + 1] = true;
                    }
                }
            }
        }
    }
}

int main() {
    initialize();

    SPFA();
    
    if (dist[n][2] > 0)
        puts("0");
    else
        printf("%d\n", -dist[n][2]);

    return 0;
}
