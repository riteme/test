#include <cstdio>
#include <cstring>

#include <set>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

struct ratio {
    i64 a, b;

    void print() {
        reduce();
        printf("%lld/%lld\n", a, b);
    }

    void reduce() {
        i64 r = __gcd(a, b);
        a /= r;
        b /= r;
    }

    bool operator<(const ratio &z) const {
        return a * z.b < b * z.a;
    }
};

int n, m;
int l[NMAX + 10], r[NMAX + 10], pos[NMAX + 10];
vector<int> a[NMAX + 10], ins[NMAX + 10];

struct cmp {
    bool operator()(int i, int j) const {
        return tie(r[i], i) < tie(r[j], j);
    }
};

void _main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        ins[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", l + i);
        r[i] = pos[i] = 0;
        a[i].clear();
        ins[l[i]].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int w, t;
        scanf("%d%d", &w, &t);
        a[t].push_back(w);
        r[t]++;
    }

    for (int i = 1; i <= m; i++) {
        sort(a[i].begin(), a[i].end(), greater<i64>());
    }

    ratio ans = {0, 1};
    i64 sum = 0;
    set<int, cmp> buc;
    for (int c = 1; c <= n; c++) {
        for (int i : ins[c]) {
            buc.insert(i);
        }

        while (!buc.empty() && r[*buc.begin()] < c) {
            buc.erase(buc.begin());
        }

        for (int i : buc) {
            for ( ; pos[i] < c; pos[i]++) {
                sum += a[i][pos[i]];
            }
        }

        ratio val = {sum, c};
        if (ans < val)
            ans = val;
    }

    ans.print();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}