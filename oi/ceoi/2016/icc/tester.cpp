#include <cstdio>

#include "icc.h"

#define NMAX 100

static int n;
static int cnt;
static bool mat[NMAX + 10][NMAX + 10];

int query(int a, int b, int *A, int *B) {
    cnt++;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (mat[A[i]][B[j]])
                return 1;
        }
    }

    return 0;
}

void setRoad(int a, int b) {
    printf("Program answers: (%d, %d)\n", a, b);

    if (n > 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        mat[u][v] = mat[v][u] = true;
        n--;
    }
}

int main() {
    scanf("%d", &n);
    int u, v;
    scanf("%d%d", &u, &v);
    mat[u][v] = mat[v][u] = true;
    n--;
    run(n);
    printf("cnt = %d\n", cnt);
    return 0;
}
