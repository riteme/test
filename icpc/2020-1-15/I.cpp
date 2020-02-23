#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000
#define MOD 1000000007

typedef long long i64;

int n, m, in[NMAX + 10];
vector<int> G[NMAX + 10];
int seq[NMAX + 10];
i64 f[NMAX + 10];
bool g[NMAX + 10];

void tsort() {
    int p = 1;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        seq[p++] = u;
        for (int v : G[u]) {
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
}

void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int k;
        scanf("%d", &k);
        G[i].reserve(k);
        for (int j = 0; j < k; j++) {
            int v;
            scanf("%d", &v);
            G[i].push_back(v);
            in[v]++;
        }
    }
    tsort();

    f[1] = 1;
    g[1] = true;
    for (int i = 1; i <= n; i++) {
        int u = seq[i];
        for (int v : G[u]) {
            add(f[v], f[u]);
            g[v] |= g[u];
        }
    }

    i64 a0 = 0, a1 = 0;
    for (int i = m + 1; i <= n; i++) {
        add(a0, f[i]);
        if (g[i]) a1++;
    }

    printf("%lld %lld\n", a0, a1);
    return 0;
}