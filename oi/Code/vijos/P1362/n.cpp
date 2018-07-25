#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

#define NMAX 500000

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int            n;
static int            s;
static vector<Edge *> G[NMAX + 10];
static vector<int>    children[NMAX + 10];
static int            w[NMAX + 10];
static bool           marked[NMAX + 10];

inline void add_edge(int u, int v, int w) {
    Edge *e = new Edge(u, v, w);
    G[u].push_back(e);
    G[v].push_back(e);
}

static void build_tree(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int   v = e->either(x);

        if (marked[v])
            continue;

        children[x].push_back(v);
        w[v] = e->w;
        build_tree(v);
    }
}

static void initialize() {
    scanf("%d%d", &n, &s);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        int w;
        scanf("%d%d%d", &u, &v, &w);

        add_edge(u, v, w);
    }

    build_tree(1);
}

static int maxlength[NMAX + 10];
static int maxdist[NMAX + 10];
static int endpoint[NMAX + 10];
static int p1[NMAX + 10];
static int p2[NMAX + 10];

static void dp(int x) {
    if (children[x].empty()) {
        maxlength[x] = 0;
        maxdist[x]   = 0;
        endpoint[x]  = x;
        p1[x] = p2[x] = x;
    } else if (children[x].size() == 1) {
        int v = children[x][0];

        dp(v);
        maxdist[x]  = maxdist[v] + w[v];
        endpoint[x] = endpoint[v];

        if (maxdist[x] > maxlength[v]) {
            maxlength[x] = maxdist[x];
            p1[x]        = x;
            p2[x]        = endpoint[x];
        } else {
            maxlength[x] = maxlength[v];
            p1[x]        = p1[v];
            p2[x]        = p2[v];
        }
    } else {
        int first = 0, second = 0;
        int firstp, secondp, maxp;

        for (size_t i = 0; i < children[x].size(); i++) {
            int v = children[x][i];

            dp(v);

            if (maxlength[v] > maxlength[x]) {
                maxlength[x] = maxlength[v];
                maxp         = v;
            }

            int distv = maxdist[v] + w[v];
            if (distv > first) {
                second  = first;
                secondp = firstp;
                first   = distv;
                firstp  = endpoint[v];
            } else if (distv > second) {
                second  = distv;
                secondp = endpoint[v];
            }
        }

        int newdist = first + second;
        maxdist[x]  = first;
        endpoint[x] = firstp;
        if (newdist > maxlength[x]) {
            maxlength[x] = newdist;
            p1[x]        = firstp;
            p2[x]        = secondp;
        } else {
            p1[x] = p1[maxp];
            p2[x] = p2[maxp];
        }
    }
}

static int len;
static int path[NMAX + 10];
static int dist_to_next[NMAX + 10];
static int dist[NMAX + 10];
static int weight[NMAX + 10];

static bool scan_path(int x, int pos, int t) {
    if (x == t) {
        path[pos] = x;
        len       = pos;

        return true;
    }

    marked[x] = true;
    bool flag = false;
    dist[x]   = w[x];
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int   v = e->either(x);

        if (marked[v])
            continue;

        w[v] = e->w;

        if (scan_path(v, pos + 1, t)) {
            flag = true;

            path[pos]         = x;
            dist_to_next[pos] = w[v];
        } else {
            dist[x]     = max(dist[x], dist[v] + w[x]);
            weight[pos] = max(weight[pos], dist[v]);
        }
    }

    return flag;
}

int main() {
    // freopen("core.in", "r", stdin);
    // freopen("core.out", "w", stdout);
    // freopen("tree.in", "r", stdin);

    initialize();

    dp(1);
    // printf("%d %d\n", p1[1], p2[1]);

    memset(marked, 0, sizeof(marked));
    scan_path(p1[1], 1, p2[1]);

    for (int i = 1; i <= len; i++)
        dist_to_next[i] += dist_to_next[i - 1];

    deque<int> q;
    q.push_back(1);
    int i = 1, j = 1;
    int answer = INT_MAX;
    while (i < len && j < len) {
        if (j < i)
            j = i;

        while (j < len && dist_to_next[j] - dist_to_next[i - 1] <= s) {
            j++;

            while (!q.empty() && weight[q.back()] <= weight[j])
                q.pop_back();
            q.push_back(j);
            assert(q.size() <= len);
        }

        answer =
            min(answer, max(weight[q.front()],
                            max(dist_to_next[i - 1],
                                dist_to_next[len - 1] - dist_to_next[j - 1])));
        i++;
        while (!q.empty() && q.front() < i)
            q.pop_front();
    }

    printf("%d\n", answer);

    return 0;
}
