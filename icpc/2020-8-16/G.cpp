#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MOD 1000000007

typedef long long i64;

int n;
char s[NMAX + 10];

void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

void _main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int rcnt = 0, gcnt = 0;
    i64 ans = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?')
            ans = ans * 2 % MOD;
        if (s[i] == 'R')
            rcnt++;
        if (s[i] == 'G')
            gcnt++;
    }

    bool ok = false;
    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
    if (s[i] == 'R' && s[j] == 'R' && (i + j) % 2 == 0) {
        int k = (i + j) / 2;
        if (s[k] == 'G')
            ok = true;
    }

    if (!ok) {
        for (int i = 1; i <= n; i++)
        for (int l = 1; l <= n; l += 2) {
            int cnt = 0;
            for (int j = i; j <= n; j += l) {
                if (s[j] == 'G')
                    break;
                if (s[j] == 'R')
                    cnt++;
                if (j > i && cnt == rcnt) {
                    add(ans, MOD - 1);
                    //printf("i=%d, l=%d, j=%d\n", i, l, j);
                }
            }
        }

        if (rcnt == 1)
            add(ans, MOD - 1);
        if (rcnt == 0)
            add(ans, MOD - (n - gcnt) - 1);
    }

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
