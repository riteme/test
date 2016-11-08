#include <cassert>
#include <cstdio>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long long int64;

static int n, m;
static int64 h[NMAX + 10][NMAX + 10];
static int64 seq[NMAX + 10];
static int pos = 0;
static int ds[NMAX + 10];
static bool marked[NMAX + 10];

int main() {
    freopen("max.in", "r", stdin);
    freopen("max.out", "w", stdout);
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &h[i][j]);
            h[i][j] += h[i - 1][j] + h[i][j - 1] - h[i - 1][j - 1];
        }
    }

    int answer = 1;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            seq[0] = 0;
            ds[0] = 0;
            pos = 0;
            for (int i = 1; i <= m; i++) {
                seq[i] = h[r][i] - h[l - 1][i];
                if (seq[i] < seq[ds[pos]]) {
                    ds[++pos] = i;
                    marked[i] = true;
                } else 
                    marked[i] = false;
            }

            for (int i = 1; i <= m; i++) {
                if (marked[i])
                    continue;

                int a = 0, b = pos;
                while (a + 1 < b) {
                    int mid = (a + b) >> 1;

                    if (seq[ds[mid]] < seq[i])
                        b = mid;
                    else
                        a = mid + 1;
                }

                if (a != b && seq[ds[a]] >= seq[i])
                    a = b;
                answer = max(answer, (r - l + 1) * (i - ds[a]));
            }
        }
    }

    printf("%d\n", answer);
    return 0;
}
