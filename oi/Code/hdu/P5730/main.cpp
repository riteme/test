#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>
#include <cstring>

#include <complex>
#include <algorithm>

using namespace std;

typedef complex<double> Complex;

#define NMAX 262144
#define MOD 313

inline int next_pow(int n) {
    int ret = 1;
    while (n > ret) {
        ret <<= 1;
    }

    return ret;
}

static Complex tmp[NMAX + 10];
static Complex A[NMAX + 10], B[NMAX + 10];

void fft(Complex *X, int n, bool reversed) {
    memcpy(tmp, X, sizeof(Complex) * n);
    int rev = 0;
    for (int i = 0; i < n; i++) {
        X[i] = tmp[rev];

        int k = n >> 1;
        while (rev & k) {
            rev ^= k;
            k >>= 1;
        }

        rev |= k;
    }

    for (int s = 2; s <= n; s <<= 1) {
        int len = s >> 1;
        Complex wn = exp(Complex(0, (reversed ? -2.0 : 2.0) * M_PI / s));

        for (int i = 0; i < n; i += s) {
            Complex w = Complex(1);
            for (int j = i; j < i + len; j++) {
                Complex tmp = X[j];
                X[j] = tmp + w * X[j + len];
                X[j + len] = tmp - w * X[j + len];
                w *= wn;
            }
        }
    }
}

static int n;
static int cnt[NMAX + 10], f[NMAX + 10];

void solve(int l, int r) {
    if (l + 1 == r)
        return;

    int mid = (l + r) >> 1;
    solve(l, mid);

    int m = next_pow(r - l + mid - l + 1);
    memset(A, 0, sizeof(Complex) * m);
    memset(B, 0, sizeof(Complex) * m);
    for (int i = 1; i <= r - l; i++) {
        A[i].real(cnt[i]);
    }

    for (int i = l; i < mid; i++) {
        B[i - l].real(f[i]);
    }

    fft(A, m, false);
    fft(B, m, false);

    for (int i = 0; i < m; i++) {
        A[i] *= B[i];
    }

    fft(A, m, true);

    for (int i = mid; i < r; i++) {
        f[i] = (f[i] + int(A[i - l].real() / m + 0.5)) % MOD;
    }

    solve(mid, r);
}

void initialize() {
    memset(f, 0, sizeof(f));
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= n; i++) {
        scanf("%d", cnt + i);
        cnt[i] %= MOD;
    }

    f[0] = 1;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (!n)
            break;

        initialize();
        solve(0, next_pow(n + 1));
        printf("%d\n", f[n]);
    }

    return 0;
}
