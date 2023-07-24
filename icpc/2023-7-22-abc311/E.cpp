#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 3000;

int n, m, K;
bool S[NMAX + 10][NMAX + 10];
int up[NMAX + 10][NMAX + 10];
int head, tail;
int Q[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        S[x][y] = true;
    }
    for (int y = 1; y <= m; y++) {
        for (int x = 1; x <= n; x++) {
            up[x][y] = up[x - 1][y];
            if (S[x][y])
                up[x][y] = x;
        }
    }

    i64 ans = 0;
    for (int x = 1; x <= n; x++) {
        int h = 0;
        head = tail = 0;
        for (int y = 1; y <= m; y++) {
            while (head < tail && up[x][Q[tail - 1]] <= up[x][y]) {
                tail--;
            }
            Q[tail++] = y;
            h++;
            while (head < tail) {
                int h0 = min(h, x - up[x][Q[head]]);
                if (h == h0)
                    break;
                h = h0;
                while (head < tail && Q[head] <= y - h) {
                    head++;
                }
            }
            // printf("x=%d y=%d h=%d\n", x, y, h);
            ans += h;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
