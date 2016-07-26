/**
 * Recursive FFT
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

#define NMAX 300000

typedef complex<double> Complex;

static int n, m;
static int ra;
static Complex x1[NMAX + 10];
static Complex X1[NMAX + 10];
static Complex x2[NMAX + 10];
static Complex X2[NMAX + 10];
static Complex x3[NMAX + 10];
static Complex aux[NMAX + 10];

inline int next_pow(int x) {
    int k = 1;
    while (k < x)
        k <<= 1;
    return k;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i <= n; i++) {
        double v;
        scanf("%lf", &v);
        x1[i].real(v);
    }
    for (int i = 0; i <= m; i++) {
        double v;
        scanf("%lf", &v);
        x2[i].real(v);
    }

    ra = next_pow(n + m + 2);
}

static void fft(int left, int right, Complex *input, Complex *output,
                bool reversed = false) {
    if (left == right) {
        output[left] = input[left];
        return;
    }

    memcpy(aux + left, input + left, sizeof(Complex) * (right - left + 1));
    int n = right - left + 1;
    int mid = (left + right) / 2;
    int pos = left;
    for (int i = left; i <= right; i += 2)
        input[pos++] = aux[i];
    for (int i = left + 1; i <= right; i += 2)
        input[pos++] = aux[i];

    fft(left, mid, input, output, reversed);
    fft(mid + 1, right, input, output, reversed);

    Complex wn = exp(Complex(0, (reversed ? -1 : 1) * 2 * M_PI / n));
    Complex w = Complex(1);
    for (int k = 0; k <= n / 2 - 1; k++) {
        Complex t = w * output[mid + k + 1];
        output[mid + k + 1] = output[left + k] - t;
        output[left + k] = output[left + k] + t;
        w *= wn;
    }  // for
}

int main() {
    initialize();

    fft(0, ra - 1, x1, X1);
    fft(0, ra - 1, x2, X2);
    for (int i = 0; i < ra; i++)
        X2[i] *= X1[i];
    fft(0, ra - 1, X2, x3, true);
    for (int i = 0; i < ra; i++)
        x3[i] /= static_cast<double>(ra);

    for (int i = 0; i <= n + m; i++)
        printf("%d ", int(x3[i].real() + 0.5));

    return 0;
}  // function main
