#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int nl, nr, m;
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &nl, &nr, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(nl + v);
        G[nl + v].push_back(u);
    }
}

static bool marked[NMAX + 10];
static int match[NMAX + 10];

static bool dfs(int x) {
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (marked[v])
            continue;

        // Since we just jumped over the matched edge,
        // so we have to forbid `match[v]` to walk over it
        marked[v] = true;
        if (!match[v] || dfs(match[v])) {
            match[x] = v;
            match[v] = x;

            return true;
        }
    }

    return false;
}

static int hungarian() {
    int answer = 0;

    for (int i = 1; i <= nl; i++) {
        memset(marked, 0, sizeof(marked));
        if (!match[i] && dfs(i))
            answer++;
    }

    return answer;
}

int main() {
    initialize();

    int cnt = hungarian();

    printf("%d\n", cnt);
    for (int i = 1; i <= nl; i++) {
        if (match[i])
            printf("%d ", match[i] - nl);
        else
            printf("0 ");
    }

    return 0;
}
