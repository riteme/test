#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 17

typedef long long i64;

static int n, m;
static bool G[NMAX + 10][NMAX + 10];
static bool T[NMAX + 10][NMAX + 10];
static int perm[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        T[u][v] = T[v][u] = true;
    }

    for (int i = 1; i <= n; i++) {
        perm[i] = i;
    }
}

bool check() {
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (T[u][v] && !G[perm[u]][perm[v]])
                return false;
        }
    }

    return true;
}

int main() {
    initialize();

    i64 answer = check();
    while (next_permutation(perm + 1, perm + n + 1)) {
        answer += check() ? 1 : 0;
    }

    printf("%lld\n", answer);

    return 0;
}
