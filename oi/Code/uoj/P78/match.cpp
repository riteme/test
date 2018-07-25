#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 2000

static int a, b, m;
static vector<int> G[NMAX + 10];
static bool marked[NMAX + 10];
static int match[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &a, &b, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        v += a;

        G[u].push_back(v);
        G[v].push_back(u);
    }
}

static bool dfs(int u) {
    for (unsigned i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (not marked[v]) {
            marked[v] = true;

            if (match[v] == 0 or dfs(match[v])) {
                match[u] = v;
                match[v] = u;

                return true;
            }
        }
    }

    return false;
}

int main() {
    initialize();

    memset(match, 0, sizeof(match));
    int cnt = 0;
    for (int i = 1; i <= a; i++) {
        memset(marked, false, sizeof(marked));
        if (match[i] == 0) {
            if (dfs(i)) {
                cnt++;
            }
        }
    }

    printf("%d\n", cnt);

    for (int i = 1; i <= a; i++) {
        if (match[i] == 0) {
            printf("0 ");
        } else {
            printf("%d ", match[i] - a);
        }
    }

    return 0;
}
