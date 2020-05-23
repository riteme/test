#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

#define NMAX 50000
#define MMAX 200000
#define S 700

#define L(i) ((i) * S)
#define R(i) (L(i) + S - 1)

struct item {
    int prod, mu;
};

struct ayaya {
    i64 a[NMAX + 10];
    i64 s[NMAX / S + 10];

    void reset(int n) {
        memset(a + 1,  0, sizeof(i64) * n);
        memset(s, 0, sizeof(i64) * (n / S + 1));
    }

    void modfiy(int x, i64 v) {
        a[x] += v;
        s[x / S] += v;
    }

    i64 query(int r) {
        i64 v = 0;
        for (int i = L(r / S); i <= r; i++) {
            v += a[i];
        }
        for (int i = 0; i < r / S; i++) {
            v += s[i];
        }
        return v;
    }
};

int n, q;
ayaya ds;
i64 saved[NMAX + 10];
vector<item> buc[MMAX + 10];

void modify(int m, int d, i64 v) {
    if (m % d != 0)
        return;

    for (auto &e : buc[m / d]) {
        int k = e.prod * d;
        i64 x = e.mu * v;
        if (k > n)
            continue;

        if (k <= S)
            saved[k] += x;
        else {
            for (int j = k; j <= n; j += k)
                ds.modfiy(j, x);
        }
    }
}

i64 query(int r) {
    i64 ans = ds.query(r);
    for (int i = 1; i <= min(n, S); i++) {
        ans += saved[i] * (r / i);
    }
    return ans;
}

void _main() {
    ds.reset(n);
    memset(saved + 1, 0, sizeof(i64) * n);

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int m, d, v;
            scanf("%d%d%d", &m, &d, &v);
            modify(m, d, v);
        } else {
            int r;
            scanf("%d", &r);
            printf("%lld\n", query(r));
        }
    }
}

void initialize() {
    for (int i = 1; i <= MMAX; i++) {
        buc[i].push_back({1, 1});
    }

    for (int i = 2; i <= MMAX; i++) {
        if (buc[i].size() > 1)
            continue;

        for (int j = i; j <= MMAX; j += i) {
            int c = buc[j].size();
            buc[j].resize(2 * c);
            for (int k = 0; k < c; k++) {
                buc[j][c + k] = {
                    buc[j][k].prod * i,
                    -buc[j][k].mu
                };
            }
        }
    }
}

int main() {
    initialize();

    for (int i = 1; true; i++) {
        scanf("%d%d", &n, &q);
        if (n == 0 && q == 0)
            break;

        printf("Case #%d:\n", i);
        _main();
    }
    return 0;
}