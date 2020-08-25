#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 1000

typedef long long i64;

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

int n, m;
vec A[NMAX + 10], B[MMAX + 10];
int sgn[NMAX + 10][NMAX + 10];

bool contain(vec a, vec b, const vec &p) {
    if (a % b < 0)
        swap(a, b);
    return a % p >= 0 && p % b >= 0 && (b - a) % (p - a) >= 0;
}

void _main() {
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &A[i].x, &A[i].y);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld", &B[i].x, &B[i].y);
    }

    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) {
        sgn[i][j] = 0;
        for (int k = 1; k <= m; k++) {
            if (contain(A[i], A[j], B[k]))
                sgn[i][j] ^= 1;
        }
        sgn[j][i] = sgn[i][j];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
    for (int k = j + 1; k <= n; k++) {
        int cnt = sgn[i][j] ^ sgn[j][k] ^ sgn[k][i];
        if (cnt)
            ans++;
    }

    printf("%d\n", ans);
}

int main() {
    int t = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        t++;
        printf("Case %d: ", t);
        _main();
    }
    return 0;
}
