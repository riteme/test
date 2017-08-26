#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, m, k;
static vector<int> G[NMAX + 10];
static bool marked[NMAX + 10];
static bool col[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

int color(int x) {
    marked[x] = true;

    for (auto v : G[x]) {
        if (!marked[v]) {
            col[v] = col[x] ^ 1;
            if (!color(v))
                return 0;
        } else if (col[v] == col[x])
            return 0;
    }

    return 1;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        initialize();

        memset(marked, 0, sizeof(marked));
        memset(col, 0, sizeof(col));

        int a2 = 0, a3 = 0;

        // x = 1
        if (m == 0) {
            a2 = k % 2;

            if (k * (k - 1) % 3 == 0)
                a3 = k % 3;
        }

        // x = 2
        if (k * (k - 1) % 3 != 0) {
            int d = 1;
            for (int i = 1; i <= n; i++) {
                if (!marked[i]) {
                    if (color(i))
                        d = d * 2 % 3;
                    else {
                        d = 0;
                        break;
                    }
                }
            }

            a3 = (a3 + d * k * (k - 1) * 2) % 3;
        }

        printf("%d\n", (3 * a2 + 4 * a3) % 6);
    }

    return 0;
}
