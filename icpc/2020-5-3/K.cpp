#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define T 100

struct Point {
    int x, y, h;
};

Point p[NMAX + 10];
multimap<int, int> mpx, mpy;

int cur;
inline void check(int i, int j) {
    int dx = abs(p[i].x - p[j].x);
    int dy = abs(p[i].y - p[j].y);
    int dh = abs(p[i].h - p[j].h);
    int sx = dx & 1, sy = dy & 1, sh = dh & 1;
    if (((sx ^ sy) != sh) || dx + dy < dh) {
        printf("%d\n", cur);
        exit(0);
    }
}

int main() {
    int n, A, B;
    scanf("%d%d%d", &n, &A, &B);
    auto xl = mpx.insert({0, 0});
    auto xr = mpx.insert({A + 1, 0});
    auto yl = mpy.insert({0, 0});
    auto yr = mpy.insert({B + 1, 0});
    for (cur = 1; cur <= n; cur++) {
        int i = cur;
        // printf("%d\n", i);
        scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].h);
        auto it = mpx.insert({p[i].x, i});
        auto x = prev(it);
        for (int t = 0; t < T && x != xl; t++, x--)
            check(x->second, i);
        x = next(it);
        for (int t = 0; t < T && x != xr; t++, x++)
            check(x->second, i);

        it = mpy.insert({p[i].y, i});
        x = prev(it);
        for (int t = 0; t < T && x != yl; t++, x--)
            check(x->second, i);
        x = next(it);
        for (int t = 0; t < T && x != yr; t++, x++)
            check(x->second, i);
    }
    puts("bravo komisijo");

    return 0;
}