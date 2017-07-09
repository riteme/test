#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define MMAX 3000
#define INF 100000000000000LL

typedef long long i64;

static int n, m;
static i64 A[NMAX + 10];
static i64 f[MMAX + 10][MMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", A + i);
        A[i] += A[i - 1];
    }
}

struct Point {
    Point(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    i64 operator%(const Point &b) const {
        return x * b.y - y * b.x;
    }
};

inline i64 p(i64 x) {
    return x * x;
}

#define LAST(q) q[q.size() - 1]
#define LSEC(q) q[q.size() - 2]

int main() {
    freopen("moveproblem.in", "r", stdin);
    freopen("moveproblem.out", "w", stdout);
    initialize();

    i64 ans = 0;
    if (n > 3000) {
        int r = n % m;
        int d = n / m;
        int cnt = 0;

        while (cnt < n) {
            i64 s = d * A[1];
            cnt += d;
            if (r) {
                r--;
                cnt++;
                s += A[1];
            }
            ans += s * s;
        }
    } else {
        for (int i = 1; i <= n; i++) {
            f[0][i] = INF;
        }

        for (int j = 1; j <= m; j++) {
            deque<Point> q;
            for (int i = 0; i <= n; i++) {
                while (q.size() > 1 &&
                       q[0].y - q[1].y >= 2 * A[i] * (q[0].x - q[1].x))
                    q.pop_front();

                f[j][i] = min(INF, q[0].y + p(A[i]) - 2 * A[i] * q[0].x);

                Point np(A[i], f[j - 1][i] + p(A[i]));
                while (q.size() > 1 &&
                       (np - LSEC(q)) % (LAST(q) - LSEC(q)) >= 0)
                    q.pop_back();
                q.push_back(np);
            }
        }

        ans = f[m][n];
    }

    printf("%lld\n", m * ans - p(A[n]));

    return 0;
}
