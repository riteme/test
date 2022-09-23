#include <cstdio>
#include <cassert>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 300000;

struct vec {
    i64 x, y;

    int quarter() const {
        if (x >= 0 && y >= 0)
            return 0;
        if (x <= 0 && y >= 0)
            return 1;
        if (x <= 0 && y <= 0)
            return 2;
        return 3;
    }

    i64 slen() const {
        return x * x + y * y;
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    i64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    i64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }

    bool operator<(const vec &z) const {
        int q1 = quarter();
        int q2 = z.quarter();
        if (q1 != q2)
            return q1 < q2;
        i64 c = z % (*this);
        if (c == 0)
            return slen() < z.slen();
        return c < 0;
    }
};

int n, q;
vec O;
vec p[NMAX + 10];
int rk[NMAX + 10];
bool zero[NMAX + 10];
int a[NMAX + 10];
int maxl[NMAX + 10];

bool test(int i, int j) {
    i64 c = p[i] % p[j];
    if (c == 0) {
        i64 d = p[i] * p[j];
        if (d <= 0)
            return false;
        return rk[i] > rk[j];
    }
    return c < 0;
}

struct Set {
    set<int> s;
    bool okay = true;

    template <typename TIter>
    void find_neighbors(TIter it, int &prev, int &next) {
        if (it == s.begin()) {
            if (s.size() > 1)
                prev = a[*s.rbegin()];
            else
                prev = 0;
        } else
            prev = a[*std::prev(it)];
        it++;
        if (it == s.end()) {
            if (s.size() > 1)
                next = a[*s.begin()];
            else
                next = 0;
        } else
            next = a[*it];
    }

    void add(int k) {
        auto it = s.insert(rk[k]).first;
        int i, j;
        find_neighbors(it, i, j);
        if (!i || !j)
            okay = true;
        else if (i == j || test(i, j))
            okay = (test(i, k) || test(k, j));
    }

    void remove(int k) {
        auto it = s.find(rk[k]);
        assert(it != s.end());
        int i, j;
        find_neighbors(it, i, j);
        s.erase(it);
        if (!i || !j || i == j || test(i, j))
            okay = true;
    }
};

Set s;

int main() {
    scanf("%d%lld%lld", &n, &O.x, &O.y);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        p[i] = p[i] - O;
        zero[i] = (p[i].slen() == 0);
        a[i] = i;
    }
    sort(a + 1, a + n + 1, [](int i, int j) {
        return p[i] < p[j];
    });
    for (int i = 1; i <= n; i++) {
        rk[a[i]] = i;
    }

    int l = 1;
    for (int r = 1; r <= n; r++) {
        if (zero[r])
            continue;

        s.add(r);
        while (l < r && !s.okay) {
            if (!zero[l])
                s.remove(l);
            l++;
        }
        maxl[r] = l - 1;
    }

    int lastz = 0;
    for (int i = 1; i <= n; i++) {
        if (zero[i])
            lastz = i;
        maxl[i] = max(maxl[i], lastz);
    }

    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        puts(l <= maxl[r] ? "Yes" : "No");
    }

    return 0;
}
