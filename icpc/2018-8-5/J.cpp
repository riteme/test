#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 500
#define INF 1000000000

struct Edge {
    Edge(int _v, int _c) : v(_v), c(_c), rev(NULL) {}
    int v, c;
    Edge *rev;
};

static int n, m, s, t, cnt, sum;
static unordered_map<int, int> id;
static int L[NMAX + 10], R[NMAX + 10], V[NMAX + 10], seq[NMAX + 10];
static int cur[NMAX + 10], lev[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

inline void link(int u, int v, int c) {
    // printf("%d -> %d (%d)\n", u, v, c);
    Edge *e = new Edge(v, c);
    Edge *re = new Edge(u, 0);
    e->rev = re;
    re->rev = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", L + i, R + i, V + i);
        sum += V[i];
        R[i]--;
        seq[++cnt] = L[i];
        seq[++cnt] = R[i];
    }

    sort(seq + 1, seq + cnt + 1);
    cnt = unique(seq + 1, seq + cnt + 1) - seq - 1;
    for (int i = 1; i <= cnt; i++)
        id[seq[i]] = i;

    s = n + cnt * 2; t = s + 1;
    // printf("n = %d, cnt = %d, s = %d\n", n, cnt, s);
    for (int i = 1; i <= n; i++) {
        link(s, i, V[i]);
        for (int j = 1; j <= cnt; j++) {
            if (L[i] <= seq[j] && seq[j] <= R[i])
                link(i, n + j, 1);
        }
    }

    for (int i = 1; i <= cnt; i++) {
        link(n + i, t, m);
        if (i == cnt) continue;
        link(n + cnt + i, t, (seq[i + 1] - seq[i] - 1) * m);
        for (int j = 1; j <= n; j++) {
            if (L[j] <= seq[i] + 1 && seq[i + 1] - 1 <= R[j])
                link(j, n + cnt + i, seq[i + 1] - seq[i] - 1);
        }
    }
}

bool bfs() {
    memset(lev, 0, sizeof(lev));
    lev[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto e : G[u]) {
            int v = e->v;
            if (!e->c || lev[v]) continue;
            lev[v] = lev[u] + 1;
            q.push(v);
        }
    }

    return lev[t];
}

int dfs(int x, int maxflow) {
    if (x == t) return maxflow;
    int ret = 0;
    for (int &i = cur[x]; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->v;
        if (lev[x] + 1 != lev[v] || !e->c) continue;
        int flow = min(maxflow - ret, e->c);
        flow = dfs(v, flow);
        e->c -= flow;
        e->rev->c += flow;
        ret += flow;
        if (ret >= maxflow) break;
    }
    return ret;
}

int maxflow() {
    int ret = 0;
    while (bfs()) {
        memset(cur, 0, sizeof(cur));
        ret += dfs(s, INF);
        // printf("ret = %d\n", ret);
    }
    return ret;
}

int main() {
    initialize();
    puts(maxflow() == sum ? "YES" : "NO");

    return 0;
}
