#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MPI 3.141592652589793
#define S 5e7
#define SZ 2000
#define NMAX 100000
#define TMAX 50
#define ANGLE 1.92608175354679
#define EPS 1e-9

bool eq(double x, double y) {
    return fabs(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    vec cw() const {
        return vec(y, -x);
    }

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    vec operator*(double k) const {
        return vec(x * k, y * k);
    }

    double operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    double operator%(const vec &z) const {
        return x * z.y - z.x * y;
    }
};

struct line {
    vec v;
    double t;
};

int n;
line l1, l2;
vec p[NMAX + 10];
double a[NMAX + 10];

vec dir(double t) {
    return vec(cos(t), sin(t));
}

bool cmp(const vec &u, const vec &v) {
    return (u % l1.v) > (v % l1.v);
}

bool contain(double L, double R, double x) {
    return L - EPS < x && x < R + EPS;
}

bool isect(double L1, double R1, double L2, double R2) {
    return contain(L1, R1, L2) || contain(L1, R1, R2) || contain(L2, R2, L1) || contain(L2, R2, R1);
}

int test(double t) {
    l2.v = dir(t);
    for (int i = 1; i <= n; i++) {
        a[i] = p[i] % l2.v;
    }
    int k = n / 2;
    sort(a + 1, a + k + 1);
    sort(a + k + 1, a + n + 1);
    double L1 = a[k / 2], R1 = a[k / 2 + 1];
    double L2 = a[k + k / 2], R2 = a[k + k / 2 + 1];
    double L = max(L1, L2);
    double R = min(R1, R2);
    l2.t = (L + R) / 2;

    if (isect(L1, R1, L2, R2))
        return 0;
    else if (L1 < L2)
        return -1;
    else
        return 1;
}

void output(const line &l, double k) {
    vec u = l.v.cw() * l.t;
    double mi = 1e99;
    vec out;
    for (int i = k - SZ; i <= k + SZ; i++) {
        vec z = u + l.v * i;
        int x = z.x, y = z.y;
        for (int nx = x; nx <= x + 1; nx++)
        for (int ny = y; ny <= y + 1; ny++) {
            vec tmp = vec(nx, ny);
            double dist = fabs(tmp % l.v - l.t);
            if (dist < mi) {
                mi = dist;
                out = tmp;
            }
        }
    }
    int x = out.x, y = out.y;
    printf("%d %d ", x, y);
}

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }

    l1.v = dir(ANGLE);
    for (int i = 1; i <= n; i++) {
        a[i] = p[i] % l1.v;
    }
    sort(a + 1, a + n + 1);
    l1.t = (a[n / 2] + a[n / 2 + 1]) / 2;
    sort(p + 1, p + n + 1, cmp);

    double l = 0, r = MPI - EPS;
    for (int _ = 0; _ < TMAX; _++) {
        double m = (l + r) / 2;
        int ret = test(m + ANGLE);
        if (ret == 0)
            l = r = m;
        else if (ret > 0)
            l = m;
        else
            r = m;
    }

    output(l1, S);
    output(l1, -S);
    puts("");
    output(l2, S);
    output(l2, -S);
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
