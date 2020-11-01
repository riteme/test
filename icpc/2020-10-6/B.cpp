#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;
using f64 = double;

const f64 PI = acos(-1);
constexpr f64 EPS = 1e-9;
constexpr f64 INF = 1e99;
constexpr int NMAX = 1000;

bool eq(f64 x, f64 y) {
    return fabs(x - y) < EPS;
}

struct vec2 {
    f64 x, y;

    f64 len2() const {
        return x * x + y * y;
    }

    vec2 operator+(const vec2 &z) const {
        return {x + z.x, y + z.y};
    }

    vec2 operator-(const vec2 &z) const {
        return {x - z.x, y - z.y};
    }

    vec2 operator*(f64 k) const {
        return {x * k, y * k};
    }

    vec2 operator/(f64 k) const {
        return {x / k, y / k};
    }

    f64 operator*(const vec2 &z) const {
        return x * z.x + y * z.y;
    }

    f64 operator/(const vec2 &z) const {
        return x * z.y - y * z.x;
    }
};

template <typename T>
struct vec3 {
    using self = vec3<T>;

    vec3()
        : x(0), y(0), z(0) {}
    vec3(T _x, T _y, T _z)
        : x(_x), y(_y), z(_z) {}

    template <typename U>
    vec3(const vec3<U> &w)
        : x(w.x), y(w.y), z(w.z) {}

    T x, y, z;

    T len() const {
        T s = x * x + y * y + z * z;
        return sqrt(s);
    }

    self operator+(const self &w) const {
        return {x + w.x, y + w.y, z + w.z};
    }

    self operator-(const self &w) const {
        return {x - w.x, y - w.y, z - w.z};
    }

    self operator*(T k) const {
        return {x * k, y * k, z * k};
    }

    T operator*(const self &w) const {
        return x * w.x + y * w.y + z * w.z;
    }

    self operator%(const self &w) const {
        return {
            y * w.z - z * w.y,
            z * w.x - x * w.z,
            x * w.y - y * w.x
        };
    }
};

using vec3i = vec3<i64>;
using vec3f = vec3<f64>;

int n;
f64 ans = INF;
vec3i P[NMAX + 10];
bool off[NMAX + 10][NMAX + 10];

struct MinimalCircle {
    MinimalCircle() {
        memset(this, 0, sizeof(MinimalCircle));
    }

    int cnt;
    f64 r2;
    vec2 p[NMAX + 10], o[4], res;

    void ball() {
        vec2 q[2];
        f64 m[2][2], sol[2], l[2], d;
        res = {0, 0};
        r2 = 0;

        switch (cnt) {
            case 1:
                res = o[0];
                break;

            case 2:
                res = (o[0] + o[1]) / 2;
                r2 = (res - o[0]).len2();
                break;

            case 3:
                for (int i = 0; i < 2; i++) {
                    q[i] = o[i + 1] - o[0];
                }
                for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++) {
                    m[i][j] = q[i] * q[j] * 2;
                }
                for (int i = 0; i < 2; i++) {
                    sol[i] = q[i].len2();
                }
                d = m[0][0] * m[1][1] - m[0][1] * m[1][0];
                if (eq(d, 0.0))
                    return;
                l[0] = (sol[0] * m[1][1] - sol[1] * m[0][1]) / d;
                l[1] = (sol[1] * m[0][0] - sol[0] * m[1][0]) / d;
                res = o[0] + q[0] * l[0] + q[1] * l[1];
                r2 = (res - o[0]).len2();
                break;
        }
    }

    void recur(int m) {
        ball();
        if (cnt < 3) {
            for (int i = 0; i < m; i++)
            if ((res - p[i]).len2() >= r2 + EPS) {
                o[cnt++] = p[i];
                recur(i);
                cnt--;
                if (i > 0) {
                    vec2 t = p[i];
                    memmove(p + 1, p, sizeof(vec2) * i);
                    p[0] = t;
                }
            }
        }
    }

    f64 area() {
        r2 = -1;
        res = {0, 0};
        for (int i = 0; i < n; i++)
        if ((res - p[i]).len2() >= r2 + EPS) {
            cnt = 1;
            o[0] = p[i];
            recur(i);
        }
        return PI * r2;
    }
} solver;

void initialize(int &u, int &v) {
    u = 0;
    for (int i = 1; i < n; i++) {
        if (P[i].x < P[u].x || (P[i].x == P[u].x && P[i].y < P[u].y))
            u = i;
    }

    swap(P[0], P[u]);
    u = 0;
    v = 1;
    for (int i = 2; i < n; i++) {
        vec3i dv = P[v] - P[0];
        vec3i di = P[i] - P[0];
        i64 c = di.x * dv.y - di.y * dv.x;
        if (c > 0)
            v = i;
    }
}

void normalize(vec3f &w) {
    w = w * (1.0 / w.len());
}

void update(int i, int j, int k) {
    /*
    printf(
        "(%lld,%lld,%lld) - (%lld,%lld,%lld) - (%lld,%lld,%lld)\n",
        P[i].x, P[i].y, P[i].z,
        P[j].x, P[j].y, P[j].z,
        P[k].x, P[k].y, P[k].z
    );
    */

    vec3f u = P[k] - P[i];
    vec3f v = P[j] - P[i];
    normalize(u);
    v = v - u * (v * u);
    normalize(v);

	vec3f d = u % v;
    normalize(d);

	f64 mi = INF, mx = -INF;
	for (int x = 0; x < n; x++) {
        vec3f w = P[x] - P[i];
        f64 s = w * d;
        mi = min(mi, s);
        mx = max(mx, s);

        w = w - d * s;
        solver.p[x] = {w * u, w * v};
	}

    f64 rax = solver.area();
    rax *= mx - mi;
    //printf("rax = %.3lf\n", rax);
    ans = min(ans, rax);
}

void wrap(int i, int j) {
    if (off[i][j])
        return;

    vec3i v = P[j] - P[i];
    int k = -1;
    for (int p = 0; p < n; p++)
    if (p != i && p != j) {
        if (k == -1 || ((P[p] - P[i]) % (P[k] - P[i])) * v > 0)
            k = p;
    }

    update(i, k, j);

    off[i][j] = off[k][i] = off[j][k] = true;
    wrap(i, k);
    wrap(k, j);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld", &P[i].x, &P[i].y, &P[i].z);
    }

    int u, v;
    initialize(u, v);
    wrap(u, v);
    //wrap(v, u);
    printf("%.10lf\n", ans);

    return 0;
}
