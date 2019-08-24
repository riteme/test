// #define NDEBUG

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <deque>

using namespace std;

#define NMAX 1000000

#define SEC(q) q[q.size() - 2]

typedef long long i64;

struct Point {
    Point() : x(0), y(0), dir(0), next(NULL) {}
    Point(i64 _x, i64 _y, int _d = 0) : x(_x), y(_y), dir(_d), next(NULL) {}

    i64 x, y;
    int dir;
    Point *next;

    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    Point operator*(const i64 r) const {
        return Point(x * r, y * r);
    }

    i64 operator*(const Point &b) const {
        return x * b.y - y * b.x;
    }

    bool operator<(const Point &b) const {
        return x < b.x;
    }

    bool operator==(const Point &b) const {
        return x == b.x && y == b.y;
    }
};  // struct Point

typedef deque<Point *> Deque;

static int n, sx, sy, head, tail;
static Point P[NMAX + 10];
static Deque q[2];

inline double polar(const i64 x, const i64 y) {
    double a = atan2(y, x);
    return a < 0.0 ? M_PI - a : a;
}

inline double dist(const double a, const double b) {
    return a < b ? b - a : M_PI - a + b;
}

inline bool in_range(const double l, const double r, const double a) {
    return dist(l, a) <= dist(l, r);
}

void initialize() {
    scanf("%d%d%d", &n, &sx, &sy);

    double a;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lf", &P[i].x, &P[i].y, &a);
        double l = polar(-P[i].x, -P[i].y);
        double r = polar(sx - P[i].x, sy - P[i].y);
        P[i].dir = in_range(l, r, a) ? 0 : 1;
    }  // for

    P[++n] = Point(0, 0);
    P[++n] = Point(sx, sy);
    sort(P + 1, P + n + 1);

    for (int i = 1; i <= n; i++) {
        if (P[i] == Point(0, 0))
            head = i;
        if (P[i] == Point(sx, sy))
            tail = i;
    }  // for
}

int main() {
    freopen("data.in", "r", stdin);
    initialize();

    q[1].push_back(P + head);
    for (int i = head; i <= tail; i++) {
        Point &p = P[i];
        Deque &q1 = q[p.dir];
        Deque &q2 = q[p.dir ^ 1];

        if (q2.size() > 1 &&
            (*q2[1] - *q2[0]) * (p - *q2[0]) * (p.dir ? -1 : 1) >= 0) {
            while (q2.size() > 1 &&
                   (*q2[1] - *q2[0]) * (p - *q2[0]) * (p.dir ? -1 : 1) >= 0) {
                q2.pop_front();
            }  // while

            if (!q2.empty())
                q2[0]->next = &p;
        } else {
            while (q1.size() > 1 &&
                   (*q1.back() - *SEC(q1)) * (p - *SEC(q1)) *
                           (p.dir ? -1 : 1) >=
                       0) {
                q1.pop_back();
            }  // while

            if (!q1.empty())
                q1.back()->next = &p;
        }

        q1.push_back(&p);
    }  // for

    Point *u = P + head;
    printf("(0, 0)");
    do {
        u = u->next;
        printf(" -> (%lld, %lld)", u->x, u->y);
    } while (u != P + tail);  // do ... while
    printf("\n");

    return 0;
}  // function main
