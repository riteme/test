//
// Copyright 2015 riteme
//

// Tips: 01邻接矩阵A的K次方C=A^K,C[i][j]表示i点到j点正好经过K条边的路径数
// BUT WA...

#include <climits>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ntype;

#define MAP_SIZE 201

struct Matrix {
    Matrix() { memset(m, INT_MAX, sizeof(m)); }

    ntype &get(int x, int y) { return m[x][y]; }
    ntype get(int x, int y) const { return m[x][y]; }

    friend Matrix operator*(const Matrix &a, const Matrix &b);

    ntype m[MAP_SIZE][MAP_SIZE];
};  // struct Matrix

static Matrix map;
static int vx[1001];
static int N, T, S, E;

void PrintMatrix(const Matrix &m) {
    for (int x = 1; x <= MAP_SIZE; x++) {
        for (int y = 1; y <= MAP_SIZE; y++) {
            printf("%lld ", m.get(x, y));
        }  // for

        printf("\n");
    }  // for
}

void Read() {
    memset(vx, 0, sizeof(vx));

    scanf("%d %d %d %d", &N, &T, &S, &E);

    int cnt = 1;
    for (int i = 1; i <= T; i++) {
        int w, v, u;
        scanf("%d %d %d", &w, &v, &u);

        if (v != u) {
            vx[v] = cnt++;
            vx[u] = cnt++;

            if (map.get(vx[v], vx[u]) == 0 or map.get(vx[v], vx[u]) > w) {
                map.get(vx[v], vx[u]) = w;
                map.get(vx[u], vx[v]) = w;
            }
        }
    }  // for
}

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c;

    for (int i = 1; i <= MAP_SIZE; i++) {
        for (int j = 1; j <= MAP_SIZE; j++) {
            for (int k = 1; k <= MAP_SIZE; k++) {
                if (c.get(i, j) > a.get(i, k) + b.get(k, j)) {
                    c.get(i, j) = a.get(i, k) + b.get(k, j);
                }
            }  // for
        }      // for
    }          // for

    return c;
}

void QuickPow(int k) {
    Matrix a = map;

    while (k >= 1) {
        if (k % 2 == 1) { map = map * a; }

        k /= 2;
        a = a * a;
    }  // while
}

int main() {
    Read();

    // PrintMatrix(map);

    QuickPow(N);

    // PrintMatrix(map);

    printf("%lld", map.get(vx[S], vx[E]));

    return 0;
}  // function main
