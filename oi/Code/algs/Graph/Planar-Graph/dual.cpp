#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 1000

typedef long long i64;

struct Vector {
    Vector() : x(0), y(0) {}
    Vector(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    Vector operator+(const Vector &b) {
        return Vector(x + b.x, y + b.y);
    }

    Vector operator-(const Vector &b) {
        return Vector(x - b.x, y - b.y);
    }
};  // struct Vector

inline i64 dot(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

inline i64 cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

static int n, m;
static Vector location[NMAX + 10];

struct Region {
    int id;
    vector<int> path;
};  // struct Region
