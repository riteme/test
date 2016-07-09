#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define MOD 2333

struct Matrix {
    Matrix() : m11(1), m12(0), m21(0), m22(1) {}
    Matrix(const int _m11, const int _m12, const int _m21, const int _m22)
            : m11(_m11), m12(_m12), m21(_m21), m22(_m22) {}

    int m11, m12, m21, m22;

    Matrix &operator*=(const Matrix &b) {
        int nm11 = m11 * b.m11 + m12 * b.m21;
        int nm12 = m11 * b.m12 + m12 * b.m22;
        int nm21 = m21 * b.m11 + m22 * b.m21;
        int nm22 = m21 * b.m12 + m22 * b.m22;
        m11 = nm11 % MOD;
        m12 = nm12 % MOD;
        m21 = nm21 % MOD;
        m22 = nm22 % MOD;

        return *this;
    }
};  // struct Matrix

static Matrix quick_pow(Matrix a, int b) {
    Matrix ans = Matrix();
    while (b > 0) {
        if (b % 2 == 1)
            ans *= a;
        a *= a;
        b /= 2;
    }  // while
    return ans;
}

#define NMAX 500000

static int n, m;
static int f1[NMAX + 10], f2[NMAX + 10];
static vector<int> G[NMAX + 10];
static int w[NMAX + 10];
static int maxdist[NMAX + 10];
static bool marked[NMAX + 10];
static Matrix basic;

static void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", f1 + i, f2 + i);
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    if (m == 1) {
        for (int i = 1; i <= n; i++) {
            w[i] = f1[i];
        }  // for
    } else if (m == 2) {
        for (int i = 1; i <= n; i++) {
            w[i] = f2[i];
        }  // for
    } else {
        basic = quick_pow(Matrix(3, 1, 2, 0), m - 2);
        for (int i = 1; i <= n; i++) {
            Matrix m = Matrix(3 * f2[i] + 2 * f1[i], f2[i], f2[i], f1[i]);
            m *= basic;
            w[i] = m.m12;
        }  // for
    }
}

static int dfs(int x) {
    marked[x] = true;

    int result = 0;
    bool haschildren = false;
    int first = 0, second = 0;
    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            haschildren = true;
            result = max(result, dfs(v));

            if (maxdist[v] > first) {
                second = first;
                first = maxdist[v];
            } else if (maxdist[v] > second)
                second = maxdist[v];
        }
    }  // for

    if (!haschildren) {
        maxdist[x] = w[x];
        return w[x];
    }

    // printf("dfs(%d): first = %d, second = %d\n", x, first, second);
    result = max(result, first + second + w[x]);
    maxdist[x] = max(first, second) + w[x];
    return result;
}

int main() {
    initialize();

    // for (int i = 1; i <= n; i++) {
    //     printf("w[%d] = %d\n", i, w[i]);
    // }  // for

    printf("%d\n", dfs(1));

    return 0;
}  // function main
