#include <cstdio>
#include <cstring>

#include <algorithm>

#include "satellite.h"

using namespace std;

#define NMAX 100

namespace {
static int n, cnt;
static bool mat[NMAX + 10][NMAX + 10];
}

bool query(int a[], size_t na, int b[], size_t nb) {
    cnt++;

    for (size_t i = 0; i < na; i++) {
        for (size_t j = 0; j < nb; j++) {
            if (mat[a[i]][b[j]])
                return true;
        }  // for
    }      // for

    return false;
}

int main() {
    scanf("%d", &n);

    initialize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        mat[u][v] = mat[v][u] = true;

        int x, y;
        search(x, y);

        if ((x != u || y != v) && (x != v || y != u)) {
            printf("Wrong answer: expected %d - %d, but got %d - %d\n", u, v, x,
                   y);
            return 0;
        }
    }  // for

    if (cnt > 1)
        printf("Accepted: used %d queries.\n", cnt);
    else
        printf("Accepted: used %d query.\n", cnt);

    return 0;
}  // function main
