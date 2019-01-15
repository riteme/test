#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define AMAX 30
#define KMAX 5000
#define INF 100000000000000000

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define rrep(i, r, l) for (int i = r; i >= l; i--)

static int n, K, A;
static char buf[NMAX + 10];
static int cnt[AMAX + 10];
static i64 f[KMAX + 10], w[AMAX + 10];

void initialize() {
    scanf("%d%d%s", &n, &K, buf);
    A = 26;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
        cnt[buf[i] - 'a' + 1]++;
    for (char c = 'a'; c <= 'z'; c++)
        w[c - 'a' + 1] = c;
}

inline i64 c2(i64 n) {
    return n * (n - 1) >> 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        initialize();
        i64 sum = 0;
        rep(i, 1, A) sum += c2(cnt[i]) * w[i];
        // printf("sum = %lld\n", sum);
        i64 ans = sum;
        rep(i, 1, A) rep(j, 1, A) {  // i: target, j: last
            if (j == i || !cnt[j]) continue;

            fill(f + 1, f + K + 1, -INF);
            rep(k, 1, A) {
                if (k == i || k == j || !cnt[k]) continue;
                rrep(c, K, cnt[k]) {
                    i64 A = cnt[i] + c;
                    i64 B = cnt[k];
                    f[c] = max(
                        f[c],
                        f[c - B] + (c2(A) - c2(A - B)) * w[i] - c2(B) * w[k]
                    );
                }
            }

            // printf("i = %d, j = %d\n", i, j);
            rep(c, 0, K) {
                // printf("%lld ", f[c]);
                i64 A = cnt[i] + c;
                i64 B = min(K - c, cnt[j]);
                ans = max(
                    ans,
                    max(sum + f[c],
                        sum + f[c] + (c2(A + B) - c2(A)) * w[i] -
                        (c2(cnt[j]) - c2(cnt[j] - B)) * w[j])
                );
            }
            // puts("");
        }

        printf("%lld\n", ans);
    }

    return 0;
}
