#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 4000

struct Edge {
    int v, w;
};

static int n, m1, m2;
static int L[2 * NMAX + 10], R[2 * NMAX + 10], K[2 * NMAX + 10];
static Edge *p[2 * NMAX + 10];
static vector<Edge*> G[NMAX + 10];

Edge* link(int u, int v, int w) {
    Edge *e = new Edge{v, w};
    G[u].push_back(e);
    return e;
}

bool spfa(int s) {
    static bool in[NMAX + 10];
    static int dist[NMAX + 10], cnt[NMAX + 10];
    memset(in, 0, s + 1);
    memset(dist, 0x3f, sizeof(int) * (s + 1));
    memset(cnt, 0, sizeof(int) * (s + 1));
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    in[s] = true;
    while (!q.empty()) {
        int u = q.front();
        in[u] = false;
        q.pop();
        if (cnt[u] > s + 5)
            return false;
        for (auto e : G[u]) {
            if (dist[e->v] > dist[u] + e->w) {
                dist[e->v] = dist[u] + e->w;
                cnt[e->v] = cnt[u] + 1;
                if (!in[e->v]) {
                    in[e->v] = true;
                    q.push(e->v);
                }
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m1, &m2);
        for (int i = 1; i <= m1; i++)
            scanf("%d%d%d", L + i, R + i, K + i);
        for (int i = m1 + 1; i <= m1 + m2; i++)
            scanf("%d%d%d", L + i, R + i, K + i);
        int s = n + 1;
        for (int i = 0; i <= s; i++)
            G[i].clear();
        link(s, 0, 0);
        //link(0, s, 0);
        auto ce1 = link(0, n, 0);
        auto ce2 = link(n, 0, 0);
        for (int i = 1; i <= n; i++)
            link(s, i, 0);
        for (int i = 1; i <= n; i++) {
            link(i, i - 1, 0);
            link(i - 1, i, 1);
        }
        for (int i = 1; i <= m1; i++)
            link(R[i], L[i] - 1, -K[i]);
        for (int i = m1 + 1; i <= m1 + m2; i++)
            p[i] = link(L[i] - 1, R[i], 0);

        int l = 0, r = n;
        while (l < r) {
            int S = (l + r) / 2;
            ce1->w = S;
            ce2->w = -S;
            for (int i = m1 + 1; i <= m1 + m2; i++)
                p[i]->w = S - K[i];
            if (spfa(s)) r = S;
            else l = S + 1;
        }

        printf("%d\n", l);
    }
    return 0;
}
