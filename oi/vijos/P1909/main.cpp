#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10000

static int n, m;
static int s, t;
static vector<int> G[NMAX + 10];
static vector<int> RG[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        RG[v].push_back(u);
    }

    scanf("%d%d", &s, &t);
}

static bool marked[NMAX + 10];
static bool connected[NMAX + 10];
static bool valid[NMAX + 10];

static void check_connection() {
    memset(marked, 0, sizeof(marked));

    queue<int> q;
    marked[t] = true;
    connected[t] = true;
    q.push(t);

    while (!q.empty()) {
        int u = q.front();;
        q.pop();

        for (size_t i = 0; i < RG[u].size(); i++) {
            int v = RG[u][i];
            connected[v] = true;

            if (!marked[v]) {
                marked[v] = true;
                q.push(v);
            }
        }
    }
}

static void check_avaliable() {
    memset(marked, 0, sizeof(marked));

    queue<int> q;
    marked[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();;
        q.pop();

        valid[u] = true;
        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (!connected[v])
                valid[u] = false;

            if (!marked[v]) {
                marked[v] = true;
                q.push(v);
            }
        }
    }
}

static int dist[NMAX + 10];

static void find_path() {
    for (int i = 1; i <= n; i++)
        dist[i] = -1;
    memset(marked, 0, sizeof(marked));

    if (!valid[s])
        return;

    queue<int> q;
    marked[s] = true;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            
            if (valid[v] && !marked[v]) {
                marked[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    initialize();
    check_connection();
    check_avaliable();
    find_path();

    if (dist[t] < 0)
        puts("-1");
    else
        printf("%d\n", dist[t]);

    return 0;
}
