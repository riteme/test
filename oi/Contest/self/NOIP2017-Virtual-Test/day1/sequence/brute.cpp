#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 20
#define MOD 577777777

static int n, m;
static int seq[NMAX + 10];
static int f[NMAX + 10];

int dp() {
    int ans = 1;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = 1;

        for (int j = 1; j < i; j++) {
            if (seq[j] <= seq[i])
                f[i] = max(f[i], f[j] + 1);
        }

        ans = max(ans, f[i]);
    }

    return ans;
}

bool inc() {
    seq[1]++;
    int i;
    for (i = 1; seq[i] > m && i <= n; i++) {
        seq[i] = 1;
        seq[i + 1]++;
    }

    return i <= n;
}

int main() {
#ifdef USE_FILE_IO
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        seq[i] = 1;
    }

    int ans = 0;
    do {
        // for (int i = 1; i <= n; i++) {
        //     printf("%d ", seq[i]);
        // }
        // int val = dp();
        // printf("= %d\n", val);
        // ans += val;
        ans += dp();
        if (ans >= MOD)
            ans -= MOD;
    } while (inc());

    printf("%d\n", ans);

    return 0;
}
