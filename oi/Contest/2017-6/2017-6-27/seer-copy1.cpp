// #define NDEBUG
// #define USE_FILE_IO

#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 250000

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

static int n, m, K;
static struct Edge {
    int u, v, w;
    bool determined;
} edge[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int sorted[MMAX + 10];
static bool marked[MMAX + 10], ok[NMAX + 10];
static int prime[MMAX + 20], pcnt;
static int w[NMAX + 10], d[NMAX + 10];
static int r[MMAX + 10], cnt;

bool cmp(int a, int b) {
    int da = d[edge[a].u] + d[edge[a].v];
    int db = d[edge[b].u] + d[edge[b].v];
    return da < db;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];
        scanf("%d%d", &e.u, &e.v);
        e.w = e.determined = 0;
        d[e.u]++;
        d[e.v]++;
        G[e.u].push_back(&e);
        G[e.v].push_back(&e);
        sorted[i] = i;
    }
    sort(sorted + 1, sorted + m + 1, cmp);

    marked[1] = true;
    for (int i = 2; i <= m; i++) {
        if (!marked[i])
            prime[++pcnt] = i;

        for (int j = 1; prime[j] * i <= m; j++) {
            marked[prime[j] * i] = true;

            if (i % prime[j] == 0)
                break;
        }
    }
}

int evaluate() {
    memset(w, 0, sizeof(w));
    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];
        w[e.u] = gcd(w[e.u], e.w);
        w[e.v] = gcd(w[e.v], e.w);
    }

    int ret = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] > 1)
            ret = max(ret, w[i]);
    }

    return ret;
}

int main() {
#ifdef USE_FILE_IO
    freopen("seer.in", "r", stdin);
    freopen("seer.out", "w", stdout);
#endif
    srand(time(0));
    initialize();

    prime[++pcnt] = 1;
    int i, j;
    for (i = 1, j = pcnt; i <= m && j >= 1; i++) {
        Edge &e = edge[sorted[i]];

        if (d[e.u] > 1 && d[e.v] > 1 && !ok[e.u] && !ok[e.v]) {
            e.w = prime[j--];
            e.determined = true;
            ok[e.u] = true;
            ok[e.v] = true;
        }
    }

    assert(j < pcnt);
    for (int i = 2; i <= m; i++) {
        if (marked[i] || i <= prime[j])
            r[++cnt] = i;
    }

    while (true) {
        random_shuffle(r + 1, r + cnt + 1);
        int j = 1;
        for (int i = 1; i <= m; i++) {
            Edge &e = edge[i];

            if (!e.determined)
                e.w = r[j++];
        }

        if (evaluate() <= K)
            break;
    }

    for (int i = 1; i <= m; i++) {
        printf("%d\n", edge[i].w);
    }

    return 0;
}
