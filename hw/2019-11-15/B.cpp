// FSX sb

#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;
typedef long double ld;

#define NMAX 100000

struct vec {
    int i;
    i64 x, y;

    ld len() {
        return hypotl(x, y);
    }

    i64 len2() {
        return x * x + y * y;
    }
};

i64 cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

i64 dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

int region(const vec &u) {
    if (u.x >= 0 && u.y >= 0) return 1;
    if (u.x <= 0 && u.y >= 0) return 2;
    if (u.x <= 0 && u.y <= 0) return 3;
    return 4;
}

static int n;
static vec v[NMAX + 10];

bool cmp(i64 q1, i64 p1, i64 q2, i64 p2) {
    i64 k1 = q1 / p1;
    i64 k2 = q2 / p2;
    if (k1 != k2) return k1 < k2;
    i64 r1 = q1 % p1;
    i64 r2 = q2 % p2;
    for (int i = 0; i < 200 && (r1 || r2); i++) {
        k1 = r1 * 2 / p1;
        k2 = r2 * 2 / p2;
        r1 = r1 * 2 % p1;
        r2 = r2 * 2 % p2;
        if (k1 != k2) return k1 < k2;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        v[i].i = i;
        scanf("%lld%lld", &v[i].x, &v[i].y);
    }
    sort(v + 1, v + n + 1, [](const vec &u, const vec &v) {
        int i = region(u);
        int j = region(v);
        return i > j || (i == j && cross(u, v) < 0);
    });
    v[n + 1] = v[1];
    vec p = v[1], q = v[2];
    for (int i = 2; i <= n; i++) {
        vec x = v[i], y = v[i + 1];
        if (dot(x, y) == 0 && dot(p, q) == 0) continue;
        if (dot(x, y) <= 0 && dot(p, q) > 0) continue;
        if (dot(x, y) >= 0 && dot(p, q) < 0) {
            p = x;
            q = y;
        } else {
            i64 p1 = x.len2() * y.len2();
            i64 p2 = p.len2() * q.len2();
            i64 q1 = dot(x, y) * dot(x, y);
            i64 q2 = dot(p, q) * dot(p, q);
            if ((dot(x, y) < 0 && cmp(q1, p1, q2, p2)) ||
                (dot(x, y) > 0 && cmp(q2, p2, q1, p1))) {
                p = x;
                q = y;
            }
        }
    }
    printf("%d %d\n", p.i, q.i);
    return 0;
}
