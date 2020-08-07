#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define MOD 1000000007

using i64 = long long;

#define NMAX 1000010

int T;
int pos[1000];
bool req[NMAX + 10];
// vector<i64*> req[NMAX + 10];
int ans[NMAX + 10];
// vector<int> buc[NMAX + 10];
int buc[NMAX + 10][8];
int pr[NMAX / 10 + 10], pcnt;
int pw[NMAX + 10];

i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; a = a * a % MOD, k >>= 1) {
        if (k & 1)
            r = r * a % MOD;
    }
    return r;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

i64 eval(int n) {  // get lcm(1..n) / n
    i64 ret = inv(n);
    /*
    for (int i = 0; i < pcnt; i++) {
        ret = ret * qpow(pr[i], cnt[pr[i]]) % MOD;
    }
    */
//    for (int i = 2; i <= NMAX; i++) if (pw[i] > 1) {
    for (int i = 0; i < pcnt; i++) if (pw[pr[i]] > 1) {
    //    ret = ret * qpow(i, cnt[i]) % MOD;
       ret = ret * pw[pr[i]] % MOD;
   }
    return ret;
}

int main() {
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int x;
        scanf("%d", &x);
        // req[x + 1].push_back(ans + i);
        req[x + 1] = true;
        pos[i] = x + 1;
    }

    for (int i = 2; i <= NMAX; i++) {
        // if (buc[i].size() > 0)
        if (buc[i][0] > 0)
            continue;
        pr[pcnt++] = i;
        for (int j = i; j <= NMAX; j += i) {
            // buc[j].push_back(i);
            buc[j][++buc[j][0]] = i;
        }
    }

    for (int i = 1; i <= NMAX; i++) {
        // for (int p : buc[i]) {
        for (int j = 1; j <= buc[i][0]; j++) {
            int p = buc[i][j];
            int k = 0, x = i;
            i64 tmp = 1;
            while (x % p == 0) {
                x /= p;
                tmp = tmp * p % MOD;
                k++;
            }
            // cnt[p] = max(cnt[p], k);
            pw[p] = max(i64(pw[p]), tmp);
        }

        if (req[i]) {
            ans[i] = eval(i);
        }
        // i64 val = !req[i].empty() ? eval(i) : -1;
        // for (i64 *ptr : req[i]) {
            // *ptr = val;
        // }
    }

    for (int i = 0; i < T; i++) {
        // printf("%lld\n", ans[i]);
        printf("%d\n", ans[pos[i]]);
    }

    return 0;
}