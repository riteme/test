#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 5000
#define BASE 19260817

typedef unsigned long long u64;

static int n, q;
static char ch[NMAX + 10];
static int fa[NMAX + 10];
static u64 H[NMAX + 10][NMAX + 10];
static unordered_map<u64, int> cnt[NMAX + 10];

int main() {
    scanf("%d%d%s", &n, &q, ch + 1);
    for (int v = 1; v <= n; v++) {
        if (v > 1) scanf("%d", fa + v);
        u64 S = 0;
        for (int u = v, l = 1; u; u = fa[u], l++) {
            S = S * BASE + ch[u];
            H[v][l] = S;
            cnt[l][S]++;
        }
    }
    while (q--) {
        int x, L;
        scanf("%d%d", &x, &L);
        printf("%d\n", cnt[L][H[x][L]]);
    }
    return 0;
}
