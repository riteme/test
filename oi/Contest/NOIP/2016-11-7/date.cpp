#pragma GCC optimize(3)

#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 300
#define TMAX 60000
#define INFTY 1000000000

struct Edge {
    Edge (int _u, int _v, int _w) 
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }
};

#define BL true
#define PL false

static int s, end;
static int n, m;
static char C[NMAX + 10];
static int R[NMAX + 10], B[NMAX + 10], P[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static bool light[NMAX + 10];
static int cnt[NMAX + 10];
static bool f[TMAX + 10][NMAX + 10];
static int from[TMAX + 10][NMAX + 10];
static int fromt[TMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d%d%d", &s, &end, &n, &m);

    for (int i = 1; i <= n; i++) {
        C[i] = getchar();
        while (!isalpha(C[i]))
            C[i] = getchar();
        if (C[i] == 'B')
            light[i] = BL;
        else
            light[i] = PL;

        scanf("%d%d%d", R + i, B + i, P + i);
        cnt[i] = R[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        Edge *e = new Edge(u, v, w);
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

int main() {
    freopen("date.in", "r", stdin);
    freopen("date.out", "w", stdout);
    initialize();

    memset(f, 0, sizeof(f));
    f[0][s] = true;
    int t;
    for (t = 0; t <= TMAX; t++) {
        if (f[t][end])
            break;

        for (int u = 1; u <= n; u++) {
            if (t > 0 && f[t - 1][u]) {
                f[t][u] = true;
                from[t][u] = from[t - 1][u];
                fromt[t][u] = fromt[t - 1][u];
            }

            if (!f[t][u])
                continue;

            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];
                int v = e->either(u);

                if (light[u] != light[v] || t + e->w > TMAX)
                    continue;

                f[t + e->w][v] = true;
                from[t + e->w][v] = u;
                fromt[t + e->w][v] = t;
            }
        }

        for (int i = 1; i <= n; i++) {
            cnt[i]--;

            if (cnt[i] == 0) {
                light[i] ^= 1;

                if (light[i] == BL)
                    cnt[i] = B[i];
                else
                    cnt[i] = P[i];
            }
        }
    }

    int answer = t;
    int pos = 0;
    int stack[NMAX + 10];
    int x = end;
    while (x) {
        stack[++pos] = x;
        int tmp = x;
        x = from[t][x];
        t = fromt[t][tmp];
    }

    printf("%d\n", answer);
    for (int i = pos; i >= 1; i--)
        printf("%d ", stack[i]);
    putchar('\n');

    fclose(stdin);
    fclose(stdout);
    return 0;
}
