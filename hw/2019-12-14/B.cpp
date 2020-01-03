#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long long i64;

static int n, m;
static i64 a[NMAX + 10];
static int seq[NMAX + 10];
static vector<int> G[NMAX + 10];

bool cmp(int i, int j) {
    return a[i] < a[j] || (a[i] == a[j] && i < j);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        seq[i] = i;
        scanf("%lld", a + i);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    sort(seq + 1, seq + n + 1, cmp);
    i64 ans = 0;
    for (int i = n; i >= 1; i--) {
        int u = seq[i];
        for (int v : G[u])
            if (cmp(v, u)) ans += a[v];
    }
    printf("%lld\n", ans);
    return 0;
}
