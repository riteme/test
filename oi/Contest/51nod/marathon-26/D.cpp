#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 8000

typedef long long i64;

struct Point {
    Point() : x(0), y(0) {}
    Point(i64 _x, i64 _y) : x(_x), y(_y) {}

    int index;
    i64 x, y;

    int id() const {
        return y >= 0 ? 0 : 1;
    }

    i64 length() const {
        return x * x + y * y;
    }

    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    i64 operator%(const Point &b) const {
        return x * b.y - y * b.x;
    }

    bool operator<(const Point &b) const {
        return x < b.x || (x == b.x && y < b.y);
    }
};

bool cmp(const Point &a, const Point &b) {
    if (a.id() != b.id())
        return a.id() < b.id();

    i64 p = a % b;
    return p < 0 || (p == 0 && a.length() < b.length());
}

static int n;
static Point P[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    int p = 0;
    for (int i = 0; i <= n; i++) {
        scanf("%lld%lld", &P[i].x, &P[i].y);

        if (P[i] < P[p])
            p = i;
    }

    for (int i = 0; i <= n; i++) {
        if (i != p)
            P[i] = P[i] - P[p];
        P[i].index = i;
    }

    swap(P[p], P[0]);
    sort(P + 1, P + n + 1, cmp);
}

int main() {
    initialize();

    int i;
    for (i = n; i > 0; i--) {
        if (P[i] % P[i - 1] != 0)
            break;
    }

    reverse(P + i, P + n + 1);

    i = 0;
    while (P[i].index != 0)
        i++;

    for (int j = 0; j <= n + 1; j++) {
        printf("%d\n", P[i].index);
        i++;
        if (i > n)
            i = 0;
    }

    return 0;
}
