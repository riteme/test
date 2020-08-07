#include <cmath>
#include <cstdio>
#include <cstring>

#include <tuple>
#include <algorithm>

using namespace std;

using i64 = long long;
using d8 = long double;

constexpr i64 NMAX = 100000;
constexpr d8 EPS = 1e-7;

bool eq(d8 x, d8 y) {
    return fabs(x - y) < EPS;
}

struct vec {
    i64 x, y;

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    vec operator*(i64 k) const {
        return {x * k, y * k};
    }

    i64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

int n;
vec p[NMAX + 10], v[NMAX + 10];
int id[NMAX + 10];
d8 yp[NMAX + 10];

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld%lld", &p[i].x, &p[i].y, &v[i].x, &v[i].y);
        if (p[i].x > v[i].x || (p[i].x == v[i].x && p[i].y > v[i].y))
            swap(p[i], v[i]);
        v[i] = v[i] - p[i];
        id[i] = i;
    }

    sort(id + 1, id + n + 1, [](int i, int j) {
        i64 c = v[i] % v[j];
        return c < 0 || (c == 0 && v[i].x < v[j].x);
    });

    i64 ans = 0;
    for (int i = 1, j; i <= n; i = j) {
        j = i + 1;
        while (j <= n && v[id[i]] % v[id[j]] == 0) {
            j++;
        }

        i64 cnt = j - i;
        ans += cnt * (n - cnt);
        for (int k = i; k < j; k++) {
            if (v[id[k]].x != 0)
                yp[k - i] = d8(v[id[k]] % p[id[k]]) / v[id[k]].x;
            else
                yp[k - i] = d8(v[id[k]] % p[id[k]]) / v[id[k]].y;
        }
        sort(yp, yp + cnt);

        for (int p = 0, q; p < cnt; p = q) {
            q = p + 1;
            while (q < cnt && eq(yp[p], yp[q])) {
                q++;
            }

            i64 c = q - p;
            ans += c * (c - 1);
        }
    }

    printf("%lld\n", ans / 2);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}