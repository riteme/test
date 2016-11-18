#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 100
#define INFTY 1000000000

static int L, m, s, t;

struct Matrix {
    Matrix() {
        for (int i = 1; i <= NMAX; i++)
            for (int j = 1; j <= NMAX; j++)
                mat[i][j] = INFTY;
    }

    int mat[NMAX + 10][NMAX + 10];

    Matrix operator*(const Matrix &b) const {
        Matrix c;

        for (int i = 1; i <= NMAX; i++) {
            for (int j = 1; j <= NMAX; j++) {
                for (int k = 1; k <= NMAX; k++) {
                    c.mat[i][j] = min(
                        c.mat[i][j],
                        mat[i][k] + b.mat[k][j]
                    );
                }
            }
        }

        return c;
    }
};

inline void quick_pow(Matrix &a, int b, Matrix &out) {
    bool first = true;

    while (b) {
        if (b & 1) {
            if (first) {
                out = a;
                first = false;
            } else
                out = out * a;
        }
        a = a * a;
        b >>= 1;
    }
}

static Matrix G;
static Matrix R;
static int cnt;
static map<int, int> table;

inline int id(int x) {
    if (!table.count(x))
        table[x] = ++cnt;
    return table[x];
}

int main() {
    scanf("%d%d%d%d", &L, &m, &s, &t);
    s = id(s);
    t = id(t);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &w, &u, &v);
        u = id(u);
        v = id(v);

        G.mat[u][v] = G.mat[v][u] = min(G.mat[v][u], w);
    }

    quick_pow(G, L, R);

    printf("%d\n", R.mat[s][t]);

    return 0;
}
