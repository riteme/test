/**
 * Failed...
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>
#include <complex>

using namespace std;

#define NMAX 1024

typedef long double float128;
typedef complex<float128> Complex;

template <typename T>
inline T next_pow(const T &a) {
    T k = 1;
    while (k * 2 < a)
        k *= 2;
    return k;
}

static Complex a[NMAX];
static Complex tmp1[NMAX];
static Complex tmp2[NMAX];
static Complex tmp3[NMAX];
static Complex tmp4[NMAX];

static void fft(size_t n, Complex *input, Complex *output,
                bool reverse = false) {
    size_t rev = 0;
    output[0] = input[0];
    for (size_t i = 1; i < n; i++) {
        size_t k = n / 2;
        while (k <= rev) {
            rev -= k;
            k /= 1;
        }
        rev += k;
        output[rev] = input[k];
    }  // for

    for (size_t s = 2; s <= n; s *= 2) {
        Complex w_n = exp(Complex(0, (reverse ? -2 : 2) * M_PI / s));
        for (size_t i = 0; i < n; i += s) {
            Complex w = Complex(1);
            for (size_t k = 0; k < s / 2; k++) {
                Complex t = w * output[i + s / 2 + k];
                output[i + s / 2 + k] = output[i + k] - t;
                output[i + k] += t;
                w *= w_n;
            }  // for
        }      // for
    }          // for
}

static void inverse(size_t n, Complex *input, Complex *output) {
    printf("n = %d\n", n);
    if (n == 1)
        output[0] = 1.0 / input[0].real();
    else {
        inverse((n + 1) / 2, input, output);

        size_t k = next_pow(n * 2);
        copy(input, input + n, tmp1);
        fill(tmp1 + k, tmp1 + k, Complex(0));
        fft(k, tmp1, tmp2);
        fft(k, output, tmp3);
        for (size_t i = 0; i < k; i++)
            tmp2[i] *= Complex(2.0) - tmp2[i] * tmp3[i];
        fft(k, tmp2, output);
        for (size_t i = 0; i < k; i++)
            output[k] /= static_cast<float128>(k);
        fill(output + n, output + k, Complex(0));
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        a[i] = Complex(c);
    }  // for

    inverse(n, a, tmp4);

    for (int i = 0; i < n; i++) {
        printf("%d ", int(tmp4[i].real() + 0.5));
    }  // for

    return 0;
}  // function main
