#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

struct vec {
    vec() : x(0), y(0) {}
    vec(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    i64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    i64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

int n, s, t;
vec p[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
    }
    p[n] = p[0];

    scanf("%d%d", &s, &t);
    if (s == 0)
        s = n;
    if (t == 0)
        t = n;

    bool rev = s > t;
    if (rev)
        swap(s, t);

    vector<int> stk;
    for (int i = s; i <= t; i++) {
        while (stk.size() > 1 && (p[stk[stk.size() - 2]] - p[i]) % (p[stk[stk.size() - 1]] - p[i]) >= 0) {
            stk.pop_back();
        }

        stk.push_back(i);
    }

    if (rev)
        reverse(stk.begin(), stk.end());

    printf("%zu\n", stk.size());
    for (int x : stk) {
        printf("%d ", x % n);
    }
    puts("");

    return 0;
}