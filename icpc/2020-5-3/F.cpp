#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define EPS 1e-8

typedef long double d8;

bool eq(d8 x, d8 y) {
    return fabsl(x - y) < EPS;
}

struct vec {
    d8 x, y;

    vec ccw() const {
        return {-y, x};
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    vec operator/(d8 k) const {
        return {x / k, y / k};
    }

    vec operator*(d8 k) const {
        return {x * k, y * k};
    }

    d8 operator%(const vec &z) const {
        return x * z.x + y * z.y;
    }

    d8 operator^(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

struct event {
    d8 t;
    int v;

    bool operator<(const event &z) const {
        return t < z.t;
    }
};

int m;
event ev[NMAX * 2 + 10];

int scanline() {
    sort(ev, ev + m);
    int ans = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        if (i && !eq(ev[i - 1].t, ev[i].t)) {
            assert(cnt >= 0);
            ans = max(ans, cnt);
        }
        cnt += ev[i].v;
    }

    return ans;
}

int n, ans;
vec diag, q[4];
vec p[NMAX + 10];

template <typename TFunc>
bool cut(int i, vec &u1, vec &u2, const TFunc &f) {
    for (int j = 0; j < 4; j++) {
        vec o = (q[j] + p[i]) / 2;
        vec v = (q[j] - p[i]).ccw();
        d8 c1 = v ^ (u1 - o);
        d8 c2 = v ^ (u2 - o);
        if (c1 > -EPS && c2 > -EPS)
            return false;
        else {
            // vec u = o + v / v.x * (x0 - o.x);
            vec u = f(o, v);
            if (c1 >= EPS)
                u1 = u;
            else if (c2 >= EPS)
                u2 = u;
        }
    }

    return true;
}

void solve_x(d8 x0) {
    m = 0;
    for (int i = 1; i <= n; i++) {
        vec u1 = {x0, q[3].y - EPS}, u2 = {x0, q[0].y + EPS};

        bool ok = cut(i, u1, u2, [x0](const vec &o, const vec &v) {
            return o + v / v.x * (x0 - o.x);
        });
        if (ok) {
            assert(u1.y <= u2.y - EPS);
            assert(eq(u1.x, x0));
            assert(eq(u2.x, x0));
            ev[m++] = {u1.y, +1};
            ev[m++] = {u2.y, -1};
        }
    }

    int cnt = scanline();
    ans = min(ans, n - cnt);
}

void solve_y(d8 y0) {
    m = 0;
    for (int i = 1; i <= n; i++) {
        vec u1 = {q[0].x - EPS, y0}, u2 = {q[3].x + EPS, y0};

        bool ok = cut(i, u1, u2, [y0](const vec &o, const vec &v) {
            return o + v / v.y * (y0 - o.y);
        });
        if (ok) {
            assert(u1.x <= u2.x - EPS);
            assert(eq(u1.y, y0));
            assert(eq(u2.y, y0));
            ev[m++] = {u1.x, +1};
            ev[m++] = {u2.x, -1};
        }
    }

    int cnt = scanline();
    ans = min(ans, n - cnt);
}

int main() {
    scanf("%d%Lf%Lf%Lf%Lf", &n, &q[0].x, &q[0].y, &diag.x, &diag.y);
    diag.y *= -1;
    for (int i = 1; i <= n; i++)
        scanf("%Lf%Lf", &p[i].x, &p[i].y);
    q[1] = q[0] + vec{diag.x, 0};
    q[2] = q[0] + vec{0, diag.y};
    q[3] = q[0] + diag;

    ans = n;
    solve_x(q[0].x);
    solve_x(q[3].x);
    solve_x((q[0].x + q[3].x) / 2);
    solve_y(q[0].y);
    solve_y(q[3].y);
    solve_y((q[0].y + q[3].y) / 2);
    printf("%d\n", ans);
    return 0;
}