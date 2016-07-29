/**
 * Problem: I need a data to prove that this algorithm is wrong.
 * orzorzorz
 */

#define NDEBUG

#include <bits/stdc++.h>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif  // IFNDEF NDEBUG

#define EPSILON 0.00000001

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

struct Vector2 {
    Vector2() : x(0.0), y(0.0) {}
    Vector2(const double _x, const double _y) : x(_x), y(_y) {}

    double x, y;

    Vector2 &operator+=(const Vector2 &b) {
        x += b.x;
        y += b.y;

        return *this;
    }

    Vector2 &operator-=(const Vector2 &b) {
        x -= b.x;
        y -= b.y;

        return *this;
    }

    Vector2 &operator*=(const double &b) {
        x *= b;
        y *= b;

        return *this;
    }

    friend Vector2 operator+(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator*(const Vector2 &a, const double &b);
};  // struct Vector2

Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator*(const Vector2 &a, const double &b) {
    return Vector2(a.x * b, a.y * b);
}

inline double length(const Vector2 &a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

inline Vector2 normalize(const Vector2 &a) {
    return a * (1.0 / length(a));
}

inline double cross(const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - a.y * b.x;
}

inline double dot(const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

#define NMAX 2000

static int n;
static double X[NMAX + 10];
static double Y1[NMAX + 10];
static double Y2[NMAX + 10];
static double P[NMAX + 10];
static bool marked[NMAX + 10];
static Vector2 s, t;
static double velocity;

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        double x1, y1, x2, y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);

        X[i] = x2;
        Y1[i] = y1;
        Y2[i] = y2;
        Y1[i - 1] = max(Y1[i - 1], y1);
        Y2[i - 1] = min(Y2[i - 1], y2);
    }  // for

    scanf("%lf%lf", &s.x, &s.y);
    scanf("%lf%lf", &t.x, &t.y);
    scanf("%lf", &velocity);
}

static void correct(int left, int right, const Vector2 &u, const Vector2 &v) {
    if (right < left)
        return;

    // DEBUG("[%d, %d]: (%lf, %lf) - (%lf, %lf)\n", left, right, u.x, u.y, v.x,
    // v.y);

    double xwidth = v.x - u.x;
    for (int i = left; i <= right; i++) {
        double delta_x = X[i] - u.x;
        Vector2 intersect_point = (v - u) * (delta_x / xwidth) + u;
        double y = intersect_point.y;

        if (Y1[i] <= y && y <= Y2[i]) {
            P[i] = y;
        } else if (y < Y1[i]) {
            if (!marked[i + 1] && u.y >= Y1[i] &&
                almost_equal(Y1[i], Y1[i + 1]))
                i++;

            P[i] = Y1[i];
            marked[i] = true;

            correct(left, i - 1, u, Vector2(X[i], Y1[i]));
            correct(i + 1, right, Vector2(X[i], Y1[i]), v);
            return;
        } else {  // y > Y2[i]
            if (!marked[i + 1] && u.y <= Y2[i] &&
                almost_equal(Y2[i], Y2[i + 1]))
                i++;

            P[i] = Y2[i];
            marked[i] = true;

            correct(left, i - 1, u, Vector2(X[i], Y2[i]));
            correct(i + 1, right, Vector2(X[i], Y2[i]), v);
            return;
        }
    }  // for
}

int main() {
    initialize();

    if (s.x > t.x)
        swap(s, t);

    int i = 1, j = n - 1;
    while (X[i] < s.x)
        i++;
    while (X[j] > t.x)
        j--;

    // DEBUG("i = %d, j = %d\n", i, j);
    correct(i, j, s, t);

    // for (int k = i; k <= j; k++)
    // printf("(%lf, %lf)\n", X[k], P[k]);

    double dist = 0.0;
    for (int k = i; k < j; k++)
        dist += length(Vector2(X[k + 1] - X[k], P[k + 1] - P[k]));

    if (i <= j) {
        dist += length(Vector2(X[i] - s.x, P[i] - s.y));
        dist += length(Vector2(t.x - X[j], P[j] - t.y));
    } else
        dist = length(t - s);

    printf("%.10lf\n", dist / velocity);

    return 0;
}  // function main
