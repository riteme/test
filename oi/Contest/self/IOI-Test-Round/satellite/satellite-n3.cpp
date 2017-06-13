#include "satellite.h"

#define NMAX 100

static int n;
static bool mat[NMAX + 10][NMAX + 10];

void initialize(int _n) {
    n = _n;
}

void search(int &u, int &v) {
    for (u = 1; u <= n; u++) {
        for (v = u + 1; v <= n; v++) {
            if (mat[u][v])
                continue;

            if (query(&u, 1, &v, 1)) {
                mat[u][v] = true;
                return;
            }
        }  // for
    }      // for
}
