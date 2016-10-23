#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define EPSILON 0.0000001

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

struct Vector {
    Vector() : x(0.0), y(0.0) {}
    Vector(const double _x, const double _y) : x(_x), y(_y) {}

    Vector(const Vector &b) : x(b.x), y(b.y) {}

    Vector &operator=(const Vector &b) {
        x = b.x;
        y = b.y;

        return *this;
    }

    bool operator==(const Vector &b) const {
        return almost_equal(x, b.x) && almost_equal(y, b.y);
    }

    bool operator!=(const Vector &b) const {
        return !(*this == b);
    }

    Vector operator+(const Vector &b) const {
        return Vector(x + b.x, y + b.y);
    }

    Vector operator-(const Vector &b) const {
        return Vector(x - b.x, y - b.y);
    }

    Vector operator*(const double b) const {
        return Vector(x * b, y * b);
    }

    double x, y;
};  // struct Vector

inline double cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

inline double dot(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
}

#define NMAX 100000

typedef long long int64;

template <typename T>
struct Stack {
    void push(const T &v) {
        _container.push_back(v);
    }

    void pop() {
        _container.pop_back();
    }

    T &top() {
        return _container.back();
    }

    T &second() {
        return _container[size() - 2];
    }

    size_t size() const {
        return _container.size();
    }

    bool empty() const {
        return _container.empty();
    }

    T &operator[](const size_t pos) {
        return _container[pos];
    }

 private:
    vector<T> _container;
};  // struct Stack

static int n;
static int64 h[NMAX + 10];
static int64 sum[NMAX + 10];
static int64 f[NMAX + 10];
static int64 endpoint[NMAX + 10];
static Stack<Vector> convex;

static void insert_point(const Vector &p) {
    while (convex.size() >= 2 &&
           cross(convex.top() - p, convex.second() - p) >= 0.0)
        convex.pop();

    while (!convex.empty() && p.x < convex.top().x)
        convex.pop();
    convex.push(p);
}

static Vector &query_point(const double slope) {
    int left = 0, right = convex.size() - 1;

    while (left + 1 < right) {
        int mid = (left + right) / 2;
        assert(0 < mid && mid < convex.size() - 1);

        double leftslope = (convex[mid].x - convex[mid - 1].x) /
                           (convex[mid].y - convex[mid - 1].y);
        double rightslope = (convex[mid].x - convex[mid + 1].x) /
                            (convex[mid].y - convex[mid + 1].y);

        if (leftslope <= slope && slope <= rightslope)
            left = right = mid;
        else if (slope < leftslope)
            left = mid;
        else
            right = mid;
    }

    if (left != right &&
        slope <= (convex[left].x - convex[right].x) /
                     (convex[left].y - convex[right].y))
        left = right;

    return convex[left];
}

static void initialize() {
    scanf("%d", &n);
    n++;

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &h[n - i + 1]);
        sum[n - i + 1] = h[n - i + 1];
    }

    for (int i = 1; i <= n; i++)
        sum[i] += sum[i - 1];
}

int main() {
    initialize();

    f[n] = h[n];
    endpoint[n] = n;
    insert_point(Vector(f[n] + sum[n - 1], n));

    for (int i = n - 1; i >= 1; i--) {
        Vector &p = query_point(-h[i]);
        int target = p.y;
        int64 directcost = (2 * (n - i + 1) - 1) * h[i];
        int64 bettercost =
            f[target] + (target - i) * h[i] + sum[target - 1] - sum[i - 1];

        if (bettercost < directcost) {
            f[i] = bettercost;
            endpoint[i] = endpoint[target];
        } else {
            f[i] = directcost;
            endpoint[i] = i;
        }

        insert_point(Vector(f[i] + sum[i - 1], i));
    }  // for

    printf("%lld\n", f[1] * 2 - h[endpoint[1]]);

    return 0;
}
