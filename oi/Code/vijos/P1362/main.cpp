#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 300

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, s;
static vector<Edge *> G[NMAX + 10];
static int dist[NMAX + 10][NMAX + 10];
static int maxlen;

static int p;
static bool marked[NMAX + 10];
static void dfs(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (!marked[v]) {
            dist[p][v] = dist[p][x] + e->w;
            dfs(v);
        }
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &s);

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for

    for (int i = 1; i <= n; i++) {
        memset(marked, 0, sizeof(marked));
        p = i;
        dfs(i);
    }  // for
}

static int len;
static int path[NMAX + 10];
static int dist_to_next[NMAX + 10];

static bool scan_path(int x, int pos, int t) {
    if (x == t) {
        len = pos;
        path[pos] = t;
        return true;
    }

    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (marked[v])
            continue;

        if (scan_path(v, pos + 1, t)) {
            path[pos] = x;
            dist_to_next[pos] = e->w;

            return true;
        }
    }  // for

    return false;
}

static int query(int l, int r) {
    int result = 0;

    for (int i = 1; i <= n; i++) {
        int mindist = INT_MAX;

        for (int j = l; j <= r; j++) {
            mindist = min(mindist, dist[i][path[j]]);
        }

        result = max(result, mindist);
    }

    return result;
}

int main() {
    freopen("core.in", "r", stdin);
    freopen("core.out", "w", stdout);

    initialize();

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (dist[i][j] > maxlen)
                maxlen = dist[i][j];

    int answer = INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist[i][j] == maxlen) {
                memset(marked, 0, sizeof(marked));
                scan_path(i, 1, j);

                int l = 1, r = 1;
                int curlen = 0;
                int result = INT_MAX;
                while (l <= len && r <= len) {
                    if (r < l)
                        r = l;

                    while (r < len && curlen + dist_to_next[r] <= s) {
                        curlen += dist_to_next[r];
                        r++;
                    }

                    result = min(result, query(l, r));
                    curlen -= dist_to_next[l];
                    l++;
                }

                answer = min(answer, result);
            }
        }  // for
    }      // for

    printf("%d\n", answer);

    return 0;
}  // function main
