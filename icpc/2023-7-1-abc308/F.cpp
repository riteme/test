#include <algorithm>
#include <cstdio>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

struct Coup {
    int L, D, R;
};

int m, m;
i64 P[NMAX + 10];
Coup C[NMAX + 10];
int a[NMAX + 10];

void modify(int x, int v) {
    x++;
    for (; x <= m + 1; x += x & -x) {
        a[x] += v;
    }
}

int query(int r) {
    r++;
    int v = 0;
    for (; r; r -= r & -r) {
        v += a[r];
    }
    return v;
}

int main() {
    scanf("%d%d", &m, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", P + i);
    }
    sort(P + 1, P + m + 1, [](i64 u, i64 v) { return u > v; });
    for (int i = 1; i <= m; i++) {
        scanf("%d", &C[i].L);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &C[i].D);
    }

    sort(C + 1, C + m + 1, [](Coup &u, Coup &v) { return u.L > v.L; });
    int i = 0;
    for (int j = 1; j <= m; j++) {
        while (i < m && P[i + 1] >= C[j].L) {
            i++;
        }
        C[j].R = i;
    }

    i64 ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += P[i];
    }

    sort(C + 1, C + m + 1, [](Coup &u, Coup &v) { return u.D > v.D || (u.D == v.D && u.R > v.R); });
    for (int i = 1; i <= m; i++) {
        int k = query(C[i].R);
        // printf("i=%d, k=%d, C[i]={L=%d, D=%d, R=%d}\n", i, k, C[i].L, C[i].D, C[i].R);
        if (k < C[i].R) {
            ans -= C[i].D;

            int l = 1, r = C[i].R;
            while (l < r) {
                int m = (l + r) / 2 + 1;
                int v = query(C[i].R) - query(m - 1);
                if (v == C[i].R - m + 1)
                    r = m - 1;
                else
                    l = m;
            }
            modify(l, +1);
        }
    }

    printf("%lld\n", ans);
    return 0;
}
