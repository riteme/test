#include <cstdio>
#include <cassert>
#include <cstring>

#include <set>
#include <deque>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n;
i64 a[NMAX + 10], t[NMAX + 10], f[NMAX + 10];

void chkmin(i64 &a, i64 b) {
    if (a > b)
        a = b;
}

void solve() {
    deque<int> q;
    multiset<i64> h;

    auto push_back = [&](int i) {
        if (q.size()) {
            int j = q.back();
            h.insert(f[j] + 2 * a[i]);
        }

        q.push_back(i);
    };

    auto pop_front = [&] {
        int i = q.front();
        q.pop_front();

        if (q.size()) {
            int j = q.front();
            auto it = h.find(f[i] + 2 * a[j]);
            assert(it != h.end());
            h.erase(it);
        }
    };

    auto pop_back = [&] {
        int i = q.back();
        q.pop_back();

        if (q.size()) {
            int j = q.back();
            auto it = h.find(f[j] + 2 * a[i]);
            assert(it != h.end());
            h.erase(it);
        }
    };

    for (int i = 1; i <= n; i++) {
        while (q.size() && f[q.front()] <= t[i]) {
            pop_front();
        }

        while (q.size() && a[q.back()] <= a[i]) {
            pop_back();
        }

        push_back(i);

        f[i] = t[i] + 2 * a[q.front()];
        if (h.size())
            chkmin(f[i], *h.begin());
    }

    printf("%lld\n", f[n]);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld", t + i, a + i);
        }

        solve();
    }

    return 0;
}