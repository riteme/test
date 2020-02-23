#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

int n, K;
vector<int> G[NMAX + 10];
int fa[NMAX + 10];
int mx[NMAX + 10], mxp[NMAX + 10];

void dp(int x) {
    mx[x] = 1;
    mxp[x] = x;
    for (int v : G[x]) {
        fa[v] = x;
        dp(v);
        if (mx[v] + 1 > mx[x]) {
            mx[x] = mx[v] + 1;
            mxp[x] = mxp[v];
        }
    }
}

struct State {
    int u, dep;

    bool operator<(const State &z) const {
        return dep < z.dep;
    }
};

bool mark[NMAX + 10];
priority_queue<State> q;

void take(int x) {
    while (!mark[x]) {
        for (int v : G[x]) if (!mark[v])
            q.push({mxp[v], mx[v]});
        mark[x] = true;
        x = fa[x];
    }
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 2; i <= n; i++) {
        int u;
        scanf("%d", &u);
        G[u].push_back(i);
    }
    dp(1);

    mark[0] = true;
    q.push({mxp[1], mx[1]});
    int ans = 0;
    for (int i = 0; i < K && !q.empty(); i++) {
        auto _ = q.top();
        q.pop();
        ans += _.dep;
        take(_.u);
    }

    printf("%d\n", ans);
    return 0;
}