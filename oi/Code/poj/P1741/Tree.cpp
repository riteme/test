#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10000

struct Edge {
    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, k;
static vector<Edge *> G[NMAX + 10];
static int cnt;
static int dist[NMAX + 10];
static int totalsize;
static int size[NMAX + 10];
static int maxsize[NMAX + 10];
static bool marked[NMAX + 10];

inline void add_edge(int u, int v, int w) {
    Edge *e = new Edge;

    e->u = u;
    e->v = v;
    e->w = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static void initialize() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    memset(marked, false, sizeof(marked));
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        add_edge(u, v, c);
    }  // for
}

static void update_size(int x) {
    marked[x] = true;
    size[x] = 1;
    maxsize[x] = 0;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            update_size(v);

            size[x] += size[v];
            maxsize[x] = max(maxsize[x], size[v]);
        }
    }  // for

    marked[x] = false;
}

static void update_distance(int x, int d) {
    marked[x] = true;
    dist[++cnt] = d;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            update_distance(v, d + e->w);
        }
    }  // for

    marked[x] = false;
}

static int choose(int x) {
    marked[x] = true;

    int answer = x;
    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (not marked[v]) {
            maxsize[v] = max(maxsize[v], totalsize - size[v]);

            int result = choose(v);
            if (maxsize[answer] > maxsize[result]) {
                answer = result;
            }
        }
    }  // for

    marked[x] = false;
    return answer;
}

static int compute(int x, int d) {
    cnt = 0;
    update_distance(x, d);
    sort(dist + 1, dist + cnt + 1);

    int answer = 0;
    int i = 1, j = cnt;
    while (i < j) {
        while (i < j && dist[i] + dist[j] > k) {
            j--;
        }  // while

        if (dist[i] + dist[j] <= k) {
            answer += j - i;
        }
        i++;
    }  // while

    return answer;
}

static int solve(int x) {
    update_size(x);
    totalsize = size[x];
    int center = choose(x);

    int answer = compute(center, 0);
    marked[center] = true;
    for (unsigned i = 0; i < G[center].size(); i++) {
        Edge *e = G[center][i];
        int v = e->either(center);

        if (not marked[v]) {
            answer -= compute(v, e->w);
            answer += solve(v);
        }
    }  // for

    return answer;
}

int main() {
    while (scanf("%d%d", &n, &k)) {
        if (n == 0 && k == 0) {
            break;
        }

        initialize();
        printf("%d\n", solve(1));
    }  // while

    return 0;
}  // function main
