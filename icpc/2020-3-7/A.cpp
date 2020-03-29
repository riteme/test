#include <cstdio>
#include <cstring>

#include <tr1/unordered_map>
#include <algorithm>

using namespace std;
using namespace std::tr1;

#define NMAX 1000000
#define MOD 1000000007

typedef long long i64;

bool mark[NMAX + 10];
int pr[NMAX + 10], pcnt;
int cnt[NMAX + 10], m;
i64 C[500][500];

int main() {
    for (int i = 0; i < 500; i++)
        C[i][0] = 1;
    for (int i = 1; i < 500; i++)
    for (int j = 1; j <= i; j++)
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;

    for (int i = 2; i <= NMAX; i++) {
        if (!mark[i])
            pr[pcnt++] = i;
        for (int j = 0; i64(i) * pr[j] <= NMAX; j++) {
            mark[i * pr[j]] = true;
            if (i % pr[j] == 0)
                break;
        }
    }

    int n;
    while (scanf("%d", &n) != EOF) {
        tr1::unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            for (int j = 0; i64(pr[j]) * pr[j] <= v; j++) {
                while (v % pr[j] == 0) {
                    v /= pr[j];
                    mp[pr[j]]++;
                }
            }
            if (v > 1)
                mp[v]++;
        }

        m = 0;
        for (tr1::unordered_map<int, int>::iterator it = mp.begin();
            it != mp.end(); it++)
            cnt[m++] = it->second;

        i64 ans = 0;
        for (int k = 0; k <= n; k++) {
            i64 ret = 1;
            for (int j = 0; j < m; j++)
                ret = ret * C[cnt[j] + n - k - 1][cnt[j]] % MOD;
            ans = (ans + (k & 1 ? -1 : 1) * C[n][k] * ret) % MOD;
        }

        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }

    return 0;
}