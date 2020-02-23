#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MOD 10000007

typedef long long i64;

vector<int> fac[NMAX + 10];
bool mark[NMAX + 10];
int query[NMAX + 10], q;
int pr[NMAX + 10], cnt;
i64 ans[NMAX + 10], k[NMAX + 10];

void initialize() {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        query[++q] = n;
        mark[n] = true;
    }
}

int main() {
    initialize();

    for (int i = 2; i <= NMAX; i++) {
        if (!fac[i].empty())
            continue;
        else
            pr[cnt++] = i;
        for (int j = i; j <= NMAX; j += i)
            fac[j].push_back(i);
    }

    for (int n = 1; n <= NMAX; n++) {
        int m = n;
        for (int p : fac[n]) {
            int kp = 0;
            while (m % p == 0) {
                kp++;
                m /= p;
            }
            k[p] += kp;
        }

        if (mark[n]) {
            i64 a = 1;
            for (int i = 0; i < cnt; i++) {
                int p = pr[i];
                a = a * ((k[p] + 1) * (k[p] + 2) / 2) % MOD;
            }
            ans[n] = a;
        }
    }

    for (int i = 1; i <= q; i++)
        printf("%lld\n", ans[query[i]]);
    return 0;
}