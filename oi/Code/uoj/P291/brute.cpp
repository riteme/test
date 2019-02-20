#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 998244353LL
#define INV4 748683265LL

typedef long long i64;

struct Array4i {
    Array4i() {
        memset(a, 0, sizeof(a));
    }
    Array4i(i64 a0, i64 a1, i64 a2, i64 a3) {
        a[0] = a0;
        a[1] = a1;
        a[2] = a2;
        a[3] = a3;
    }

    i64 a[4];

    void normalize() {
        for (int i = 0; i < 4; i++) {
            if (a[i] >= MOD) a[i] -= MOD;
            else if (a[i] < -MOD) a[i] += MOD;
        }
    }

    Array4i operator+(const Array4i &b) const {
        Array4i c = {a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]};
        c.normalize();
        return c;
    }

    Array4i operator-(const Array4i &b) const {
        Array4i c = {a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]};
        c.normalize();
        return c;
    }

    Array4i operator*(const Array4i &b) const {
        return {a[0] * b[0] % MOD, a[1] * b[1] % MOD, a[2] * b[2] % MOD, a[3] * b[3] % MOD};
    }

    Array4i &operator*=(const Array4i &b) {
        a[0] = a[0] * b[0] % MOD;
        a[1] = a[1] * b[1] % MOD;
        a[2] = a[2] * b[2] % MOD;
        a[3] = a[3] * b[3] % MOD;
        return *this;
    }

    inline i64 &operator[](const int i) {
        return a[i];
    }

    inline const i64 operator[](const int i) const {
        return a[i];
    }
};

inline Array4i fwt(const Array4i &arr) {
    i64 a = arr[0] + arr[1], b = arr[0] - arr[1];
    i64 c = arr[2] + arr[3], d = arr[2] - arr[3];
    return {(a + c) % MOD, (b + d) % MOD, (a - c) % MOD, (b - d) % MOD};
}

inline Array4i rfwt(const Array4i &arr) {
    i64 a = arr[0] + arr[1], b = arr[0] - arr[1];
    i64 c = arr[2] + arr[3], d = arr[2] - arr[3];
    return {(a + c) * INV4 % MOD, (b + d) * INV4 % MOD, (a - c) * INV4 % MOD, (b - d) * INV4 % MOD};
}

static int n, m, q;
static i64 inv[NMAX + 10];
static struct {
    int l, r;

    int len() const {
        return r - l + 1;
    }
} op[NMAX + 10];

Array4i query(int l, int r) {
    Array4i ret = {1, 1, 1, 1};
    for (int i = 1; i <= m; i++) {
        const int L = op[i].len();
        if (i == m && (m & 1) && !l) {  // Since when l = 0 simply returns 0.
            if (op[i].r < r) ret *= fwt({0, 0, 1, 0});
            else if (op[i].l > r) ret *= fwt({0, 1, 0, 0});
            else ret *= fwt({inv[L], (op[i].r - r) * inv[L] % MOD, (r - op[i].l) * inv[L] % MOD, 0});
        } else if (op[i].l <= l && r <= op[i].r) ret *= fwt({
            (L - 2) * inv[L] % MOD, inv[L], inv[L], 0
        });
        else if (op[i].l <= l && l <= op[i].r) ret *= fwt({
            (L - 1) * inv[L] % MOD, inv[L], 0, 0
        });
        else if (op[i].l <= r && r <= op[i].r) ret *= fwt({
            (L - 1) * inv[L] % MOD, 0, inv[L], 0
        });
    }
    return rfwt(ret);
}

int main() {
    scanf("%d%d", &n, &q);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
    for (int i = 1; i <= q; i++) {
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1) op[++m] = {l, r};
        else {
            // if (l == 1) fprintf(stderr, "[%d, %d]: %d\n", l, r, i - m);
            auto result = query(l - 1, r);
            i64 ans = (result[0] + result[3]) % MOD;
            if (ans < 0) ans += MOD;
            printf("%lld\n", ans);
        }
    }
    return 0;
}