#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long double float128;

static int n;
static vector<int> G[NMAX + 10];
static int X[NMAX + 10];
static int Y[NMAX + 10];
static float128 pin[NMAX + 10];
static float128 pout[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    float128 xsum = 0;
    float128 ysum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", X + i, Y + i);

        xsum += X[i];
        ysum += Y[i];
    }
    
    for (int i = 1; i <= n; i++) {
        pin[i] = X[i] / xsum;
        pout[i] = Y[i] / ysum;
    }
}

static bool marked[NMAX + 10];
static int size[NMAX + 10];
static int nxt[NMAX + 10];
static float128 E[NMAX + 10];

static bool dfs(int x, int t) {
    if (x == t) {
        E[x] = 0.0L;
        return true;
    }

    bool flag = false;
    marked[x] = true;
    size[x] = 1;
    E[x] = 0.0L;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (marked[v])
            continue;

        if (dfs(v, t)) {
            nxt[x] = v;
            E[x] += E[v] + 1.0L;
            flag = true;
        } else {
            E[x] += size[v];
            size[x] += size[v];
        }
    }

    return flag;
}

int main() {
    initialize();

    float128 answer = 0.0L;

    for (int in = 1; in <= n; in++) {
        for (int out = 1; out <= n; out++) {
            memset(marked, 0, sizeof(marked));
            dfs(in, out);

            answer += E[in] * pin[in] * pout[out];
        }
    }

    printf("%.12Lf\n", answer);

    return 0;
}
