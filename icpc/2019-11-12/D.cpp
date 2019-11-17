#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300
#define END 200
#define K 47

typedef long long i64;

static i64 f[NMAX + 10];
static int p[NMAX + 10], n;
static int to[NMAX + 10];

int main() {
    f[0] = f[1] = 1;
    for (int i = 2; i <= 100; i++)
        f[i] = f[i - 1] + f[i - 2];
    i64 m;
    while (scanf("%lld", &m) != EOF) {
        n = 0;
        for (int i = K; i >= 1; i--) {
            if (m >= f[i]) {
                p[++n] = i;
                m -= f[i];
            }
        }
        memset(to, 0, sizeof(to));
        int j = 1;
        for (int i = 1; i <= n; i++) {
            to[j] = END - p[i];
            j += 2;
        }
        to[j] = j;
        to[j + 1] = j + 1;
        int cnt = 0;
        for (int i = 1; i < END; i++)
            cnt += to[i] != 0;
        printf("%d\n", cnt);
        for (int i = 1; i < END; i++)
            if (to[i]) printf("%d %d\n", i, to[i]);
    }
    return 0;
}
