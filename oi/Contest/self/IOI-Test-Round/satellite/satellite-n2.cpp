#include "satellite.h"

#include <vector>

using namespace std;

#define NMAX 100

static int n;
static bool mat[NMAX + 10][NMAX + 10];
static vector<int> a;

void initialize(int _n) {
    n = _n;
}

void search(int &u, int &v) {
    u = v = 0;

    for (int i = 1; i <= n; i++) {
        if (v)
            break;

        a.clear();
        for (int j = 1; j <= n; j++) {
            if (i != j && !mat[i][j])
                a.push_back(j);
        }  // for

        if (query(&i, 1, a.data(), a.size())) {
            if (u)
                v = i;
            else
                u = i;
        }
    }  // for

    mat[u][v] = mat[v][u] = true;
}
