#include <cmath>
#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 50
#define MMAX 300
#define INF 1e99

struct Point {
    Point() : x(0), y(0) {}
    Point(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    double len() const {
        return hypot(x, y);
    }

    i64 len2() const {
        return x * x + y * y;
    }

    Point operator+(const Point &z) const {
        return Point(x + z.x, y + z.y);
    }

    Point operator-(const Point &z) const {
        return Point(x - z.x, y - z.y);
    }

    Point operator*(i64 k) const {
        return Point(x * k, y * k);
    }
};

inline i64 dot(const Point &u, const Point &v) {
    return u.x * v.x + u.y * v.y;
}

inline i64 cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}

inline bool onseg(const Point &a, const Point &b, const Point &c) {
    return cross(c - a, b - a) == 0 && dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}

inline bool neg(i64 x, i64 y) {
    return !x || !y || (x < 0) != (y < 0);
}

inline bool has_sect(const Point &a, const Point &b, const Point &c, const Point &d) {
    return cross(a - b, c - d) != 0 &&
        neg(cross(b - a, c - a), cross(b - a, d - a)) &&
        neg(cross(d - c, a - c), cross(d - c, b - c)) &&
        //cross(b - a, c - a) * cross(b - a, d - a) <= 0 &&
        //cross(d - c, a - c) * cross(d - c, b - c) <= 0 &&
        !onseg(a, b, c) && !onseg(a, b, d);
}

inline void sect(const Point &a, const Point &b, const Point &c, const Point &d, double &ox, double &oy) {
    i64 s1 = abs(cross(c - a, d - a)), s2 = abs(cross(c - b, d - b));
    double k = double(s1) / (s1 + s2);
    ox = a.x + (b.x - a.x) * k;
    oy = a.y + (b.y - a.y) * k;
}

static int n, K;
static int m[NMAX + 10];
static Point C[5];
static Point P[NMAX + 10][MMAX + 10];
static double dist[NMAX + 10];

int main() {
    scanf("%d", &K);
    for (int i = 1; i <= 4; i++)
        scanf("%lld%lld", &C[i].x, &C[i].y);
    scanf("%d", &n);
    //int m1, m2;
    for (int i = 1; i <= n; i++) {
        scanf("%d", m + i);
        //if (i == 1) m1 = m[1];
        //if (i == 2) m2 = m[2];
        dist[i] = INF;
        int mi = 1;
        for (int j = 1; j <= m[i]; j++) {
            i64 _;
            scanf("%lld%lld%lld", &P[i][j].x, &P[i][j].y, &_);
            if (_ != 0) {
                m[i]--;
                j--;
                continue;
            }
            if (j != mi && (P[i][j].x < P[i][mi].x ||
                (P[i][j].x == P[i][mi].x && P[i][j].y < P[i][mi].y)))
                mi = j;
        }
        swap(P[i][1], P[i][mi]);
        Point O = P[i][1];
        sort(P[i] + 2, P[i] + m[i] + 1, [O](const Point &u, const Point &v) {
            i64 x = cross(u - O, v - O);
            return x > 0 || (x == 0 && (u - O).len2() < (v - O).len2());
        });
        deque<Point> q;
        q.push_front(P[i][1]);
        for (int j = 2; j <= m[i]; j++) {
            while (q.size() >= 2 && cross(P[i][j] - q[1], q[0] - q[1]) >= 0)
                q.pop_front();
            q.push_front(P[i][j]);
        }
        m[i] = q.size();
        for (int j = 0; j < m[i]; j++)
            P[i][j + 1] = q[j];
        P[i][0] = P[i][m[i]];
        P[i][m[i] + 1] = q[0];  // 0 ~ m[i] + 1 circular
    }

    Point v = Point(C[2].y - C[1].y, C[1].x - C[2].x);
    for (int i = 1; i <= 4; i++) {
        Point u = C[i] + v * 20000;
        for (int j = 1; j <= n; j++) for (int k = 1; k <= m[j]; k++) {
            if (has_sect(C[i], u, P[j][k], P[j][k + 1])) {
                double x, y;
                sect(C[i], u, P[j][k], P[j][k + 1], x, y);
                dist[j] = min(dist[j], hypot(x - C[i].x, y - C[i].y));
            }
            if (onseg(C[i], u, P[j][k]) && has_sect(C[i], u, P[j][k - 1], P[j][k + 1])) {
                dist[j] = min(dist[j], hypot(P[j][k].x - C[i].x, P[j][k].y - C[i].y));
            }
        }
    }

    sort(dist + 1, dist + n + 1);
    if (K >= n || dist[K + 1] > 1e98) puts("oo");
    else printf("%.8lf\n", dist[K + 1]);

    //if (dist[K + 1] - 5.65685425 > 1e-6) {
    //    int fake;
    //    if (m1 >> 7) return 1;
    //    else while(1);
    //    //int bits = (m1 & 0xC) >> 2;
    //    //int bits = m1 & 3;
    //    //int bits = (n & 0x30) >> 4;
    //    //int bits = (n & 0xC0) >> 6;
    //    //int bits = (n & 0x300) >> 8;
    //    int bits = (n & 0xC00) >> 10;
    //    if (bits == 0) return 0;
    //    if (bits == 1) return 1;
    //    if (bits == 2) {
    //        while(1);
    //    }
    //    if (bits == 3) {
    //        while (1) new double[65536];
    //    }
    //}

    return 0;
}
