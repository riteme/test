//#define NDEBUG
#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

struct Point {
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    Point operator+(const Point &z) const {
        return Point(x + z.x, y + z.y);
    }

    Point operator-(const Point &z) const {
        return Point(x - z.x, y - z.y);
    }

    Point operator/(int k) const {
        return Point(x / k, y / k);
    }
};

inline int dot(const Point &u, const Point &v) {
    return u.x * v.x + u.y * v.y;
}

inline int cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}

static int n;
static Point p[NMAX + 10];

inline int nxt(int i) {
    return i < n ? i + 1 : 1;
}

inline int pre(int i) {
    return i > 1 ? i - 1 : n;
}

inline bool check(int s1, int s2, int u, int v) {
    int cnt = 0, i = s1, j = s2;
    Point d = p[u] - p[v], m = (p[u] + p[v]) / 2;
    do {
        if (i != j && dot(d, p[i] - m) == 0 && dot(d, p[j] - m) == 0) return false;
        if (dot(p[i] - p[j], d) < 0) return false;
        cnt += cross(d, p[i] - p[j]) || dot(d, (p[i] + p[j]) / 2 - m);
        j = nxt(j);
        i = pre(i);
        if (i == j || nxt(j) == i || nxt(i) == j) break;
    } while (cnt <= 1);
    if (i != j && dot(d, p[i] - m) == 0 && dot(d, p[j] - m) == 0) return false;
    if (dot(p[i] - p[j], d) < 0) return false;
    cnt += cross(d, p[i] - p[j]) || dot(d, (p[i] + p[j]) / 2 - m);
    //fprintf(stderr, "%d, %d, %d, %d, %d\n", s1, s2, u, v, cnt);
    return cnt <= 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &p[i].x, &p[i].y);
            p[i].x <<= 1;
            p[i].y <<= 1;
        }
        if (n <= 4) puts("Y");
        else {
            bool ok = false;
            for (int i = 1; !ok && i <= n; i++) {
                ok |= check(i, i, pre(i), nxt(i));
                if (!ok) ok |= check(i, i, pre(pre(i)), nxt(nxt(i)));
                if (!ok) ok |= check(i, nxt(i), i, nxt(i));
                if (!ok) ok |= check(i, nxt(i), pre(i), nxt(nxt(i)));
                //if (ok) fprintf(stderr, "%d\n", i);
            }
            puts(ok ? "Y" : "N");
        }
    }
    return 0;
}
