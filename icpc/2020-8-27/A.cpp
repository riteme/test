#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 200
#define EMAX 100000
#define BASE 100000000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

struct Edge {
    int u, v, c;
    int nxt;
    i64 w;
};

int n, m, s, t, ecnt;
int G[NMAX + 10];
Edge e[EMAX + 10];

void link(int u, int v, int c, i64 w) {
    e[ecnt + 1] = {u, v, c, G[u], w};
    e[ecnt + 2] = {v, u, 0, G[v], -w};
    G[u] = ecnt + 1;
    G[v] = ecnt + 2;
    ecnt += 2;
}

bool mark[NMAX + 10];
int pa[NMAX + 10];
i64 dist[NMAX + 10];

void spfa() {
    memset(dist + 1, 0x3f, sizeof(i64) * t);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    do {
        int u = q.front();
        q.pop();
        mark[u] = false;
        for (int i = G[u]; i; i = e[i].nxt)
        if (e[i].c > 0) {
            int v = e[i].v;
            if (dist[v] > dist[u] + e[i].w) {
                pa[v] = i;
                dist[v] = dist[u] + e[i].w;
                if (!mark[v]) {
                    mark[v] = true;
                    q.push(v);
                }
            }
        }
    } while (!q.empty());
}

i64 mcmf() {
    i64 rax = 0;

    while (true) {
        spfa();
        if (dist[t] >= INF)
            break;

        int x = t;
        i64 mic = INF;
        do {
            int i = pa[x];
            mic = min(mic, (i64) e[i].c);
            x = e[i].u;
        } while (x != s);

        rax += mic * dist[t];

        x = t;
        do {
            int i = pa[x];
            e[i].c -= mic;
            e[i ^ 1].c += mic;
            x = e[i].u;
        } while (x != s);
    }

    return rax;
}

i64 w[NMAX + 10][NMAX + 10];
int perm[NMAX + 10];

void _main() {
    i64 ans0 = 0;
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        scanf("%lld", w[i] + j);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", perm + i);
        ans0 += w[i][perm[i]];
    }

    s = n + m + 1;
    t = s + 1;
    ecnt = 1;
    memset(G + 1, 0, sizeof(int) * t);

    for (int i = 1; i <= n; i++) {
        link(s, i, 1, 0);
    }
    for (int j = 1; j <= m; j++) {
        link(n + j, t, 1, 0);
    }
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        link(i, n + j, 1, -(w[i][j] * BASE + (j == perm[i] ? 1 : 0)));
    }

    i64 ret = -mcmf();
    int cnt = n - ret % BASE;
    i64 ans = ret / BASE;
    i64 inc = ans - ans0;
    printf("%d %lld\n", cnt, inc);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        _main();
    }
    return 0;
}
