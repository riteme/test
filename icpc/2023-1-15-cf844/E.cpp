#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;
constexpr int XMAX = 1000000000;

struct ran {
    mutable int i, l, r;

    bool contain(const ran &z) const {
        return l <= z.l && z.r <= r;
    }

    bool operator<(const ran &z) const {
        return l < z.l;
    }
};

void push1(const ran &v, set<ran> &s) {
    auto ui = prev(s.upper_bound(v));
    if (ui->contain(v))
        return;

    auto wi = s.lower_bound(v);
    ui = prev(wi);
    ui->r = min(ui->r, v.l - 1);
    while (v.contain(*wi)) {
        wi = s.erase(wi);
    }
    wi->l = max(wi->l, v.r + 1);
    s.insert(v);
}

auto greedy(const vector<ran> &a) -> set<ran> {
    set<ran> s;
    s.insert({0, 0, 0});
    s.insert({0, XMAX + 1, XMAX + 1});

    for (auto &v : a) {
        push1(v, s);
    }

    return s;
}

int n;
vector<ran> a[3];
set<ran> s[3];
ran ans[NMAX + 10];

void push2(const ran &v) {
    auto ui1 = prev(s[1].upper_bound(v));
    auto ui2 = prev(s[2].upper_bound(v));
    bool c1 = ui1->contain(v);
    bool c2 = ui2->contain(v);
    if (c1 && c2)
        return;
    if (c1) {
        push1(v, s[2]);
    } else if (c2) {
        push1(v, s[1]);
    } else {
        push1(v, s[1]);
        push1(v, s[2]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int k = 0; k < 3; k++) {
            a[k].clear();
        }
        for (int i = 1; i <= n; i++) {
            int u, l, d, r;
            scanf("%d%d%d%d", &u, &l, &d, &r);
            int k = (u == d ? u : 0);
            a[k].push_back({i, l, r});
        }
        for (int k = 0; k < 3; k++) {
            s[k] = greedy(a[k]);
        }

        for (auto &v : s[0]) {
            if (v.i == 0)
                continue;
            push2(v);
        }

        memset(ans + 1, 0, sizeof(ran) * n);
        int area = 0;
        for (int k = 1; k <= 2; k++) {
            for (auto &v : s[k]) {
                if (v.i == 0)
                    continue;
                ans[v.i].i |= 1 << (k - 1);
                ans[v.i].l = v.l;
                ans[v.i].r = v.r;
                area += v.r - v.l + 1;
            }
        }

        printf("%d\n", area);
        for (int i = 1; i <= n; i++) {
            if (ans[i].i == 0)
                puts("0 0 0 0");
            else {
                int u, d;
                if (ans[i].i == 1)
                    u = d = 1;
                if (ans[i].i == 2)
                    u = d = 2;
                if (ans[i].i == 3) {
                    u = 1;
                    d = 2;
                }
                printf("%d %d %d %d\n", u, ans[i].l, d, ans[i].r);
            }
        }
    }
    return 0;
}
