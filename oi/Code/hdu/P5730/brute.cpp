#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 313

static int n;
static int cnt[NMAX + 10];
static int f[NMAX + 10];

void initialize() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", cnt + i);
        cnt[i] %= MOD;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (!n)
            break;

        initialize();

        memset(f, 0, sizeof(f));
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                f[i] = (f[i] + f[j] * cnt[i - j]) % MOD;
            }
        }

        printf("%d\n", f[n]);
    }

    return 0;
}

