#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define WMAX 600
#define BASE 100

int n;
int K[NMAX + 10], cur[WMAX + 10];
vector<int> buc[WMAX + 10];

bool cmp(int u, int v) {
    return K[u] > K[v] || (K[u] == K[v] && u < v);
}

void initialize() {
    for (int i = 0; i <= WMAX; i++)
        buc[i].clear();
    memset(cur, 0, sizeof(cur));

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int f, s;
        scanf("%d%d", &f, &s);
        K[i] = s;
        buc[f - s + BASE].push_back(i);
    }

    for (int i = 0; i <= WMAX; i++)
        sort(buc[i].begin(), buc[i].end(), cmp);
}

int S(int k, int t) {
    return k - BASE + t * K[buc[k][cur[k]]];
}

void solve() {
    initialize();

    for (int i = 1; i <= n; i++) {
        int j, mx = -10000;
        for (int k = 0; k <= WMAX; k++) if (cur[k] < buc[k].size()) {
            int val = S(k, i);
            if (val > mx || (val == mx && buc[k][cur[k]] < buc[j][cur[j]])) {
                j = k;
                mx = val;
            }
        }

        printf(i < n ? "%d " : "%d\n", buc[j][cur[j]]);
        cur[j]++;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("Case #%d:\n", t);
        solve();
    }
    return 0;
}