#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using d8 = long double;

constexpr int NMAX = 1000000;
constexpr d8 EPS = 1e-7;

bool eq(d8 x, d8 y) {
    return fabsl(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0) {}
    vec(d8 _x, d8 _y) : x(_x), y(_y) {}

    d8 x, y;

    int id() const {
        if (x >= 0 && y >= 0)
            return 0;
        if (x <= 0 && y >= 0)
            return 1;
        if (x <= 0 && y <= 0)
            return 2;
        return 3;
    }

    d8 len2() const {
        return x * x + y * y;
    }

    d8 len() const {
        return hypotl(x, y);
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-() const {
        return {-x, -y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    vec operator*(d8 k) const {
        return {x * k, y * k};
    }

    vec operator/(d8 k) const {
        return {x / k, y / k};
    }

    d8 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    d8 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

struct shit {
    int A, d;
    vec p;
    bool rev;
};

int n, K;
vec C;
shit s[NMAX + 10];

void enumerate() {
    int a[K + 1];
    a[0] = 0;
    for (int A = 0; A < (1 << K); A++) {
        for (int i = 1; i <= K; i++) {
            int b = (A >> (i - 1)) & 1;
            a[i] = a[i - 1] + (b ? +1 : -1);
        }

        bool ok = true;
        for (int i = 1; i <= K; i++) {
            ok &= a[i] >= 0;
        }

        if (!ok)
            continue;

        vec p;
        d8 m = 0;
        for (int i = 1; i <= K; i++) {
            int z = min(a[i - 1], a[i]);
            m += z + 0.5L;
            p = p + vec(i - 0.5L, z / 2.0L) * z;

            if (a[i] > a[i - 1])
                p = p + (vec(i - 1, z) + vec(i, z) + vec(i, z + 1)) / 6.0L;
            else
                p = p + (vec(i - 1, z) + vec(i - 1, z + 1) + vec(i, z)) / 6.0L;
        }

        p = p / m;
        s[n++] = {A, a[K], (p - C) * m, false};
        p = {2 * K - p.x, p.y};
        s[n++] = {A, a[K], (C - p) * m, true};
    }
}

void output(const shit &p) {
    char a[K];
    for (int i = 0; i < K; i++) {
        a[i] = (p.A >> i) & 1;
    }
    if (p.rev)
        reverse(a, a + K);
    for (int i = 0; i < K; i++) {
        putchar((a[i] ^ p.rev) ? '(' : ')');
    }
}

int main() {
    scanf("%d%Lf%Lf", &K, &C.x, &C.y);
    K /= 2;

    enumerate();
    sort(s, s + n, [](const shit &_u, const shit &_v) {
        const vec &u = _u.p;
        const vec &v = _v.p;

        if (u.id() != v.id())
            return u.id() < v.id();

        d8 c = u % v;
        if (eq(c, 0))
            return u.len2() < v.len2();
        return c > 0;
    });

    for (int i = 0; i < n; i++) {
        for (int j = (i + 1) % n; true; j = (j + 1) % n) {
            if (!eq((s[i].p - s[j].p).len(), 0))
                break;
            if (s[i].rev == s[j].rev || s[i].d != s[j].d)
                continue;

            if (s[i].rev) {
                output(s[j]);
                output(s[i]);
            } else {
                output(s[i]);
                output(s[j]);
            }

            puts("");
            return 0;
        }
    }

    abort();
}