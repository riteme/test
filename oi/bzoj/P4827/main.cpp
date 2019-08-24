#include <cstdio>
#include <cstring>
#include <climits>

#include <complex>
#include <algorithm>

using namespace std;

#define NMAX 131072

static int n, m;
static int sumx, sumx2, sumy, sumy2;
static int x[NMAX + 10];
static int y[NMAX + 10];
static int sxy[NMAX + 10];

typedef complex<double> Complex;

void fft(Complex *X, int n, bool reversed) {
    static Complex tmp[NMAX + 10];
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
        Complex wn = exp(Complex(0, (reversed ? -2 : 2) * M_PI / s));

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

    if (reversed) {
        Complex div = Complex(1.0 / n);
        for (int i = 0; i < n; i++) {
            X[i] *= div;
        }
    }
}

inline int next_pow(int x) {
    int ret = 1;
    while (x > ret) {
        ret <<= 1;
    }

    return ret;
}

static Complex A[NMAX + 10];
static Complex B[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", x + i);
        sumx += x[i];
        sumx2 += x[i] * x[i];
        A[i - 1].real(x[i]);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", y + i);
        sumy += y[i];
        sumy2 += y[i] * y[i];
        B[n - i].real(y[i]);
    }

    int k = next_pow(n * 2);
    fft(A, k, false);
    fft(B, k, false);

    for (int i = 0; i < k; i++) {
        A[i] *= B[i];
    }

    fft(A, k, true);

    sxy[0] = A[n - 1].real() + 0.5;
    for (int i = 1; i < n; i++) {
        sxy[i] = (A[n - i - 1].real() + A[2 * n - i - 1].real()) + 0.5;
    }
}

int main() {
    initialize();

    int delta = INT_MAX;
    int xy = 0;
    for (int c = 0; c <= m; c++) {
        delta = min(delta,
                    n * c * c + 2 * c * (sumx - sumy));
        delta = min(delta,
                    n * c * c + 2 * c * (sumy - sumx));
    }

    for (int i = 0; i < n; i++) {
        xy = max(xy, sxy[i]);
    }

    printf("%d\n", sumx2 + sumy2 + delta - 2 * xy);

    return 0;
}
