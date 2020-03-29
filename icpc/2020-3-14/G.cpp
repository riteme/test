#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000

struct Edge {
    int v;
    double w;
};

int n;
double ln[101];
vector<Edge> G[NMAX + 10];
double dist[NMAX + 10];

void solve() {
    for (int i = 1; i <= n; i++)
        G[i].clear();

    for (int u = 1; u <= n; u++) {
        int c;
        scanf("%d", &c);
        G[u].reserve(c);
        for (int i = 0; i < c; i++) {
            int v, d;
            scanf("%d%d", &v, &d);
            if (d == 100)
                continue;
            G[u].push_back({v, ln[100 - d]});
        }
    }

    int s, t, D;
    scanf("%d%d%d", &s, &t, &D);
    for (int i = 1; i <= n; i++)
        dist[i] = 1e99;
    dist[s] = 0;
    struct State {
        int u;
        double t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    priority_queue<State> q;
    q.push({s, 0.0});
    do {
        State _ = q.top();
        q.pop();
        if (_.t > dist[_.u])
            continue;

        int u = _.u;
        for (int i = 0; i < G[u].size(); i++) {
            Edge &e = G[u][i];
            int v = e.v;
            if (dist[v] > _.t + e.w) {
                dist[v] = _.t + e.w;
                q.push({v, dist[v]});
            }
        }
    } while (!q.empty());

    if (dist[t] >= 1e99)
        puts("IMPOSSIBLE!");
    else
        printf("%.2lf\n", D * (1 - exp(-dist[t])));
}

int main() {
    for (int i = 1; i < 100; i++)
        ln[i] = -log(i * 0.01);
    ln[100] = 0;

    while (scanf("%d", &n) != EOF)
        solve();

    return 0;
}