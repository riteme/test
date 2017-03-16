#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define EPSILON 0.00000001

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

#define NMAX 500
#define MMAX 250000

typedef double float128;

struct Edge {
    Edge ()
        : u(0), v(0), e(0.0L) {}

    int u, v;
    float128 e;

    int either(int x) const {
        return u == x ? v : u;
    }
};

static int n, m;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int degree[NMAX + 10];
static float128 mat[NMAX + 10][NMAX + 10];
static float128 ret[NMAX + 10];
static float128 weight[MMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &m);
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        cin >> u >> v;

        Edge *e = edges + i;
        e->u = u;
        e->v = v;
        G[u].push_back(e);
        G[v].push_back(e);
        degree[u]++;
        degree[v]++;
    }
}

static bool cmp(const float128 &a, const float128 &b) {
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    initialize();

    ret[1] = 1.0L;
    for (int u = 1; u <= n - 1; u++) {
        mat[u][u] = 1.0L;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);
            
            if (v != n) {
                mat[u][v] = -1.0L / degree[v];
            }
        }
    }

    for (int i = 1; i < n - 1; i++) {
        int pivot = i;

        for (int j = i + 1; j <= n - 1; j++) {
            if (abs(mat[j][i]) > abs(mat[pivot][i]))
                pivot = j;
        }

        if (i != pivot) {
            for (int j = i; j <= n - 1; j++) {
                swap(mat[pivot][j], mat[i][j]);
            }
            // What...
            swap(ret[pivot], ret[i]);
        }

        for (int j = i + 1; j <= n - 1; j++) {
            float128 rate = mat[j][i] / mat[i][i];

            ret[j] -= ret[i] * rate;
            for (int k = i; k <= n - 1; k++) {
                mat[j][k] -= mat[i][k] * rate;
            }
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        ret[i] /= mat[i][i];

        for (int j = i - 1; j >= 1; j--) {
            ret[j] -= mat[j][i] * ret[i];
            mat[j][i] = 0.0L;
        }
    }

    for (int u = 1; u <= n - 1; u++) {
        float128 average = ret[u] / degree[u];

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];

            e->e += average;
        }
    }

    for (int i = 1; i <= m; i++) {
        weight[i] = edges[i].e;
    }

    sort(weight + 1, weight + m + 1, cmp);

    float128 answer = 0.0L;
    for (int i = 1; i <= m; i++) {
        answer += i * weight[i];
    }

    // printf("%.3lf\n", answer);
    cout.precision(3);
    cout << fixed << answer << endl;

    return 0;
}

