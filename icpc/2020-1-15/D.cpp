#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

#define CW 0
#define CCW 1

typedef long long i64;

struct vec {
    i64 x, y;

    i64 len2() const {
        return x * x + y * y;
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
};

i64 dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

i64 cross(const vec &u, const vec &v) {
    return u.y * v.x - u.x * v.y;
}

int n, id[NMAX + 10], mxw;
vec p[NMAX + 10];
vector<int> B[NMAX + 10];
int pt[NMAX + 10][NMAX + 10][2];

void build_convex(int w) {
    int u = 0;
    for (int i = 1; i < B[w].size(); i++) {
        int x = B[w][i], y = B[w][u];
        if (p[x].x < p[y].x || (p[x].x == p[y].x && p[x].y < p[y].y))
            u = i;
    }

    if (u) swap(B[w][0], B[w][u]);
    sort(B[w].begin() + 1, B[w].end(), [w](int i, int j) {
        auto u = p[i] - p[B[w][0]];
        auto v = p[j] - p[B[w][0]];
        i64 cr = cross(u, v);
        return cr ? cr > 0 : u.len2() < v.len2();
    });

    int t = 0;
    for (int i = 1; i < B[w].size(); i++) {
        int u = B[w][i];
        while (t && cross(p[B[w][t]] - p[u], p[B[w][t - 1]] - p[u]) >= 0)
            t--;
        B[w][++t] = u;
    }

    B[w].resize(t + 1);
    for (int i : B[w])
        id[i] = w;
}

void scan(int i) {
    for (int w = 1; w <= mxw; w++) if (!B[w].empty())
    for (int j : B[w]) {
        if (cross(p[j] - p[i], p[pt[i][w][CW]] - p[i]) >= 0)
            pt[i][w][CW] = j;
        if (cross(p[j] - p[i], p[pt[i][w][CCW]] - p[i]) <= 0)
            pt[i][w][CCW] = j;
    }
}

bool in(const vec &a, const vec &b, const vec &c, const vec &u) {
    i64 s0 = abs(cross(b - a, c - a));
    i64 s1 = abs(cross(a - u, b - u)) + abs(cross(b - u, c - u)) + abs(cross(c - u, a - u));
    return s0 == s1;
}

bool in_convex(int i, int w) {
    for (int j = 1; j < B[w].size() - 1; j++)
        if (in(p[B[w][0]], p[B[w][j]], p[B[w][j + 1]], p[i]))
            return true;
    return false;
}

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        p[i] = {x, y};
        B[w].push_back(i);
        mxw = max(mxw, w);
    }

    for (int i = 1; i <= mxw; i++)
        build_convex(i);
    for (int i = 1; i <= n; i++) if (id[i])
        scan(i);
}

int main() {
    initialize();

    return 0;
}