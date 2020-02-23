#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 400
#define QMAX 100000
#define INF 0x3f3f3f3f

int n, m, q, seq[NMAX + 10];
int t[NMAX + 10];
int G[NMAX + 10][NMAX + 10];
int W[NMAX + 10][NMAX + 10];
vector<int> pre[NMAX + 10], suf[NMAX + 10];
struct Query {
    int s, t, ans;
} op[QMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    memset(G, 0x3f, sizeof(G));
    for (int i = 1; i <= n; i++) {
        G[i][i] = 0;
        seq[i] = i;
        scanf("%d", t + i);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u][v] = G[v][u] = w;
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int k, t;
        scanf("%d%d%d%d", &op[i].s, &op[i].t, &k, &t);
        if (t == 0)
            pre[k].push_back(i);
        else
            suf[k].push_back(i);
    }
}

void solve(vector<int> *li) {
    memcpy(W, G, sizeof(W));
    int p = 1;
    for (int k = 1; k <= n; k++) {
        int u = seq[k];
        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            W[i][j] = min(W[i][j], W[i][u] + W[u][j]);

        if (k < n && t[u] == t[seq[k + 1]])  // process same temps
            continue;

        for (int x : li[p]) {
            int s = op[x].s;
            int t = op[x].t;
            op[x].ans = W[s][t] < INF ? W[s][t] : -1;
        }
        p++;
    }

    for ( ; p <= n; p++)  // process remaining requests
    for (int x : li[p]) {
        int s = op[x].s;
        int t = op[x].t;
        op[x].ans = W[s][t] < INF ? W[s][t] : -1;
    }
}

int main() {
    initialize();

    sort(seq + 1, seq + n + 1, [](int u, int v) {
        return t[u] < t[v];
    });
    solve(pre);
    sort(seq + 1, seq + n + 1, [](int u, int v) {
        return t[u] > t[v];
    });
    solve(suf);

    for (int i = 1; i <= q; i++)
        printf("%d\n", op[i].ans);
    return 0;
}