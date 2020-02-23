#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>

using namespace std;

#define BASE 19260817
#define NMAX 2000000
#define MOD 998244353

typedef long long i64;
typedef unsigned long long u64;

int n;
char s[NMAX + 10];
i64 sum[NMAX + 10];
int nxt[NMAX + 10];
unordered_map<u64, i64> cnt;

int main() {
    scanf("%d", &n);
    char *p = s;
    for (int i = 0; i < n; i++) {
        scanf("%s", p);
        int len = strlen(p);
        u64 c = 0, pw = 1;
        for (int i = len - 1; i >= 0; i--) {
            c += pw * p[i];
            pw *= BASE;
            cnt[c]++;
        }

        p += len + 1;
    }

    i64 ans = 0;
    p = s;
    for (int i = 0; i < n; i++) {
        int len = strlen(p);
        u64 c = 0;
        for (int i = 0; i < len; i++) {
            c = c * BASE + p[i];
            sum[i] = cnt[c];

            if (i) {
                int j = nxt[i - 1];
                while (j && p[j] != p[i]) j = nxt[j - 1];
                if (p[j] == p[i]) j++;
                nxt[i] = j;
                if (j) sum[j - 1] -= sum[i];
            }
        }

        for (int i = 0; i < len; i++)
            ans = (ans + 1LL * sum[i] * (i + 1) * (i + 1)) % MOD;

        p += len + 1;
    }

    printf("%lld\n", ans);
    return 0;
}