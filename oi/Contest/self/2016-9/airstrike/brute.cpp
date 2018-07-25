#include "user/interface.h"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 0.00000001;

inline bool almost_equal(const double a, const double b) {
    return fabs(a - b) < eps;
}

struct Point {
    double x, y;
    Point(double _x = 0.000, double _y = 0.000) : x(_x), y(_y) {}
    Point operator+(const struct Point _p) const {
        return Point(_p.x + x, _p.y + y);
    }
    Point operator-(const struct Point _p) const {
        return Point(x - _p.x, y - _p.y);
    }
};

inline int dcmp(double _x) {  // Judge float number
    if (fabs(_x) < eps)
        return 0;
    else if (_x < 0)
        return -1;
    else
        return 1;
}

double Dot(Point A, Point B) {  // point multiply
    return A.x * B.x + A.y * B.y;
}

double Length(Point A) {  // mo length
    return sqrt(Dot(A, A));
}

double Angle(Point A, Point B) {  // Calculate Vector Angle
    return acos(Dot(A, B)) / Length(A) / Length(B);
}

double Cross(Point A, Point B) {
    return (A.x * B.y - A.y * B.x);
}

Point ploy[1000010], JP;
bool IsPointOnSeg(Point P, Point A, Point B) {
    //    if((B.x==JP.x&&B.y==JP.y)||(A.x==JP.x&&JP.y==A.y)) return 1;
    return (dcmp(Cross(A - P, B - P)) == 0) && (dcmp(Dot(A - P, B - P)) <= 0);
}

int IsPointInPloy(int n) {
    int wn = 0;
    for (int i = 0; i < n; ++i) {
        if (IsPointOnSeg(JP, ploy[i], ploy[(i + 1) % n]))
            return -1;
        int k = dcmp(Cross(ploy[(i + 1) % n] - ploy[i], JP - ploy[i]));
        int d1 = dcmp(ploy[i].y - JP.y);
        int d2 = dcmp(ploy[(i + 1) % n].y - JP.y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            ++wn;
        if (k < 0 && d2 <= 0 && d1 > 0)
            --wn;
    }
    return wn != 0;
}

// int main() {
//     int n, m;
//     while (~scanf("%d", &n)) {
//         for (int i = 0; i < n; ++i) {
//             scanf("%lf%lf", &ploy[i].x, &ploy[i].y);
//         }
//         scanf("%d", &m);
//         while (m--) {
//             scanf("%lf%lf", &JP.x, &JP.y);
//             if (IsPointInPloy(n)) {
//                 puts("Yes");
//             } else
//                 puts("No");
//         }
//     }
//     return 0;
// }

static int cnt;

void initialize(const double *x, const double *y, const size_t n,
                const int id) {
    cnt = n;
    for (size_t i = 0; i < n; i++) {
        ploy[i].x = x[i];
        ploy[i].y = y[i];
    }  // for

    std::reverse(ploy, ploy + n);
}

bool query(const double dx, const double dy) {
    JP.x = dx;
    JP.y = dy;

    for (int i = 0; i < cnt; i++) {
        if (almost_equal(ploy[i].x, dx) && almost_equal(ploy[i].y, dy))
            return true;
        int next = i + 1;
        if (next == cnt)
            next = 0;
        if (almost_equal(0.0, Cross(ploy[next] - ploy[i], JP - ploy[i])) &&
            min(ploy[i].x, ploy[next].x) <= JP.x &&
            JP.x <= max(ploy[i].x, ploy[next].x) &&
            min(ploy[i].y, ploy[next].y) <= JP.y &&
            JP.y <= max(ploy[i].y, ploy[next].y))
            return true;
    }  // for

    return IsPointInPloy(cnt);
}

void finalize() {}
