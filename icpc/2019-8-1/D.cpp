#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

struct Point {
    Point() : x(0), y(0) {}
    Point(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    Point operator+(const Point &z) const {
        return {x + z.x, y + z.y};
    }

    Point operator-(const Point &z) const {
        return {x - z.x, y - z.y};
    }
};

inline i64 dot(const Point &u, const Point &v) {
    return u.x * v.x + u.y * v.y;
}

inline i64 cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}

inline i64 len2(const Point &u) {
    return u.x * u.x + u.y * u.y;
}

#define NMAX 200000
#define LOG 62

static int X[NMAX + 10], sx, cx, lx;
static int Y[NMAX + 10], sy, cy, ly;
static int mx[LOG][NMAX + 10], mi[LOG][NMAX + 10];
static Point P[NMAX * 2 + 10];

inline int gx(int s, i64 l) {
    return s + l >= cx ? sx + (s + l - cx) % lx : s + l;
}

inline int gy(int s, i64 l) {
    return s + l >= cy ? sy + (s + l - cy) % ly : s + l;
}

int main() {
    i64 ax, ay, bx, by, px, py, n;
    scanf("%d%d%lld%lld%lld%lld%lld%lld%lld", X, Y, &ax, &ay, &bx, &by, &px, &py, &n);

    unordered_map<int, int> S;
    S[X[0]] = 0;
    for (int i = 1; ; i++) {
        X[i] = (ax * X[i - 1] + bx) % px;
        auto it = S.find(X[i]);
        if (it != S.end()) {
            sx = it->second;
            cx = i;
            lx = cx - sx;
            break;
        } else S[X[i]] = i;
    }
    S.clear();
    S[Y[0]] = 0;
    for (int i = 1; ; i++) {
        Y[i] = (ay * Y[i - 1] + by) % py;
        auto it = S.find(Y[i]);
        if (it != S.end()) {
            sy = it->second;
            cy = i;
            ly = cy - sy;
            break;
        } else S[Y[i]] = i;
    }

    for (int i = 0; i < cy; i++) mx[0][i] = mi[0][i] = Y[i];
    for (int j = 1; j < LOG && (1LL << (j - 1)) * lx <= n; j++) for (int i = 0; i < cy; i++) {
        mx[j][i] = max(mx[j - 1][i], mx[j - 1][gy(i, (1LL << (j - 1)) * lx)]);
        mi[j][i] = min(mi[j - 1][i], mi[j - 1][gy(i, (1LL << (j - 1)) * lx)]);
    }

    int m = 0;
    for (int i = 0; i < sx && i < n; i++) P[m++] = {X[i], Y[gy(0, i)]};
    for (int i = sx; i < cx && i < n; i++) {
        i64 r = (n - i + lx - 1) / lx, p = gy(0, i);
        int ymin = INT_MAX, ymax = INT_MIN;
        for (int j = 0; j < LOG; j++) if ((r >> j) & 1) {
            ymin = min(ymin, mi[j][p]);
            ymax = max(ymax, mx[j][p]);
            p = gy(p, (1LL << j) * lx);
        }
        P[m++] = {X[i], ymin};
        P[m++] = {X[i], ymax};
    }

    Point O(INT_MAX, INT_MAX);
    for (int i = 0; i < m; i++)
        if (P[i].y < O.y || (P[i].y == O.y && P[i].x < O.x)) O = P[i];
    sort(P, P + m, [O](const Point &u, const Point &v) {
        i64 p = cross(u - O, v - O);
        return p > 0 || (p == 0 && len2(u - O) < len2(v - O));
    });
    vector<Point> stk;
    for (int i = 0; i < m; i++) {
        while (stk.size() > 1 &&
               cross(P[i] - stk[stk.size() - 2], stk[stk.size() - 1] - stk[stk.size() - 2]) >= 0)
            stk.pop_back();
        stk.push_back(P[i]);
    }

    i64 ans = 0;
    for (int i = 0; i < stk.size() - 1; i++) ans += cross(stk[i], stk[i + 1]);
    ans += cross(stk[stk.size() - 1], stk[0]);
    printf("%lld\n", abs(ans));

    return 0;
}
