#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 50000
#define SEGMAX 200000

#define SMAX 32
typedef unsigned int u32;
struct Basis {
    Basis() {
        memset(v, 0, sizeof(v));
    }

    u32 v[SMAX];
    auto operator[](const size_t i) -> u32& {
        return v[i];
    }

    auto span(u32 x) -> bool {
        for (int i = 0; i < SMAX; i++)
            if (v[i] && ((x >> i) & 1)) x ^= v[i];
        return !x;
    }

    void add(u32 x) {
        for (int i = 0; i < SMAX; i++) if ((x >> i) & 1) {
            if (v[i]) x ^= v[i];
            else {
                v[i] = x;
                return;
            }
        }
    }

    auto size() -> int {
        int r = 0;
        for (int i = 0; i < SMAX; i++) r += bool(v[i]);
        return r;
    }
};

auto intersect(Basis &u, Basis v) -> Basis {
    Basis z, r;
    for (int i = 0; i < SMAX; i++) if (u[i]) {
        u32 x = u[i], y = u[i];
        for (int j = 0; j < SMAX; j++) if ((x >> j) & 1) {
            if (v[j]) x ^= v[j], y ^= r[j];
            else {
                v[j] = x, r[j] = y;
                break;
        }}
        if (!x) z.add(y);
    }
    return z;
}

static int n, q;
static Basis tr[SEGMAX + 10];

#define L(x) (x << 1)
#define R(x) ((x << 1) | 1)

void setup(int x, int l, int r) {
    int m;
    if (l == r) {
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            u32 u;
            scanf("%u", &u);
            tr[x].add(u);
        }
    } else {
        m = (l + r) >> 1;
        setup(L(x), l, m);
        setup(R(x), m + 1, r);
        tr[x] = intersect(tr[L(x)], tr[R(x)]);
    }
}

static u32 t;
auto query(int x, int l, int r, int xl, int xr) -> bool {
    if (l <= xl && xr <= r) return tr[x].span(t);
    int m = (xl + xr) >> 1;
    if (l <= m && !query(L(x), l, r, xl, m)) return false;
    if (r > m && !query(R(x), l, r, m + 1, xr)) return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &q);
    setup(1, 1, n);
    while (q--) {
        int l, r;
        scanf("%d%d%u", &l, &r, &t);
        puts(query(1, l, r, 1, n) ? "YES" : "NO");
    }

    return 0;
}
