// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 300
#define INFTY 0x3f3f3f3f

template <typename T>
inline void chkmin(T &dest, const T &src) {
    if (src < dest)
        dest = src;
}

template <typename T>
inline void chkmax(T &dest, const T &src) {
    if (src > dest)
        dest = src;
}

static int n, m;
static bool G[NMAX + 10][NMAX + 10];
static int W[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d", &n);

    memset(W, 0x3f, sizeof(W));
    for (int i = 1; i <= n; i++) {
        W[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u][v] = G[v][u] = true;
        W[u][v] = W[v][u] = w << 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                chkmin(W[i][j], W[i][k] + W[k][j]);
            }
        }
    }
}

static int answer;
static int u, v;
static int t[NMAX + 10];
static int seq[NMAX + 10];

struct Compare {
    bool operator()(const int a, const int b) const {
        return W[u][a] > W[u][b] || (W[u][a] == W[u][b] && a < b);
    }
};

void process() {
    int w = W[u][v];
    set<int, Compare> q;
    for (int i = 1; i <= n; i++) {
        q.insert(i);
        seq[i] = i;
        t[i] = (W[v][i] - W[u][i] + w) / 2;
    }

    sort(seq + 1, seq + n + 1,
         [](const int a, const int b) {
            return t[a] < t[b];
         });

    int maxr = 0;
    for (int i = 1; i <= n; i++) {
        int cur = t[seq[i]];
        i--;
        while (i < n && t[seq[i + 1]] == cur) {
            i++;
            q.erase(seq[i]);
            chkmax(maxr, W[v][seq[i]]);
        }

        if (i < n) {
            int nxt = t[seq[i + 1]];
            int maxl = W[u][*q.begin()];
            int x = (maxr - maxl + w) / 2;
            chkmax(x, cur);
            chkmin(x, nxt);
            chkmin(answer, max(maxl + x, maxr + w - x));
        }
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("center.in", "r", stdin);
    freopen("center.out", "w", stdout);
#endif
    initialize();

    answer = INFTY;
    for (u = 1; u <= n; u++) {
        for (v = u + 1; v <= n; v++) {
            if (G[u][v])
                process();
        }
    }

    printf("%.1lf\n", answer / 2.0);

    return 0;
}
