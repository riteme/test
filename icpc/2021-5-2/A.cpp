#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

using d64 = double;

constexpr int NMAX = 200000;
constexpr d64 EPS = 1e-8;

bool eq(d64 x, d64 y) {
    return fabs(x - y) < EPS;
}

struct v3 {
    v3() : x(0), y(0), z(0) {}
    v3(d64 _x, d64 _y, d64 _z) : x(_x), y(_y), z(_z) {}

    d64 x, y, z;

    d64 len2() const {
        return (*this) * (*this);
    }

    d64 len() const {
        return sqrt(len2());
    }

    v3 unit() const {
        return (*this) / len();
    }

    v3 operator+(const v3 &w) const {
        return v3(x + w.x, y + w.y, z + w.z);
    }

    v3 operator-(const v3 &w) const {
        return v3(x - w.x, y - w.y, z - w.z);
    }

    v3 operator*(d64 k) const {
        return v3(x * k, y * k, z * k);
    }

    v3 operator/(d64 k) const {
        return v3(x / k, y / k, z / k);
    }

    d64 operator*(const v3 &w) const {
        return x * w.x + y * w.y + z * w.z;
    }

    v3 operator%(const v3 &w) const {
        return v3(
            y * w.z - z * w.y,
            z * w.x - x * w.z,
            x * w.y - y * w.x
        );
    }
};

struct v2 {
    v2() : x(0), y(0) {}
    v2(d64 _x, d64 _y) : x(_x), y(_y) {}

    d64 x, y;

    int idx() const {
        if (x > -EPS && y > -EPS)
            return 0;
        if (x < EPS && y > -EPS)
            return 1;
        if (x < EPS && y < EPS)
            return 2;
        return 3;
    }

    d64 len2() const {
        return (*this) * (*this);
    }

    d64 len() const {
        return hypot(x, y);
    }

    v2 unit() const {
        return (*this) / len();
    }

    v2 operator+(const v2 &z) const {
        return v2(x + z.x, y + z.y);
    }

    v2 operator-() const {
        return v2(-x, -y);
    }

    v2 operator-(const v2 &z) const {
        return v2(x - z.x, y - z.y);
    }

    v2 operator*(d64 k) const {
        return v2(x * k, y * k);
    }

    v2 operator/(d64 k) const {
        return v2(x / k, y / k);
    }

    d64 operator*(const v2 &z) const {
        return x * z.x + y * z.y;
    }

    d64 operator%(const v2 &z) const {
        return x * z.y - y * z.x;
    }
};

void read_block(int &n, v3 *p, v3 &v) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
    }
    scanf("%lf%lf%lf", &v.x, &v.y, &v.z);
}

void project(v3 n, int N, v3 *P, v2 *p) {
    v3 a = n;
    if (eq(a.x, 0))
        tie(a.y, a.z) = make_tuple(-a.z, a.y);
    else
        tie(a.x, a.y) = make_tuple(-a.y, a.x);

    v3 b = (a % n).unit();
    a = (n % b).unit();

    assert(eq(n.len(), 1));
    assert(eq(a.len(), 1));
    assert(eq(b.len(), 1));
    assert(eq(n * a, 0));
    assert(eq(n * b, 0));
    assert(eq(a * b, 0));

    for (int i = 1; i <= N; i++) {
        v3 u = P[i] - n * (n * P[i]);
        p[i] = v2(u * a, u * b);
    }
}

int convex_hull(int n, v2 *p) {
    int o = n;
    for (int i = 1; i < n; i++) {
        if (tie(p[i].x, p[i].y) < tie(p[o].x, p[o].y))
            o = i;
    }

    swap(p[o], p[n]);
    sort(p + 1, p + n, [n, p](const v2 &_u, const v2 &_v) {
        v2 u = _u - p[n];
        v2 v = _v - p[n];
        d64 c = u % v;
        if (eq(c, 0))
            return u.len2() < v.len2();
        return c > 0;
    });

    vector<int> stk = {n};
    for (int i = 1; i < n; i++) {
        while (stk.size() > 1 &&
            (p[stk[stk.size() - 1]] - p[i]) % (p[stk[stk.size() - 2]] - p[i]) > -EPS) {
            stk.pop_back();
        }
        stk.push_back(i);
    }

    for (int i = 1; i < stk.size(); i++) {
        p[i] = p[stk[i]];
    }
    p[stk.size()] = p[n];

    return stk.size();
}

bool inside(const v2 &u, const v2 &x) {
    d64 c = u % x;
    if (eq(c, 0))
        return u * x > -EPS;
    return c > 0;
}

int minkowski_sum(int n, v2 *p, int m, v2 *q, v2 *a) {
    if (n < m) {
        swap(n, m);
        swap(p, q);
    }

    int k = 0;
    if (m < 3) {
        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            a[++k] = p[i] + q[j];
        }
    } else {
        p[n + 1] = p[1];
        p[n + 2] = p[2];

        int j = 1;
        int c = m, d = j % m + 1;
        for (int i = 1; i <= n + 1; i++) {
            a[++k] = p[i] + q[j];
            v2 u = p[i + 1] - p[i];

            while (!inside(u, q[d] - q[j]) || !inside(u, q[c] - q[j])) {
                c = j;
                j = d;
                d = j % m + 1;
                a[++k] = p[i] + q[j];
            }
        }
    }

    return convex_hull(k, a);
}

int N, M;
v3 P[NMAX + 10], Q[NMAX + 10];
v2 p[NMAX + 10], q[NMAX + 10];
v2 a[NMAX + 10];

int main() {
    v3 vel1, vel2;
    read_block(N, P, vel1);
    read_block(M, Q, vel2);

    v3 n = vel1 - vel2;
    // assert(!eq(n.len(), 0));
    if (eq(n.len(), 0))
        puts("NO");
    else {
        n = n.unit();
        project(n, N, P, p);
        project(n, M, Q, q);

        N = convex_hull(N, p);
        M = convex_hull(M, q);

        for (int i = 1; i <= N; i++) {
            p[i] = -p[i];
        }

        int cnt = minkowski_sum(N, p, M, q, a);

        d64 area = 0, sum = 0;
        for (int i = 1; i <= cnt; i++) {
            int j = i % cnt + 1;
            d64 v = a[i] % a[j];
            area += v;
            sum += fabs(v);
        }
        area = fabs(area);

        puts(eq(area, sum) ? "YES" : "NO");
    }

    return 0;
}