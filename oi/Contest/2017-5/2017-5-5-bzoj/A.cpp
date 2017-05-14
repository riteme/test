#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define NMAX 1000

static int n, m, k;
static vector<int> G[NMAX + 10];
static int maxc;
static int col[NMAX + 10];
static int path[NMAX + 10];
static int marked[NMAX + 10];
static bool mex[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    maxc = 0;
    memset(marked, 0, n + 1);
}

void color(int s) {
    queue<int> q;
    q.push(s);
    marked[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (marked[v])
                mex[col[v]] = true;
        }  // for

        col[u] = 1;
        while (mex[col[u]]) {
            col[u]++;
        }  // while

        maxc = max(maxc, col[u]);

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (marked[v])
                mex[col[v]] = false;
        }  // for

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (!marked[v])
        }  // for
    }      // while
}

bool walk(int u, int len) {
    if (len == k + 1) {
        path[len] = u;
        return true;
    }

    marked[u] = true;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (!marked[v] && walk(v, len + 1)) {
            path[len] = u;
            return true;
        }
    }  // for

    marked[u] = false;
    return false;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();
        color(1);

        if (maxc <= k) {
            printf("color");
            for (int i = 1; i <= n; i++) {
                printf(" %d", col[i]);
            }  // for
            putchar('\n');
        } else {
            memset(marked, 0, n + 1);
            for (int i = 1; i <= n; i++) {
                if (walk(i, 1))
                    break;
            }  // for

            printf("path");
            for (int i = 1; i <= k + 1; i++) {
                printf(" %d", path[i]);
            }  // for
            putchar('\n');
        }
    }  // while

    return 0;
}  // function main
