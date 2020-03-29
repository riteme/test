#include <cstdio>
#include <cstring>

#include <list>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000

struct Edge {
    int v, w;
};

int n, m;
vector<Edge> G[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
}

int K;
int f[NMAX + 10], g[NMAX + 10];

void dp(int x, int p) {
    f[x] = g[x]= 0;
    vector<int> len;
    len.reserve(G[x].size() - !!p);

    for (auto &e : G[x]) if (e.v != p) {
        dp(e.v, x);
        f[x] += f[e.v];
        len.push_back(g[e.v] + e.w);
    }

    sort(len.begin(), len.end());
    while (!len.empty() && len.back() >= K) {
        f[x]++;
        len.pop_back();
    }

    if (!len.empty()) {
        list<int> li(len.begin(), len.end());

        for (auto i = li.begin(), j = li.end(); i != li.end(); ) {
            for (auto k = prev(j); k != i && *i + *k >= K; k--)
                j = k;

            if (j != li.end()) {
                f[x]++;
                j = li.erase(j);
            } else
                g[x] = max(g[x], *i);

            i++;
            if (j == i) j++;
        }
    }
}

int main() {
    initialize();

    int l = 0, r = 5e8 + 1;
    while (l < r) {
        K = (l + r) / 2 + 1;
        dp(1, 0);
        // fprintf(stderr, "%d → %d\n", K, f[1]);
        if (f[1] >= m) l = K;
        else r = K - 1;
    }

    printf("%d\n", l);
    return 0;
}