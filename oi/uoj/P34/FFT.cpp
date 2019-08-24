#include <cmath>
#include <cstdio>

#include <complex>

#define NMAX 262144

using namespace std;

typedef complex<double> Complex;

static Complex wtable[NMAX + 10];
static Complex iwtable[NMAX + 10];

void FFT(Complex *seq, int n, bool reversed) {
    if (n == 1)
        return;

    Complex *left = new Complex[n >> 1];
    Complex *right = new Complex[n >> 1];
    for (int i = 0; i < n; i += 2) {
        left[i >> 1] = seq[i];
        right[i >> 1] = seq[i + 1];
    }

    FFT(left, n >> 1, reversed);
    FFT(right, n >> 1, reversed);

    Complex w_n = (reversed ? iwtable[n] : wtable[n]);
    Complex w = Complex(1, 0);
    for (int i = 0; i < (n >> 1); i++) {
        seq[i] = left[i] + w * right[i];
        seq[i + (n >> 1)] = left[i] - w * right[i];

        if (i < (n >> 1) - 1)
            w *= w_n;
    }

    delete[] left;
    delete[] right;
}

static int a, b, n;
static Complex A[NMAX + 10];
static Complex B[NMAX + 10];

inline int next_pow(int n) {
    int ret = 1;
    while (n > ret) {
        ret <<= 1;
    }

    return ret;
}

int main() {
    scanf("%d%d", &a, &b);

    double v;
    for (int i = 0; i <= a; i++) {
        scanf("%lf", &v);
        A[i].real(v);
    }

    for (int i = 0; i <= b; i++) {
        scanf("%lf", &v);
        B[i].real(v);
    }

    // n = next_pow(a + b + 1);
    // n = next_pow(a + 1);
    n = 16;

    for (int i = 2; i <= n; i <<= 1) {
        wtable[i] = exp(Complex(0, 2.0 * M_PI / i));
        iwtable[i] = exp(Complex(0, -2.0 * M_PI / i));
    }

    FFT(A, n, false);
    FFT(B, n, false);

    for (int i = 0; i < n; i++) {
        A[i] = (A[i] * B[i]) / static_cast<double>(n);
    }

    FFT(A, n, true);

    // for (int i = 0; i <= a + b; i++) {
    //     printf("%d ", static_cast<int>(A[i].real() + 0.5));
    // }
    for (int i = 0; i < n; i++) {
        printf("%d ", static_cast<int>(A[i].real() + 0.5));
    }
    printf("\n");

    return 0;
}
