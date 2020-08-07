#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 3000

typedef long long i64;

struct vec {
    vec() : x(0), y(0) {}
    vec(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    int idx() const {
        if (x >= 0 && y >= 0)
            return 0;
        if (x <= 0 && y >= 0)
            return 1;
        if (x <= 0 && y <= 0)
            return 2;
        return 3;
    }

    i64 len2() const {
        return x * x + y * y;
    }

    bool operator<(const vec &z) const {
        int i = idx(), j = z.idx();
        if (i != j)
            return i < j;

        i64 c = (*this) % z;
        return c ? c > 0 : len2() < z.len2();
    }

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    vec operator*(i64 k) const {
        return vec(x * k, y * k);
    }

    i64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    i64 operator%(const vec &z) const {
        return x * z.y - z.x * y;
    }
};

int n;
int cnt[3];
vec P[3][NMAX + 10];

void initialize() {
    scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) {
        i64 x, y, c;
        scanf("%lld%lld%lld", &x, &y, &c);
        P[c][cnt[c]++] = vec(x, y);
    }
}

vec co;

bool ccmp(const vec &u, const vec &v) {
    return (u - co) < (v - co);
}

void convex() {
    int o = 0;
    for (int i = 1; i < cnt[0]; i++)
    if (P[0][i].y < P[0][o].y || (P[0][i].y == P[0][o].y && P[0][i].x > P[0][o].x))
        o = i;

    swap(P[0][0], P[0][o]);
    co = P[0][0];
    sort(P[0], P[0] + cnt[0], ccmp);

    vector<vec> stk;
    for (int i = 0; i < cnt[0]; i++) {
        vec x = P[0][i];
        while (stk.size() > 1) {
            vec v = stk[stk.size() - 1];
            vec u = stk[stk.size() - 2];
            if ((x - u) % (v - u) >= 0)
                stk.pop_back();
            else break;
        }
        stk.push_back(x);
    }

    cnt[0] = stk.size();
    for (int i = 0; i < cnt[0]; i++) {
        P[0][i] = stk[i];
    }
}

struct tangent {
    tangent() {}
    tangent(int _i, int _j)
        : i(_i), j(_j) {}

    int i, j;

    bool operator<(const tangent &z) const {
        vec p = P[1][j] - P[1][i];
        vec zp = P[1][z.j] - P[1][z.i];
        return p < zp;
    }
};

int m;
tangent tg[NMAX * NMAX + 10];

int nxtp(int i) {
    return i + 1 < cnt[0] ? i + 1 : 0;
}

int prep(int i) {
    return i ? i - 1 : cnt[0] - 1;
}

void _main() {
    initialize();
    convex();

    memcpy(P[1] + cnt[1], P[2], sizeof(vec) * cnt[2]);

    m = 0;
    for (int i = 0; i < cnt[1]; i++)
    for (int j = 0; j < cnt[2]; j++) {
        tg[m++] = tangent(i, cnt[1] + j);
        tg[m++] = tangent(cnt[1] + j, i);
    }
    sort(tg, tg + m);

    int j = 0;
    i64 ans = 0;
    for (int i = 0; i < m; i++) {
        vec p = P[1][tg[i].j] - P[1][tg[i].i];
        while (true) {
            vec u = P[0][j] - P[0][prep(j)];
            vec v = P[0][nxtp(j)] - P[0][j];
            if (u % p >= 0 && p % v >= 0)
                break;
            else
                j = nxtp(j);
        }

        ans = max(ans, abs(p % (P[0][j] - P[1][tg[i].i])));
    }

    printf("%lld", ans >> 1);
    puts((ans & 1) ? ".5" : ".0");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}