#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
// #define NMAX 100
#define LOGN 17

typedef long long int64;

struct Ticket {
    int k;
    int64 price;
};  // struct Ticket

static int n, m, q;
static vector<int> G[NMAX + 10];
static vector<Ticket> tickets[NMAX + 10];
static vector<int> children[NMAX + 10];
static bool marked[NMAX + 10];
static int depth[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static int minv[NMAX + 10][LOGN + 1];
static int64 dp[NMAX + 10];

static bool cmp(const int a, const int b) {
    return dp[a] < dp[b];
}

static void build(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            children[x].push_back(v);
            depth[v] = depth[x] + 1;
            f[v][0] = x;

            build(v);
        }
    }  // for
}

static void dfs(int x) {
    for (size_t i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        for (auto &ticket : tickets[v]) {
            int target_depth = max(0, depth[v] - ticket.k);
            int dist = depth[v] - target_depth - 1;
            int p = f[v][0];
            int answer = p;

            for (int j = LOGN; j >= 0; j--) {
                if (dist & (1 << j)) {
                    answer = min(answer, minv[p][j], cmp);
                    p = f[p][j];
                }
            }  // for

            dp[v] = min(dp[v], dp[answer] + ticket.price);
        }  // foreach in tickets[v]

        minv[v][0] = min(v, f[v][0], cmp);
        for (int j = 1; j <= LOGN; j++) {
            minv[v][j] = min(minv[v][j - 1], minv[f[v][j - 1]][j - 1], cmp);
        }  // for

        dfs(v);
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    for (int i = 1; i <= m; i++) {
        int id, k;
        int64 v;
        scanf("%d%d%lld", &id, &k, &v);

        tickets[id].push_back({ k, v });
    }  // for

    build(1);

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= LOGN; j++) {
            minv[i][j] = 0;
        }  // for
    }      // for

    for (int i = 0; i <= n; i++) {
        dp[i] = LLONG_MAX;
    }  // for

    dp[1] = 0;
    for (int i = 0; i <= LOGN; i++) {
        minv[1][i] = 1;
    }  // for

    dfs(1);
}

int main() {
    initialize();

    scanf("%d", &q);

    while (q--) {
        int x;
        scanf("%d", &x);

        printf("%lld\n", dp[x]);
    }  // while

    return 0;
}  // function main
