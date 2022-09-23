#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 1000000;
// constexpr int MMAX = 1000;

using vec = bitset<NMAX + 1>;

struct Rock {
    int x, y, v;

    bool operator<(const Rock &r) const {
        return y > r.y;
    }
};

int n, m, K, L, h, P;
Rock rock[2 * NMAX + 10];
int query[NMAX + 10];
int cnt[NMAX + 10];

int main() {
    scanf("%d%d%d%d%d", &n, &m, &K, &L, &h);
    for (int i = 1; i <= K; i++) {
        scanf("%d", query + i);
    }
    for (int i = 1; i <= L; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        rock[P++] = {x, y, +1};
        rock[P++] = {x, y - h, -1};
    }
    sort(rock, rock + 2 * L);

    vec f, g, v;
    for (int i = 1; i <= n; i++) {
        f[i] = g[i] = 1;
    }

    int j = 0;
    for (int y = m + 1; y >= 1; y--) {
        while (j < P && rock[j].y >= y) {
            int x = rock[j].x;
            cnt[x] += rock[j].v;
            g[x] = (cnt[x] == 0);
            j++;
        }

        v = g & f;
        f = v | ((v << 1) & g) | ((v >> 1) & g);
        f[0] = f[n + 1] = 0;
    }

    int ans = 0;
    for (int i = 1; i <= K; i++) {
        ans += f[query[i]];
    }

    printf("%d\n", ans);

    return 0;
}
