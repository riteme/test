#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;
constexpr int LMAX = 300;
constexpr int INF = 0x3f3f3f3f;

struct Entry {
    int key, dep;
    mutable int idx = 0;

    bool operator<(const Entry &z) const {
        return key < z.key;
    }
};

using Tree = set<Entry>;

template <typename TIter>
auto build(TIter beg, TIter end) -> Tree {
    Tree tr;
    tr.insert({-INF, 0});
    tr.insert({+INF, 0});
    for ( ; beg != end; beg++) {
        int key = *beg;
        auto it = tr.upper_bound({.key = key});
        tr.insert({key, 1 + max(it->dep, prev(it)->dep)});
    }
    return tr;
}

vector<int> G[NMAX + 10];
i64 f[LMAX + 10][LMAX + 10];
i64 cnt[LMAX + 10];

i64 tsize(int l, int r) {
    return cnt[r] - cnt[l] + G[l].size();
}

// a[0..n - 1], [0, R)
i64 solve1(int *a, int n, int R) {
    for (int i = 0; i <= R; i++) {
        G[i].clear();
        cnt[i] = 0;
        memset(f[i], 0x3f, sizeof(i64) * (R + 1));
    }

    sort(a, a + R);
    for (int i = R; i < n; i++) {
        int j = upper_bound(a, a + R, a[i]) - a;
        G[j].push_back(a[i]);
    }
    cnt[0] = G[0].size();
    for (int i = 1; i <= R; i++) {
        cnt[i] = cnt[i - 1] + 1 + G[i].size();
    }
    for (int i = 0; i <= R; i++) {
        auto tr = build(G[i].begin(), G[i].end());
        f[i][i] = 0;
        for (auto &e : tr) {
            f[i][i] += e.dep;
        }
    }

    for (int l = 2; l <= R + 1; l++)
    for (int i = 0; i + l - 1 <= R; i++) {
        int j = i + l - 1;
        for (int k = i; k < j; k++) {
            f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
        }
        f[i][j] += tsize(i, j);
    }

    return f[0][R];
}

vector<int> buc[NMAX + 10];

// a[0..n - 1], [L, R)
i64 solve0(int *a, int n, int L, int R) {
    if (!L)
        return solve1(a, n, R);

    auto tr = build(a, a + L);
    int idx = 0;
    for (auto &e : tr) {
        e.idx = idx++;
    }

    for (int i = L; i < n; i++) {
        auto it = prev(tr.upper_bound({.key = a[i]}));
        buc[it->idx].push_back(i);
    }

    i64 ans = 0;
    for (auto l = tr.begin(), r = next(l); r != tr.end(); l = r++) {
        ans += r->dep;

        auto &b = buc[l->idx];
        int cnt = 0;
        for (auto &v : b) {
            if (v < R)
                cnt++;
            v = a[v];
        }

        i64 d = max(l->dep, r->dep);
        i64 rax = solve1(&b[0], b.size(), cnt);
        ans += rax + b.size() * d;
    }

    return ans;
}

int n, L, R;
int a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    scanf("%d%d", &L, &R);
    L--;

    i64 ans = solve0(a, n, L, R);
    printf("%lld\n", ans);

    return 0;
}
