#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define LMAX 10000

static int n, L;
static vector<int> G[NMAX + LMAX + 10];
static int matched[NMAX + LMAX + 10];
static bool marked[NMAX + LMAX + 10];
static int cnt;

inline void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

static void initialize() {
    scanf("%d%d", &n, &L);

    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (a <= L)
            add_edge(i, n + a);
        if (b <= L)
            add_edge(i, n + b);
    }  // for
}

static bool dfs(int u) {
    marked[u] = true;

    bool flag = false;
    for (unsigned i = 0; !flag && i < G[u].size(); i++) {
        int v = G[u][i];

        if (!marked[v]) {
            marked[v] = true;

            if (matched[v] == 0 || dfs(matched[v])) {
                matched[u] = v;
                matched[v] = u;

                flag = true;
            }

            marked[v] = false;
        }
    }

    marked[u] = false;
    return flag;
}

static int match() {
    int answer = cnt;

    for (int i = 1; i <= n; i++) {
        if (matched[i] == 0) {
            if (dfs(i)) {
                answer++;
            }
        }
    }

    return answer;
}

int main() {
    initialize();

    if (match() >= L) {
        puts("Yes");
    } else {
        puts("No");
    }

    return 0;
}  // function main
