#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int nl, nr, m;
static int ret = 0;
static vector<int> G[NMAX + 10];
static bool marked[NMAX + 10];
static int match[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &nl, &nr, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v + nl);
        G[v + nl].push_back(u);
    }

    for (int u = 1; u <= nl; u++) {
        for (int v : G[u]) {
            if (!match[v]) {
                match[u] = v;
                match[v] = u;
                ret++;
                break;
            }
        }
    }
}

bool dfs(int u) {
    for (int v : G[u]) {
        if (marked[v])
            continue;

        marked[v] = true;
        if (!match[v] || dfs(match[v])) {
            match[u] = v;
            match[v] = u;
            return true;
        }
    }

    return false;
}

int hungarian() {
    for (int u = 1; u <= nl; u++) {
        if (match[u])
            continue;

        memset(marked, 0, sizeof(marked));
        if (dfs(u))
            ret++;
    }

    return ret;
}

int main() {
    initialize();

    printf("%d\n", hungarian());
    for (int u = 1; u <= nl; u++) {
        printf("%d ", match[u] ? match[u] - nl : 0);
    }
    printf("\n");

    return 0;
}
