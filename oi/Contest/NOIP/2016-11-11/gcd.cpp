#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long int64;

static int n;
static vector<int> son[NMAX + 10];
static int seq[NMAX + 10];
static int cnt[NMAX + 10];
static int64 f[NMAX + 10];

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);

    for (int i = 1; i <= NMAX; i++)
        for (int j = i << 1; j <= NMAX; j += i)
            son[j].push_back(i);

    int t;
    scanf("%d", &t);

    while (t--) {
        memset(cnt, 0, sizeof(cnt));
        memset(f, 0, sizeof(f));

        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            scanf("%d", seq + i);
            cnt[seq[i]]++;
            f[seq[i]] += seq[i];
        }

        sort(seq + 1, seq + n + 1);
        for (int i = 1; i <= NMAX; i++)
            for (int j = i << 1; j <= NMAX; j += i)
                cnt[i] += cnt[j];

        for (int i = NMAX; i > 1; i--) {
            for (size_t pos = 0; pos < son[i].size(); pos++) {
                int j = son[i][pos];

                f[j] = max(f[j], f[i] + (cnt[j] - cnt[i]) * j);
            }
        }

        printf("%lld\n", f[1]);
    }

    return 0;
}
