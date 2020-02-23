#include <cstring>
#include <climits>

#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 5000

typedef long long i64;

struct Edge {
    int v;
    i64 w;
};

int n, m;
unordered_map<string, int> id;
vector<Edge> G[NMAX + 10];
bool mark[NMAX + 10];
int dist[NMAX + 10];
i64 mi[NMAX + 10];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    n++;
    id["English"] = 1;
    for (int i = 2; i <= n; i++) {
        string name;
        cin >> name;
        id[name] = i;
        mi[i] = LLONG_MAX;
    }
    for (int i = 0; i < m; i++) {
        string un, vn;
        int w;
        cin >> un >> vn >> w;
        int u = id[un];
        int v = id[vn];
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    queue<int> q;
    q.push(1);
    mark[1] = true;
    do {
        int u = q.front();
        q.pop();
        for (auto &e : G[u]) {
            if (!mark[e.v]) {
                mark[e.v] = true;
                dist[e.v] = dist[u] + 1;
                q.push(e.v);
            }
            if (dist[u] + 1 == dist[e.v])
                mi[e.v] = min(mi[e.v], e.w);
        }
    } while (!q.empty());

    bool ok = true;
    for (int i = 1; i <= n; i++)
        ok &= mark[i];
    if (ok) {
        i64 ans = 0;
        for (int i = 2; i <= n; i++)
            ans += mi[i];
        printf("%lld\n", ans);
    } else cout << "Impossible" << endl;

    return 0;
}
