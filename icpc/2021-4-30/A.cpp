#include <cstdio>
#include <climits>
#include <cstring>

#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 30000;

struct vec {
    vec() : x(0), y(0) {}
    vec(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    i64 len2() const {
        return x * x + y * y;
    }

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    vec operator*(i64 k) const {
        return vec(x * k, y * k);
    }

    i64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    i64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

i64 area(const vec &a, const vec &b, const vec &c) {
    return abs((a - c) % (b - c));
}

i64 eval(int n, vec *p) {
    auto nxtp = [n](int i) {
        return i + 1 < n ? i + 1 : 0;
    };

    i64 rax = 0;
    auto update = [&rax, p](int i, int j) {
        rax = max(rax, (p[i] - p[j]).len2());
    };

    for (int i = 0, k = 0; i < n; i++) {
        int j = nxtp(i);

        update(i, k);
        update(j, k);

        while (true) {
            int k0 = nxtp(k);
            if (area(p[i], p[j], p[k0]) > area(p[i], p[j], p[k])) {
                k = k0;
                update(i, k);
                update(j, k);
            } else
                break;
        }
    }

    return rax;
}

int n;
vec q[NMAX + 10], tmp[NMAX + 10];

i64 solve() {
    int o = n;
    for (int i = 1; i < n; i++) {
        if (tie(q[i].x, q[i].y) < tie(q[o].x, q[o].y))
            o = i;
    }

    swap(q[n], q[o]);
    sort(q + 1, q + n, [](const vec &_u, const vec &_v) {
        auto u = _u - q[n];
        auto v = _v - q[n];
        auto c = u % v;
        return c ? c > 0 : u.len2() < v.len2();
    });

    vector<int> con;
    con.push_back(n);
    for (int i = 1; i < n; i++) {
        while (con.size() > 1 &&
            (q[con[con.size() - 1]] - q[i]) % (q[con[con.size() - 2]] - q[i]) >= 0) {
            con.pop_back();
        }

        con.push_back(i);
    }

    int cnt = 0;
    for (int i : con) {
        tmp[cnt++] = q[i];
    }

    memcpy(q, tmp, sizeof(vec) * cnt);
    return eval(n, q);
}

i64 T;
vec p[NMAX + 10], d[NMAX + 10];

i64 aha(i64 t) {
    for (int i = 1; i <= n; i++) {
        q[i] = p[i] + d[i] * t;
    }

    return solve();
}

int main() {
    scanf("%d%lld", &n, &T);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld%lld", &p[i].x, &p[i].y, &d[i].x, &d[i].y);
    }

    i64 l = 0, r = T;
    while (l + 50 < r) {
        i64 m1 = (2 * l + r) / 3;
        i64 m2 = (l + 2 * r) / 3;
        i64 v1 = aha(m1);
        i64 v2 = aha(m2);
        if (v1 > v2)
            l = m1;
        else
            r = m2;
    }

    i64 ans = LLONG_MAX, ansp;
    for (int t = max(0LL, l - 1); t <= min(T, r + 1); t++) {
        i64 v = aha(t);
        if (v < ans) {
            ans = v;
            ansp = t;
        }
    }

    printf("%lld\n%lld\n", ansp, ans);
    return 0;
}