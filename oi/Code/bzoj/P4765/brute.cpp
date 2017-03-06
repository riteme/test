#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n, q, root;
static vector<int> G[NMAX + 10];
static int father[NMAX + 10];
static i64 val[NMAX + 10];
static i64 sum[NMAX + 10];

void dfs(int x, int f) {
    sum[x] = val[x];
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v == f)
            continue;

        father[v] = x;
        dfs(v, x);
        sum[x] += sum[v];
    }
}

void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", val + i);
    }

    for (int i = 1; i <= n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u) {
            G[u].push_back(v);
            G[v].push_back(u);
        } else
            root = v;
    }

    dfs(root, 0);
}

int main() {
    initialize();

    while (q--) {
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);

        if (op == 1) {
            i64 delta = b - val[a];
            val[a] = b;
            while (a) {
                sum[a] += delta;
                a = father[a];
            }
        } else {
            i64 answer = 0;
            for (int i = a; i <= b; i++) {
                answer += sum[i];
            }

            printf("%lld\n", answer);
        }
    }

    return 0;
}
