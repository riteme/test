// #define USE_FILE_IO

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

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
    int u, v;
} edge[MMAX + 10];
static int perm[MMAX + 10], ans[MMAX + 10];
static int d[NMAX + 10], w[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];
        scanf("%d%d", &e.u, &e.v);
        d[e.u]++;
        d[e.v]++;
        perm[i] = i;
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("seer.in", "r", stdin);
    freopen("seer.out", "w", stdout);
#endif
    srand(time(0));
    initialize();

    while (true) {
        random_shuffle(perm + 1, perm + m + 1);
        memset(w, 0, sizeof(w));
        for (int i = 1; i <= m; i++) {
            Edge &e = edge[perm[i]];
            w[e.u] = gcd(w[e.u], i);
            w[e.v] = gcd(w[e.v], i);
        }

        int maxw = 0;
        for (int i = 1; i <= m; i++) {
            if (d[i] > 1)
                maxw = max(maxw, w[i]);
        }

        if (maxw <= K) {
            for (int i = 1; i <= m; i++) {
                ans[perm[i]] = i;
            }

            for (int i = 1; i <= m; i++) {
                printf("%d\n", ans[i]);
            }
            
            break;
        }
    }

    return 0;
}
