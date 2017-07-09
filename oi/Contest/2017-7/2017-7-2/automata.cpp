#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef map<int, int>::iterator iter_t;

static int n;
static int father[NMAX + 10], chr[NMAX + 10];
static int fail[NMAX + 10];
static map<int, int> g[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", father + i);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", chr + i);
    }

    for (int i = 1; i <= n; i++) {
        g[father[i]][chr[i]] = i;
    }
}

int main() {
    freopen("automata.in", "r", stdin);
    freopen("automata.out", "w", stdout);
    initialize();

    queue<int> q;
    for (iter_t beg = g[0].begin(); beg != g[0].end(); beg++) {
        q.push(beg->second);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (iter_t beg = g[u].begin(); beg != g[u].end(); beg++) {
            int c = beg->first;
            int v = beg->second;

            int y = u;
            do {
                y = fail[y];

                if (g[y].count(c)) {
                    y = g[y][c];
                    break;
                }
            } while (y);

            fail[v] = y;
            q.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", fail[i]);
    }
    putchar('\n');

    return 0;
}
