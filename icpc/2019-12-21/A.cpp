#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000

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

i64 cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}

int main() {
    int n;
    i64 mx = 0, mc = 0;
    scanf("%d", &n);

    vector<Point> q;
    i64 mi, SA = 0, SB = 0;
    for (int i = 1; i <= n; i++) {
        i64 v, x, y;
        scanf("%lld%lld%lld", &v, &x, &y);
        if (i == 1) {
            mx = mi = v;
            mc = 1;
        } else {
            if (v > mx) {
                Point p(SB, mx - mi);
                SA = v - mi;
                SB += mc;
                while (q.size() >= 2 &&
                    cross(p - q[q.size() - 1], p - q[q.size() - 2]) <= 0)
                    q.pop_back();
                q.push_back(p);

                mx = v;
                mc = 1;
            } else if (v == mx)
                mc++;
        }

#define F(p) (y * (SB - p.x) - x * (SA - p.y))
        i64 ans = 0;
        int l = 0, r = static_cast<int>(q.size()) - 2;
        while (l + 5 < r) {
            int m = (l + r) / 2;
            if (F(q[m]) < F(q[m + 1]))
                l = m;
            else
                r = m + 1;
        }

        for (int j = l; j <= r + 1; j++)
            ans = max(ans, F(q[j]));
        ans += mc * y;
        printf("%lld\n", ans);
    }
    return 0;
}
