#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using d64 = double;

constexpr d64 EPS = 1e-8;
constexpr int NMAX = 100000;

bool eq(d64 x, d64 y) {
    return fabs(x - y) < EPS;
}

struct vec2 {
    d64 x, y;

    int idx() const {
        if (x >= 0 && y >= 0)
            return 1;
        if (x <= 0 && y >= 0)
            return 2;
        if (x <= 0 && y <= 0)
            return 3;
        return 4;
    }

    d64 len() const {
        return hypot(x, y);
    }

    vec2 operator+(const vec2 &z) const {
        return {x + z.x, y + z.y};
    }

    vec2 operator-(const vec2 &z) const {
        return {x - z.x, y - z.y};
    }

    vec2 operator*(d64 v) const {
        return {x * v, y * v};
    }

    d64 operator*(const vec2 &z) const {
        return x * z.x + y * z.y;
    }

    d64 operator%(const vec2 &z) const {
        return x * z.y - y * z.x;
    }
};

using vi = vector<int>;

int n;
bool mark[NMAX + 10];
vec2 p[NMAX + 10], o;

vi build(int s, int t, bool dup = false) {
    vi q;
    q.push_back(s);
    for (int i = s % n + 1; ; i = i % n + 1) if (!mark[i]) {
        while (q.size() > 1 &&
            (p[i] - p[q[q.size() - 2]]) % (p[q[q.size() - 1]] - p[q[q.size() - 2]]) > -EPS) {
            q.pop_back();
        }

        if (dup || i != s)
            q.push_back(i);

        if (i == t)
            break;
    }
    return q;
}

d64 sum(const vi &q) {
    d64 s = 0;
    for (int i = 0; i + 1 < q.size(); i++) {
        s += (p[q[i + 1]] - p[q[i]]).len();
    }
    return s;
}

vi con;
d64 w[NMAX + 10], pre[NMAX + 10], suf[NMAX + 10];

int prep(int i) {
    return i == 0 ? con.size() - 1 : i - 1;
}

int nxtp(int i) {
    return i + 1 == con.size() ? 0 : i + 1;
}

void solve() {
    d64 ans = 0;

    int u = 1;
    for (int i = 2; i <= n; i++) {
        if (eq(p[u].x, p[i].x) ? p[i].y > p[u].y : p[i].x > p[u].x)
            u = i;
    }
    con = build(u, u);

    for (int _i = 0; _i < con.size(); _i++) {
        int i = con[_i];
        int j = con[prep(_i)], k = con[nxtp(_i)];
        d64 s0 = sum({j, i, k});

        mark[i] = 1;

        auto neo = build(j, k, true);
        d64 sneo = sum(neo);
        w[_i + 1] = s0 - sneo;

        for (int _x = 1; _x + 1 < neo.size(); _x++) {
            int x = neo[_x];
            int y = neo[_x - 1], z = neo[_x + 1];
            d64 s1 = sum({y, x, z});

            mark[x] = 1;
            auto cur = build(y, z, true);
            mark[x] = 0;

            d64 val = s0 - (sneo - s1 + sum(cur));
            //printf("#1, i=%d, j=%d, k=%d, x=%d, y=%d, z=%d, val=%.3lf\n", i, j, k, x, y, z, val);
            ans = max(ans, val);
        }

        mark[i] = 0;
    }


    for (int _i = 0; _i < con.size(); _i++) {
        int i = con[_i];
        int j = con[prep(_i)];
        int k = con[nxtp(_i)];
        int l = con[nxtp(nxtp(_i))];
        d64 s0 = sum({j, i, k, l});

        mark[i] = mark[k] = 1;
        auto neo = build(j, l, true);
        d64 val = s0 - sum(neo);
        //printf("#2, i=%d, j=%d, k=%d, l=%d, val=%.3lf\n", i, j, k, l, val);
        ans = max(ans, val);
        mark[i] = mark[k] = 0;
    }

    for (int i = 1; i <= con.size(); i++) {
        pre[i] = max(pre[i - 1], w[i]);
    }
    for (int i = con.size(); i > 0; i--) {
        suf[i] = max(suf[i + 1], w[i]);
    }
    for (int i = 1; i <= con.size(); i++) {
        d64 mx = suf[i + 2];
        if (i > 1)
            mx = max(mx, pre[i - 2]);

        d64 val = mx + w[i];
        //printf("#3, i=%d, val=%.3lf\n", con[i - 1], val);
        ans = max(ans, val);
    }

    printf("%.10lf\n", ans);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        o = o + p[i];
    }
    o = o * (1.0 / n);
    for (int i = 1; i <= n; i++) {
        p[i] = p[i] - o;
    }

    sort(p + 1, p + n + 1, [](const vec2 &u, const vec2 &v) {
        if (u.idx() != v.idx())
            return u.idx() < v.idx();
        d64 c = u % v;
        if (eq(c, 0.0))
            return u.len() < v.len();
        return c > 0;
    });

    solve();

    return 0;
}
