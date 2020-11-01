#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

const int xA = 1;  // x < A?
const int yB = 2;  // y < B?
const int dK = 4;  // |x - y| < K?
const int eW = 8;  // (x ^ y) < W?
const int xL = 16;  // x > y?
const int yL = 32;  // x < y?
const int Ca = 64;  // carry bit

#define S 128
#define L 30
#define L0 31

i64 f[L0][S];
int A[L0], B[L0], K[L0], W[L0];

void decode(int x, int *y) {
    for (int i = 0; i < L; i++) {
        y[i] = x & 1;
        x >>= 1;
    }
}

void read(int *y) {
    int v;
    scanf("%d", &v);
    decode(v, y);
}

void solve() {
    read(A); read(B); read(K); read(W);

    memset(f, 0, sizeof(f));

    // init
    for (int x = 0; x < 2; x++)
    for (int y = 0; y < 2; y++)
    if (x <= A[L] && y <= B[L] && (x ^ y) <= W[L]) {
        int s = 0;
        if (x < A[L])
            s |= xA;
        if (y < B[L])
            s |= yB;
        if ((x ^ y) < W[L])
            s |= eW;
        if (x < y)
            s |= yL;
        if (x > y)
            s |= xL;

        if (abs(x - y) <= K[L]) {
            int ns = s;
            if (abs(x - y) < K[L])
                ns |= dK;
            f[L][ns] += 1;
        }

        if (x ^ y) {
            int ns = s | Ca;
            if (0 < K[L])
                ns |= dK;
            f[L][ns] += 1;
        }
    }

    for (int i = L - 1; i >= 0; i--)
    for (int x = 0; x < 2; x++)
    for (int y = 0; y < 2; y++)
    for (int s = 0; s < S; s++)
    if (f[i + 1][s] &&
        ((s & xA) || (x <= A[i])) &&
        ((s & yB) || (y <= B[i])) &&
        ((s & eW) || ((x ^ y) <= W[i]))) {
        if ((s & xL) && (s & yL))
            continue;

        int d = 0, ns = s;
        if (s & xL)
            d = x - y;
        else if (s & yL)
            d = y - x;
        else {
            d = abs(x - y);
            if (x < y)
                ns |= yL;
            if (x > y)
                ns |= xL;
        }

        if (s & Ca) {
            d += 2;
            ns ^= Ca;
        }

        if (x < A[i])
            ns |= xA;
        if (y < B[i])
            ns |= yB;
        if ((x ^ y) < W[i])
            ns |= eW;

        if (d == 2) {
            int s0 = ns;
            s0 |= Ca;
            if (1 < K[i])
                s0 |= dK;
            if ((s & dK) || (1 <= K[i])) {
                f[i][s0] += f[i + 1][s];
            }
        }

        if (d < 0 || d > 1)
            continue;

        if (d < K[i])
            ns |= dK;

        if ((s & dK) || (d <= K[i]))
            f[i][ns] += f[i + 1][s];

        if (d == 1) {
            ns |= Ca;
            if (0 < K[i])
                ns |= dK;
            f[i][ns] += f[i + 1][s];
        }
    }

    i64 ans = 0;
    for (int s = 0; s < S; s++)
    if (!(s & Ca)) {
        ans += f[0][s];
    }

    /*
    for (int i = 3; i >= 0; i--)
    for (int s = 0; s < S; s++)
    if (f[i][s]) {
        printf("f[%d][ ", i);
        if (s & xA) printf("xA ");
        if (s & yB) printf("yB ");
        if (s & dK) printf("dK ");
        if (s & eW) printf("eW ");
        if (s & xL) printf("xL ");
        if (s & yL) printf("yL ");
        if (s & Ca) printf("Ca ");
        printf("] = %lld\n", f[i][s]);
    }
    */

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
