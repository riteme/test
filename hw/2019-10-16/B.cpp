#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000000
#define M1 998244353
#define M2 1000000007
#define BASE 19260817

static i64 p1[NMAX + 10], p2[NMAX + 10];
struct Hash {
    Hash() : u(0), v(0) {}
    Hash(int _u, int _v) : u(_u), v(_v) {}

    int u, v;

    bool operator==(const Hash &z) const {
        return u == z.u && v == z.v;
    }

    bool operator!=(const Hash &z) const {
        return u != z.u || v != z.v;
    }

    Hash operator+(i64 x) const {
        return Hash((u + x) % M1, (v + x) % M2);
    }

    Hash operator+(const Hash &z) const {
        return Hash((u + z.u) % M1, (v + z.v) % M2);
    }

    Hash operator-(i64 x) const {
        int u1 = u - x;
        int v1 = v - x;
        if (u1 < 0) u1 += M1;
        if (v1 < 0) v1 += M2;
        return Hash(u1, v1);
    }

    Hash operator-(const Hash &z) const {
        int u1 = u - z.u;
        int v1 = v - z.v;
        if (u1 < 0) u1 += M1;
        if (v1 < 0) v1 += M2;
        return Hash(u1, v1);
    }

    Hash operator*(i64 x) const {
        return Hash(u * x % M1, v * x % M2);
    }

    Hash operator<<(int i) const {
        return Hash(u * p1[i] % M1, v * p2[i] % M2);
    }
};

static int n, ans[NMAX + 10];
static char s[NMAX + 10];
static Hash vec[NMAX + 10];

Hash H(int l, int r) {
    return vec[r] - (vec[l - 1] << (r - l + 1));
}

void initialize() {
    scanf("%d%s", &n, s + 1);
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= n; i++) {
        p1[i] = i64(p1[i - 1]) * BASE % M1;
        p2[i] = i64(p2[i - 1]) * BASE % M2;
        vec[i] = (vec[i - 1] << 1) + s[i];
    }
}

int main() {
    initialize();
    int l = (n + 1) / 2, r = l + !(n & 1), k;
    for ( ; l >= 1; l--, r++) {
        if (l == r) k = -1;
        else if (l + 1 == r) k = s[l] == s[r] ? 1 : -1;
        else {
            for (k += 2; k > -1; k -= 2)
                if (H(l, l + k - 1) == H(r - k + 1, r)) break;
        }
        ans[l] = k;
    }
    for (int i = 1; i <= (n + 1) / 2; i++)
        printf("%d ", ans[i]);
    return 0;
}
