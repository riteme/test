#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n;
static vector<int> G[NMAX + 10];
static int deg[NMAX + 10], leaf[NMAX + 10];
static i64 w[NMAX + 10], cnt[NMAX + 10];

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", w + i);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
}

void finalize() {
    for (int i = 1; i <= n; i++)
        G[i].clear();
    memset(deg, 0, sizeof(deg));
    memset(leaf, 0, sizeof(leaf));
}

i64 dp(int x, int f) {
    i64 sz = 1;
    cnt[x] = 2 * n - 1;
    for (int v : G[x]) {
       if (v == f) continue;
       i64 szv = dp(v, x);
       cnt[x] += szv * (n - szv - 1);
       sz += szv;
    }
    cnt[x] += (sz - 1) * (n - sz);
    return sz;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        initialize();

        dp(1, 0);
        i64 S = 0;
        for (int i = 1; i <= n; i++)
            S += w[i] * cnt[i];
        if (S == 0) puts("0");
        else {
            bool ok = false;
            for (int i = 1; !ok && i <= n; i++) {
                if (S % cnt[i] == 0) {
                    printf("1 %d\n", i);
                    ok = true;
                }
            }

            for (int i = 1; !ok && i <= n; i++) {
                if (deg[i] == 1)
                    leaf[G[i][0]]++;
            }

            for (int i = 1; !ok && i <= n; i++) {
                if (leaf[i] == 2) {
                    printf("2 %d", i);
                    for (int v : G[i]) {
                        if (deg[v] == 1) {
                            printf(" %d\n", v);
                            break;
                        }
                    }
                    ok = true;
                }
            }
        }

        finalize();
    }
    return 0;
}
