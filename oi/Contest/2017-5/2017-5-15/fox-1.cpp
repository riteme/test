// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 1000000007

struct Info {
    Info() : x(0), y(0), c(0), nx(0), ny(0), nc(0) {}

    i64 x, y, c, nx, ny, nc;

    void update() {
        x = nx;
        y = ny;
        c = nc;
    }

    void print(const char *name) {
        printf("%s: x = %lld (%lld), y = %lld (%lld), cnt = %lld\n",
            name, x, x - MOD, y, y - MOD, c);
    }
};

inline void add(i64 &a, i64 b) {
    a += b % MOD;

    if (a >= MOD)
        a -= MOD;
    else if (a < 0)
        a += MOD;
}

int main() {
#ifdef USE_FILE_IO
    freopen("fox.in", "r", stdin);
    freopen("fox.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);

    while (T--) {
        i64 t, S, L, R, ans = 0;
        Info ri, le, up, dw;
        ri.c = ri.nc = 1;
        scanf("%lld%lld%lld%lld", &t, &S, &L, &R);

        while (t--) {
            ans = ans * (S + L + R) % MOD;

            add(ans, S * (ri.y - le.y + up.x - dw.x));

            add(ri.nx, S * ri.c + (S - 1) * ri.x + R * up.x + L * dw.x);
            add(ri.ny, (S - 1) * ri.y + R * up.y + L * dw.y);
            add(ri.nc, (S - 1) * ri.c + R * up.c + L * dw.c);
            
            add(le.nx, -S * le.c + (S - 1) * le.x + L * up.x + R * dw.x);
            add(le.ny, (S - 1) * le.y + L * up.y + R * dw.y);
            add(le.nc, (S - 1) * le.c + L * up.c + R * dw.c);

            add(up.nx, (S - 1) * up.x + R * le.x + L * ri.x);
            add(up.ny, S * up.c + (S - 1) * up.x + R * le.y + L * ri.y);
            add(up.nc, (S - 1) * up.c + R * le.c + L * ri.c);

            add(dw.nx, (S - 1) * dw.x + L * le.x + R * ri.x);
            add(dw.ny, -S * dw.c + (S - 1) * dw.y + L * le.y + R * ri.y);
            add(dw.nc, (S - 1) * dw.c + L * le.c + R * ri.c);

            ri.update();
            le.update();
            up.update();
            dw.update();

            // puts("===");
            // printf("ans = %lld (%lld)\n", ans, ans - MOD);
            // ri.print("ri");
            // le.print("le");
            // up.print("up");
            // dw.print("dw");
        }

        printf("%lld\n", ans);
    }

    return 0;
}
