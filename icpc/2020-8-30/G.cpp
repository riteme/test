#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 150

int n, m;
bool G[NMAX + 10][NMAX + 10];
int s[NMAX + 10], s0[NMAX + 10];

int prep(int i) {
    return i > 1 ? i - 1 : n;
}

void _main() {
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    for (int i = 1; i <= n; i++) {
        s[i] = i;
    }

    bool ok;
    do {
        ok = true;
        for (int i = 1; i <= n; i++) {
            int j = i % n + 1;
            int v = s[i], u = s[j];
            if (G[u][v])
                continue;

            ok = false;

            int k = j % n + 1, l = k % n + 1;
            for ( ; l != i; k = l, l = l % n + 1) {
                if (G[u][s[l]] && G[s[k]][v])
                    break;
            }

            int p = 1;
            s0[p++] = u;
            for (int x = l; x != i; x = x % n + 1) {
                s0[p++] = s[x];
            }
            s0[p++] = v;
            for (int x = k; x != j; x = prep(x)) {
                s0[p++] = s[x];
            }
            memcpy(s + 1, s0 + 1, sizeof(int) * n);

            break;
        }
    } while (!ok);

    for (int i = 1; i <= n; i++) {
        printf(i < n ? "%d " : "%d\n", s[i]);
    }

    for (int i = 1; i <= n; i++) {
        memset(G[i] + 1, 0, n);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        _main();
    }

    return 0;
}
