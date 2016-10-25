#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define LOGN 16

typedef long long int64;

struct Edge {
    int u, v;
    int64 w;

    int either(int x) const {
        return x == u ? v : u;
    }
};

static int n, m;
static Edge edges[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int army[NMAX + 10];

static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static vector<int> children[NMAX + 10];
static int father[NMAX + 10];
static int64 dist[NMAX + 10];
static int64 weight[NMAX + 10];
static int from[NMAX + 10];

static bool marked[NMAX + 10];

static void build_tree(int x, int head) {
    marked[x] = true;
    in[x] = INT_MAX;
    from[x] = head;

    bool leafflag = true;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (marked[v])
            continue;

        leafflag = false;
        children[x].push_back(v);
        father[v] = x;
        dist[v] = dist[x] + e->w;
        weight[v] = e->w;

        if (x == 1)
            build_tree(v, v);
        else
            build_tree(v, head);

        in[x] = min(in[x], in[v]);
        out[x] = max(out[x], out[v]);
    }

    if (leafflag)
        in[x] = out[x] = ++timestamp;
}

inline void add_edge(int u, int v, int64 w, int i) {
    Edge *e = edges + i;
    e->u = u;
    e->v = v;
    e->w = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static int f[NMAX + 10][LOGN + 1];
static int64 distsum[NMAX + 10][LOGN + 1];

inline int jump(int x, int64 maxdist) {
    for (int i = LOGN; i >= 0; i--) {
        if (f[x][i] && distsum[x][i] <= maxdist) {
            maxdist -= distsum[x][i];
            x = f[x][i];
        }
    }

    return x;
}

static bool cmp_army(const int a, const int b) {
    return dist[a] > dist[b];
}

static bool cmp_son(const int a, const int b) {
    return weight[a] <  weight[b];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int u, v;
        int64 w;
        scanf("%d%d%lld", &u, &v, &w);

        add_edge(u, v, w, i);
    }

    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d", army + i);
    }

    build_tree(1, 1);

    for (int i = 1; i <= n; i++) {
        f[i][0] = father[i];
        distsum[i][0] = weight[i];
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j -1];
            distsum[i][j] = distsum[i][j - 1] + distsum[f[i][j - 1]][j - 1];
        }
    }

    sort(army + 1, army + m + 1, cmp_army);
    sort(children[1].begin(), children[1].end(), cmp_son);
}

static int cnt[NMAX + 10];
static bool remain[NMAX + 10];
static bool missed[NMAX + 10];

static bool test(int64 maxdist) {
    memset(cnt, 0, sizeof(cnt));
    memset(remain, 0, sizeof(remain));
    memset(missed, 0, sizeof(missed));

    for (int i = 1; i <= m; i++) {
        int endpoint = jump(army[i], maxdist);

        if (endpoint == 1)
            remain[i] = true;
        else {
            cnt[in[endpoint]]++;
            cnt[out[endpoint] + 1]--;
        }
    }

    for (int i = 1; i <= timestamp; i++) {
        cnt[i] += cnt[i - 1];
    }

    bool flag = true;
    for (int i = 1; i <= timestamp && flag; i++) {
        if (cnt[i] == 0)
            flag = false;
    }

    if (flag)
        return true;

    for (size_t i = 0; i < children[1].size(); i++) {
        int v = children[1][i];

        missed[v] = false;
        for (int j = in[v]; j <= out[v] && !missed[v]; j++) {
            if (cnt[j] == 0)
                missed[v] = true;
        }
    }
    
    int i = 1, j = 0;
    while (true) {
        while (i <= m && !remain[i])
            i++;
        while (j < children[1].size() && !missed[children[1][j]])
            j++;

        if (!(i <= m && j < children[1].size()))
            break;

        if (missed[from[army[i]]])
            missed[from[army[i]]] = false;
        else if (maxdist - dist[army[i]] >= weight[children[1][j]]) {
            missed[children[1][j]] = false;
            j++;
        }

        i++;
    }

    for (size_t k = 0; k < children[1].size(); k++) {
        if (missed[children[1][k]])
            return false;
    }

    return true;
}

int main() {
    // freopen("blockade.in", "r", stdin);
    initialize();

    int64 left = 0;
    int64 right = 0;

    for (int i = 1; i <= n; i++) {
        right = max(right, dist[i]);
    }
    int64 maxright = right * 2;
    right = maxright + 2;

    while (left + 1 < right) {
        int64 mid = (left + right) / 2;

        if (test(mid))
            right = mid;
        else
            left = mid;
    }

    if (left != right && !test(left))
        left = right;

    if (left >= maxright)
        puts("-1");
    else
        printf("%lld\n", left);

    return 0;
}
