#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define MMAX 20000

static int n, m;
static vector<int> C[NMAX + 10];
static int fr[MMAX + 10], to[MMAX + 10];

inline int dist(int i, int j) {
    return j >= i ? j - i : n - i + j;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", fr + i, to + i);
        C[fr[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        sort(C[i].begin(), C[i].end(), [](int x, int y) {
            return dist(fr[x], to[x]) < dist(fr[y], to[y]);
        });
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int j = 1; j <= n; j++)
            if (!C[j].empty())
                ans = max(ans,
                    dist(i, j) + int(C[j].size() - 1) * n + dist(j, to[C[j][0]]));
        printf("%d ", ans);
    }

    return 0;
}
