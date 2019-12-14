#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, q;
static vector<int> G[NMAX + 10];
static int in[NMAX + 10], size[NMAX + 10];
static int seq[NMAX + 10], tm;

void dfs(int x) {
    seq[++tm] = x;
    in[x] = tm;
    size[x] = 1;
    for (int v : G[x]) {
        dfs(v);
        size[x] += size[v];
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int v = 2; v <= n; v++) {
        int u;
        scanf("%d", &u);
        G[u].push_back(v);
    }
    dfs(1);
    while (q--) {
        int x, k;
        scanf("%d%d", &x, &k);
        if (k > size[x]) puts("-1");
        else printf("%d\n", seq[in[x] + k - 1]);
    }
    return 0;
}
