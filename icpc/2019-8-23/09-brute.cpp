#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 30

typedef long long i64;

static struct Edge {
    bool enabled;
    int u, v;

    int nxt(int x) const {
        return u == x ? v : u;
    }
} e[NMAX * NMAX + 1];
static int n, m, cnt, dist[2 * NMAX + 1];
static vector<Edge*> G[2 * NMAX + 1];
static bool mark[2 * NMAX + 1];
static i64 sum[2 * NMAX + 1];

int main(int argc, char *argv[]) {
    //scanf("%d%d", &n, &m);
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        e[cnt] = {false, i, n + j};
        G[i].push_back(e + cnt);
        G[n + j].push_back(e + cnt);
        cnt++;
    }
    long long num = 0;
    for (int s = 0; s < (1 << cnt); s++) {
        for (int i = 0; i < cnt; i++)
            e[i].enabled = (s >> i) & 1;
        queue<int> q;
        q.push(1);
        memset(mark, 0, sizeof(mark));
        memset(dist, 0, sizeof(dist));
        mark[1] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto e : G[u]) if (e->enabled) {
                int v = e->nxt(u);
                if (mark[v]) continue;
                dist[v] = dist[u] + 1;
                mark[v] = true;
                q.push(v);
            }
        }
        for (int i = 1; i <= m; i++) {
            num += dist[n + i];
            sum[dist[n + i]]++;
        }
    }
    long long dem = (1LL << cnt) * m;
    auto r = __gcd(num, dem);
    num /= r; dem /= r;
    for (int i = 1; i <= 2 * min(n, m) - 1; i++)
        if (sum[i]) printf("%2d: %lld\n", i, sum[i]);
    printf("%lld/%lld (%lld/%lld)\n", num, dem, num * r, dem * r);
    return 0;
}
