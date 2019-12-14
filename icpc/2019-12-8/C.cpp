#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 1000000007

typedef long long i64;

static int n;
static char s[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        i64 sum = 1, ans = 1;
        for (int i = n; i >= 1; i--) {
            if (s[i] == '1') {
                ans = (ans + sum) % MOD;
                sum = sum * 3 % MOD;
            } else
                sum = sum * 2 % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
