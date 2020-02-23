#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100

typedef long long i64;

struct vec {
    i64 x, y;

    i64 len2() const {
        return x * x + y * y;
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
};

i64 dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

i64 cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

int n, q;
vec p[NMAX + 10];

bool onseg(const vec &a, const vec &b, const vec &u) {
    return cross(u - a, b - a) == 0 &&
        min(a.x, b.x) <= u.x && u.x <= max(a.x, b.x) &&
        min(a.y, b.y) <= u.y && u.y <= max(a.y, b.y);
}

bool in(const vec &a, const vec &b, const vec &c, const vec &u) {
    i64 s = abs(cross(b - a, c - a));
    return abs(cross(a - u, b - u)) + abs(cross(b - u, c - u)) + abs(cross(c - u, a - u)) == s;
}

bool locate(const deque<vec> &stk, const vec &o) {
    for (int i = 0; i < stk.size(); i++) {
        int j = i + 1 < stk.size() ? i + 1 : 0;
        if (onseg(stk[i], stk[j], o))
            return false;
    }

    for (int i = 0; i < stk.size(); i++) {
        int j = i + 1 < stk.size() ? i + 1 : 0;
        if (in(stk[0], stk[i], stk[j], o))
            return true;
    }

    return false;
}

void solve() {
    scanf("%d%d", &n, &q);
    int k = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        if (!k || (p[i].x < p[k].x || (p[i].x == p[k].x && p[i].y < p[k].y)))
            k = i;
    }
    swap(p[1], p[k]);
    sort(p + 2, p + n + 1, [](const vec &_u, const vec &_v) {
        vec u = _u - p[1], v = _v - p[1];
        i64 cr = cross(u, v);
        if (cr == 0) return u.len2() < v.len2();
        return cr > 0;
    });

    deque<vec> stk;
    stk.push_front(p[1]);
    for (int i = 2; i <= n; i++) {
        while (stk.size() > 1 &&
            cross(stk[0] - stk[1], p[i] - stk[1]) <= 0)
            stk.pop_front();
        stk.push_front(p[i]);
    }

    printf("%lld %lld\n", stk[stk.size() - 1].x, stk[stk.size() - 1].y);
    for (int i = stk.size() - 2; i >= 0; i--)
        printf("%lld %lld\n", stk[i].x, stk[i].y);
    printf("%lld %lld\n", stk[stk.size() - 1].x, stk[stk.size() - 1].y);

    while (q--) {
        vec o;
        scanf("%lld%lld", &o.x, &o.y);
        printf("%lld %lld is %s!\n", o.x, o.y, locate(stk, o) ? "unsafe" : "safe");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case %d\n", i);
        solve();
        puts("");
    }
    return 0;
}