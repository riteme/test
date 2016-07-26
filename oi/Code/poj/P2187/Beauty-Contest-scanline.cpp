// #define NDEBUG

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif  // IFNDEF NDEBUG

#define NMAX 50000
#define EPSILON 0.00000001

inline bool almost_equal(const double a, const double b) {
    return fabs(a - b) < EPSILON;
}

struct Vector2 {
    Vector2() : x(0), y(0) {}
    Vector2(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    friend Vector2 operator+(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator*(const Vector2 &a, const double &b);
    friend double operator*(const Vector2 &a, const Vector2 &b);
};  // struct Point

Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator*(const Vector2 &a, const double &b) {
    return Vector2(a.x * b, a.y * b);
}

double operator*(const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - a.y * b.x;
}

inline double dot(const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

inline double square(const Vector2 &a) {
    return a.x * a.x + a.y * a.y;
}

// inline Vector2 distv(const Vector2 &a, const Vector2 &b, const Vector2 &c) {
//     Vector2 v = b - a;
//     Vector2 u = c - a;
//
//     if (almost_equal(dot(v, u), 0.0))
//         return u;
//
//     Vector2 v1 = v * (abs(1.0 / (dot(v, u) / sqrt(square(v)))));
//     return u - v1;
// }

inline double distl(const Vector2 &a, const Vector2 &b, const Vector2 &c) {
    Vector2 v = b - a;
    Vector2 u = c - a;

    double d = (u * v) / sqrt(square(v));
    return d * d;
}

static int n;
static Vector2 p[NMAX + 10];
static bool marked[NMAX + 10];
static int polgyoncnt = 0;
static Vector2 polgyon[NMAX + 10];

static Vector2 origin;

static bool cmp(const Vector2 &a, const Vector2 &b) {
    return (a - origin) * (b - origin) < 0;
}

static bool cmp2(const Vector2 &a, const Vector2 &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

inline bool below(const Vector2 &a, const Vector2 &b, const Vector2 &c) {
    return (b - a) * (c - a) < 0;
}

#define LAST(x) (x[x.size() - 1])
#define PLAST(x) (x[x.size() - 2])

static void scanline() {
    sort(p + 1, p + n + 1, cmp2);
    int left = 1, right = n;
    marked[left] = true;

    vector<int> up;
    vector<int> down;
    up.push_back(left);
    down.push_back(left);
    for (int i = 2; i <= n; i++) {
        if (below(p[left], p[right], p[i])) {
            while (down.size() >= 2 &&
                   ((p[i] - p[PLAST(down)]) * (p[LAST(down)] - p[PLAST(down)]) >
                        0 ||
                    (almost_equal((p[i] - p[PLAST(down)]) *
                                      (p[LAST(down)] - p[PLAST(down)]),
                                  0.0) &&
                     square(p[i] - p[PLAST(down)]) >
                         square(p[LAST(down)] - p[PLAST(down)])))) {
                int u = LAST(down);
                marked[u] = false;
                down.pop_back();
            }  // while

            down.push_back(i);
            marked[i] = true;
        } else {
            while (up.size() >= 2 &&
                   ((p[i] - p[PLAST(up)]) * (p[LAST(up)] - p[PLAST(up)]) < 0 ||
                    (almost_equal(
                         (p[i] - p[PLAST(up)]) * (p[LAST(up)] - p[PLAST(up)]),
                         0.0) &&
                     square(p[i] - p[PLAST(up)]) >
                         square(p[LAST(up)] - p[PLAST(up)])))) {
                int u = LAST(up);
                marked[u] = false;
                up.pop_back();
            }  // while

            up.push_back(i);
            marked[i] = true;
        }
    }  // for
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }  // for
}

inline int id(int x) {
    if (x > polgyoncnt)
        return x - polgyoncnt;
    return x;
}

int main() {
    initialize();

    scanline();

    for (int i = 1; i <= n; i++)
        if (marked[i])
            polgyon[++polgyoncnt] = p[i];

    // for (int i = 1; i <= polgyoncnt; i++) {
    //     printf("(%lf, %lf)\n", polgyon[i].x, polgyon[i].y);
    // }  // for

    if (polgyoncnt < 3) {  // WTF
        printf("%d\n", int(square(polgyon[1] - polgyon[2]) + 0.5));
        return 0;
    }

    origin = polgyon[1];
    sort(polgyon + 2, polgyon + polgyoncnt + 1, cmp);

    int top = 0, down = 0;
    for (int i = 1; i <= polgyoncnt; i++) {
        if (top == 0 || polgyon[top].y < polgyon[i].y ||
            (polgyon[top].y == polgyon[i].y && polgyon[top].x > polgyon[i].x))
            top = i;
        if (down == 0 || polgyon[down].y > polgyon[i].y ||
            (polgyon[down].y == polgyon[i].y && polgyon[down].x > polgyon[i].x))
            down = i;
    }  // for

    int i1 = id(top), i2 = id(top + 1);
    int j = id(down);
    double maxdist = 0.0;
    do {
        double dist = distl(polgyon[i1], polgyon[i2], polgyon[j]);
        while (distl(polgyon[i1], polgyon[i2], polgyon[id(j + 1)]) > dist) {
            j = id(j + 1);
            dist = distl(polgyon[i1], polgyon[i2], polgyon[j]);
        }

        // printf("(%lf, %lf) - (%lf, %lf) : (%lf, %lf)\n",
        //        polgyon[i1].x,
        //        polgyon[i1].y,
        //        polgyon[i2].x,
        //        polgyon[i2].y,
        //        polgyon[j].x,
        //        polgyon[j].y);

        Vector2 v = polgyon[i2] - polgyon[i1];
        while (true) {
            maxdist = max(maxdist, square(polgyon[j] - polgyon[i1]));
            maxdist = max(maxdist, square(polgyon[j] - polgyon[i2]));

            if (almost_equal(0.0, v * (polgyon[id(j + 1)] - polgyon[j])))
                j = id(j + 1);
            else
                break;
        }

        i1 = i2;
        i2 = id(i2 + 1);
    } while (i1 != top);

    printf("%d\n", int(maxdist + 0.5));

    return 0;
}  // function main
