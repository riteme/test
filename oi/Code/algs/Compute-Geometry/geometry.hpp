#ifndef GEOMETRY_HPP_

#include <cmath>
#include <cfloat>
#include <iostream>
#include <iterator>
#include <algorithm>

#define EPSILON 0.01

template <typename TFloat>
bool is_same(const TFloat &a, const TFloat &b) {
    return fabs(a - b) < EPSILON;
}

struct Vector2 {
    Vector2() = default;
    Vector2(const double _x, const double _y) : x(_x), y(_y) {}
    Vector2(const Vector2 &) = default;
    Vector2(Vector2 &&) = default;
    Vector2 &operator=(const Vector2 &) = default;
    Vector2 &operator=(Vector2 &&) = default;

    friend Vector2 operator+(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator*(const Vector2 &a, const double b);
    friend Vector2 operator/(const Vector2 &a, const double b);
    friend double operator*(const Vector2 &a, const Vector2 &b);
    friend std::istream &operator>>(std::istream &stream, Vector2 &a);
    friend std::ostream &operator<<(std::ostream &stream, const Vector2 &a);

    double x = 0.0;
    double y = 0.0;
};  // struct Vector2

Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return { a.x + b.x, a.y + b.y };
}

Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return { a.x - b.x, a.y - b.y };
}

Vector2 operator*(const Vector2 &a, const double b) {
    return { a.x * b, a.y * b };
}

Vector2 operator/(const Vector2 &a, const double b) {
    return { a.x / b, a.y / b };
}

double operator*(const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - b.x * a.y;
}

std::istream &operator>>(std::istream &stream, Vector2 &a) {
    double x, y;
    stream >> x >> y;

    a = { x, y };

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Vector2 &a) {
    stream << "(" << a.x << ", " << a.y << ")";

    return stream;
}

struct Segment {
    Segment() = default;
    Segment(const Vector2 _p1, const Vector2 _p2) : p1(_p1), p2(_p2) {}
    Segment(const Segment &) = default;
    Segment(Segment &&) = default;
    Segment &operator=(const Segment &) = default;
    Segment &operator=(Segment &&) = default;

    friend std::istream &operator>>(std::istream &stream, Segment &a);
    friend std::ostream &operator<<(std::ostream &stream, const Segment &a);

    Vector2 p1;
    Vector2 p2;
};  // struct Segment

std::istream &operator>>(std::istream &stream, Segment &a) {
    double x1, y1, x2, y2;
    stream >> x1 >> y1 >> x2 >> y2;

    a = { { x1, y1 }, { x2, y2 } };
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Segment &a) {
    stream << a.p1 << " -- " << a.p2;

    return stream;
}

template <typename TVector>
double turning(const TVector &a, const TVector &b, const TVector &c) {
    TVector p1 = a - b;
    TVector p2 = a - c;

    return p1 * p2;
}

template <typename TVector>
bool is_on_segment(const TVector &a, const TVector &b, const TVector &c) {
    using std::min;
    using std::max;

    return min(a.x, a.y) <= c.x && c.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

enum Direction {
    E = 0,
    NE = 1,
    N = 2,
    NW = 3,
    W = 4,
    SW = 5,
    S = 6,
    SE = 7
};  // enum Direction

template <typename TVector>
Direction direction(const TVector &vec) {
    if (is_same(vec.x, 0.0)) {
        if (is_same(vec.y, 0.0)) {
            return E;
        } else if (vec.y > 0.0) {
            return N;
        } else {
            return S;
        }
    } else if (vec.x > 0.0) {
        if (is_same(vec.y, 0.0)) {
            return E;
        } else if (vec.y > 0.0) {
            return NE;
        } else {
            return SE;
        }
    } else {
        if (is_same(vec.y, 0.0)) {
            return W;
        } else if (vec.y > 0.0) {
            return NW;
        } else {
            return SW;
        }
    }
}

template <typename TVector>
bool is_intersect(const TVector &a, const TVector &b, const TVector &c,
                  const TVector &d) {
    double d1 = turning(a, b, c);
    double d2 = turning(b, a, d);
    double d3 = turning(c, d, b);
    double d4 = turning(d, c, a);

    // std::cout << d1 << ", " << d2 << ", " << d3 << ", " << d4 << std::endl;

    if (is_same(d1, 0.0) && is_on_segment(a, b, c))
        return true;
    if (is_same(d2, 0.0) && is_on_segment(a, b, d))
        return true;
    if (is_same(d3, 0.0) && is_on_segment(c, d, b))
        return true;
    if (is_same(d4, 0.0) && is_on_segment(c, d, a))
        return true;

    return d1 * d2 > 0 || d3 * d4 > 0;
}

template <typename TIterator>
bool brute_any_segment_intersect(const TIterator &beg, const TIterator &end) {
    using namespace std;

    for (auto i = beg; i != end; i++) {
        for (auto j = next(i); j != end; j++) {
            if (is_intersect(i->p2, i->p2, j->p2, j->p2))
                return true;
        }
    }

    return false;
}

template <typename TIterator>
void polar_sort(const TIterator &beg, const TIterator &end) {
    std::stable_sort(beg, end, [](const Vector2 &a, const Vector2 &b) {
        return direction(a) < direction(b) || (a * b > 0);
    });
}

#endif  // IFNDEF GEOMETRY_HPP_
