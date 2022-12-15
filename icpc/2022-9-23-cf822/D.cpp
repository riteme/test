#include <cstdio>

#include <deque>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n, m;
i64 a[NMAX + 10];
i64 b[NMAX + 10];
i64 as[NMAX + 10];
i64 bs[NMAX + 10];
i64 alo[NMAX + 10];
i64 blo[NMAX + 10];
i64 amxp[NMAX + 10];
i64 bmxp[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", a + i);
        }
        reverse(a + 1, a + m + 1);
        for (int i = m + 1; i <= n; i++) {
            b[i - m] = a[i];
        }
        int t = n - m;
        n = m;
        m = t;

        for (int i = 1; i <= n; i++) {
            as[i] = as[i - 1] + a[i];
            alo[i] = max(alo[i - 1], -as[i]);
            if (as[i] > as[amxp[i - 1]])
                amxp[i] = i;
            else
                amxp[i] = amxp[i - 1];
        }
        for (int i = 1; i <= m; i++) {
            bs[i] = bs[i - 1] + b[i];
            blo[i] = max(blo[i - 1], -bs[i]);
            if (bs[i] > bs[bmxp[i - 1]])
                bmxp[i] = i;
            else
                bmxp[i] = bmxp[i - 1];
        }

        int ai = 0, bi = 0, aj = 0, bj = 0;
        deque<int> aq, bq;
        aq.push_back(0);
        bq.push_back(0);
        while (true) {
            int ak = upper_bound(alo, alo + n + 1, bs[bi]) - alo - 1;
            if (ak >= n || ak <= aj) {
                ai = ak;
                break;
            }
            while (aj < ak) {
                aj++;
                while (aq.size() && as[aq.back()] < as[aj]) {
                    aq.pop_back();
                }
                aq.push_back(aj);
            }
            ai = aq.front();
            aq.pop_front();

            int bk = upper_bound(blo, blo + m + 1, as[ai]) - blo - 1;
            if (bk >= m || bk <= bj) {
                bi = bk;
                break;
            }
            while (bj < bk) {
                bj++;
                while (bq.size() && bs[bq.back()] < bs[bj]) {
                    bq.pop_back();
                }
                bq.push_back(bj);
            }
            bi = bq.front();
            bq.pop_front();
        }

        if (ai >= n || bi >= m)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
