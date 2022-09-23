#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using f64 = double;

constexpr f64 EPS = 1e-8;

bool eq(f64 x, f64 y) {
    return abs(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0) {}
    vec(f64 _x, f64 _y) : x(_x), y(_y) {}

    f64 x, y;

    vec operator-() const {
        return vec(-x, -y);
    }

    vec operator+(vec z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(vec z) const {
        return vec(x - z.x, y - z.y);
    }

    f64 operator*(vec z) const {
        return x * z.x + y * z.y;
    }

    f64 operator%(vec z) const {
        return x * z.y - y * z.x;
    }

    f64 len() const {
        return hypot(x, y);
    }

    vec operator/(f64 k) const {
        return vec(x / k, y / k);
    }

    vec operator*(f64 k) const {
        return vec(x * k, y * k);
    }

    vec cw() const {
        return vec(y, -x);
    }
};

struct seg {
    vec u, v;
    seg() {}
    seg(vec _u, vec _v) : u(_u), v(_v) {}
    f64 len() const {
        return (u - v).len();
    }
};

struct cir {
    vec p;
    f64 r;
};

cir C[3];

f64 sqrt_s(f64 x) {
    return sqrt(max(x, 0.0));
}

void c2tan1(const cir &c1, const cir &c2, seg &t1, seg &t2) {
    vec v = c1.p - c2.p;
    f64 dr = abs(c1.r - c2.r), d = v.len();
    f64 l = sqrt_s(d * d - dr * dr);
    f64 h1 = l * c1.r / d, s1 = dr * c1.r / d;
    f64 h2 = l * c2.r / d, s2 = dr * c2.r / d;
    v = (c1.r > c2.r ? -v : v) / d;
    vec u = v.cw(), p1 = c1.p + v * s1, p2 = c2.p + v * s2;
    t1 = seg(p1 + u * h1, p2 + u * h2);
    if (eq((t1.v - c1.p).len(), c1.r))
        swap(t1.u, t1.v);
    t2 = seg(p1 - u * h1, p2 - u * h2);
    if (eq((t2.v - c1.p).len(), c1.r))
        swap(t2.u, t2.v);
}

f64 p2arc(const cir &c, vec u, vec v) {
    if (eq(u.x, v.x) && eq(u.y, v.y))
        return 0;
    u = u - c.p;
    v = v - c.p;
    f64 d = u * v, cr = u % v;
    f64 t = acos(max(-1.0, min(1.0, d / c.r / c.r)));
    return cr > 0 ? t : 2 * M_PI - t;
}

struct tvec {
    int i;
    vec u;
    bool used;
};

vector<tvec> P;
f64 ans;

bool ok(vec u, vec v) {
    for (auto &z : P) {
        if ((v - u) % (z.u - u) <= -EPS)
            return false;
    }
    return true;
}

bool eq(vec u, vec v) {
    return eq(u.x, v.x) && eq(u.y, v.y);
}

bool test(tvec a, tvec b) {
    vec u = a.u, v = b.u;
    if (ok(u, v)) {
        int i = -1;
        if (a.i == b.i) {
            i = a.i;
        } else {
            for (int j = 0; j < (int)P.size(); j++)
            for (int k = 0; k < (int)P.size(); k++)
            if (eq(P[j].u, u) && eq(P[k].u, v) && P[j].i == P[k].i) {
                i = P[j].i;
                goto out;
            }
out: ;
        }

        if (i != -1) {
            f64 r = C[i].r;
            f64 t = p2arc(C[i], u, v);
            f64 fu = C[i].p % u;
            f64 fv = C[i].p % v;
            f64 delta = r * r * t + fv - fu;
            ans += delta;
            //printf("C (%.2lf,%.2lf)→(%.2lf,%.2lf) %+.3lf t=%.3lf\n", u.x, u.y, v.x, v.y, delta, t);
        } else {
            f64 delta = u % v;
            //printf("T (%.2lf,%.2lf)→(%.2lf,%.2lf) %+.3lf\n", u.x, u.y, v.x, v.y, delta);
            ans += delta;
        }
        return true;
    }
    return false;
}

bool covered(int i) {
    for (int j = 0; j < 3; j++)
    if (i != j) {
        f64 d = (C[i].p - C[j].p).len();
        if (d < abs(C[i].r - C[j].r) + EPS)
            return true;
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 3; i++) {
            scanf("%lf%lf%lf", &C[i].p.x, &C[i].p.y, &C[i].r);
        }

        P.clear();

        for (int i = 0; i < 3; i++)
        if (!covered(i))
        for (int j = i + 1; j < 3; j++)
        if (!covered(j)) {
            f64 d = (C[i].p - C[j].p).len();
            if (d < abs(C[i].r - C[j].r) + EPS)
                continue;

            seg t1, t2;
            c2tan1(C[i], C[j], t1, t2);
            P.push_back({i, t1.u, false});
            P.push_back({i, t2.u, false});
            P.push_back({j, t1.v, false});
            P.push_back({j, t2.v, false});
        }

        for (int i = 1; i < (int)P.size(); i++) {
            if (P[i].u.x < P[0].u.x ||
                (eq(P[i].u.x, P[0].u.x) && P[i].u.y < P[0].u.y))
                swap(P[i], P[0]);
        }

        ans = 0;

        if (P.empty()) {
            for (int i = 0; i < 3; i++) {
                ans = max(ans, C[i].r * C[i].r * M_PI);
            }
        } else {
            int i = 0;
            P[i].used = true;
            while (true) {
                if (i != 0 && test(P[i], P[0]))
                    break;
                for (int j = 0; j < (int)P.size(); j++) {
                    if (P[j].used)
                        continue;
                    if (test(P[i], P[j])) {
                        P[j].used = true;
                        i = j;
                        break;
                    }
                }
            }

            ans /= 2;
        }

        ans = abs(ans);
        printf("%.12lf\n", ans);
    }

    return 0;
}
