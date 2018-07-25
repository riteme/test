#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <complex>
#include <algorithm>

using namespace std;

#define NMAX 131072
#define CMAX 50000

typedef unsigned int u32;

struct Complex {
    Complex() : real(0.0), imag(0.0) {}
    Complex(const double &_real) : real(_real), imag(0.0) {}
    Complex(const double &_real, const double &_imag)
            : real(_real), imag(_imag) {}

    double real, imag;

    friend Complex operator+(const Complex &a, const Complex &b);
    friend Complex operator-(const Complex &a, const Complex &b);
    friend Complex operator*(const Complex &a, const Complex &b);
    friend Complex operator/(const Complex &a, const double &b);

    Complex &operator*=(const Complex &b) {
        double re = real;
        double im = imag;
        real = (re * b.real - im * b.imag);
        imag = (re * b.imag + im * b.real);

        return *this;
    }
    Complex &operator/=(const double &b) {
        real /= b;
        imag /= b;

        return *this;
    }
};  // struct Complex

Complex operator+(const Complex &a, const Complex &b) {
    Complex c = Complex(a.real + b.real, a.imag + b.imag);

    return c;
}

Complex operator-(const Complex &a, const Complex &b) {
    Complex c = Complex(a.real - b.real, a.imag - b.imag);

    return c;
}

Complex operator*(const Complex &a, const Complex &b) {
    Complex c = Complex(a.real * b.real - a.imag * b.imag,
                        a.real * b.imag + a.imag * b.real);

    return c;
}

Complex operator/(const Complex &a, const double &b) {
    Complex c = Complex(a.real / b, a.imag / b);

    return c;
}

Complex my_exp(const double &x) {
    return Complex(cos(x), sin(x));
}

static Complex wtable[NMAX + 10];
static Complex iwtable[NMAX + 10];

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
        Complex wn = reversed ? iwtable[s] : wtable[s];

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

static int n, m, q;
static int a[NMAX + 10];
static int b[NMAX + 10];
static u32 ans[NMAX + 10];
static Complex A[NMAX + 10];
static Complex B[NMAX + 10];

void solve1(int l, int r) {
    if (r <= l)
        return;

    int mid = (l + r) / 2;
    solve1(l, mid);
    solve1(mid + 1, r);

    int k = next_pow(r - l + 1);
    // printf("k = %d\n", k);
    memset(A, 0, sizeof(Complex) * k);
    memset(B, 0, sizeof(Complex) * k);

    for (int i = l; i <= mid; i++) {
        A[i - l].real = a[i];
    }

    for (int i = mid + 1; i <= r; i++) {
        B[i - mid - 1].real = b[i];
    }

    fft(A, k, false);
    fft(B, k, false);

    for (int i = 0; i < k; i++) {
        A[i] *= B[i];
    }

    fft(A, k, true);

    for (int i = 0; i < k; i++) {
        ans[i + mid + l + 1] += A[i].real + 0.5;
    }
}

void solve2() {
    for (int i = 0; i <= CMAX / 2; i++) {
        swap(a[i], a[CMAX - i]);
    }

    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    for (int i = 0; i <= CMAX; i++) {
        A[i].real = a[i];
        B[i].real = b[i];
    }

    int k = NMAX;
    fft(A, k, false);
    fft(B, k, false);

    for (int i = 0; i < k; i++) {
        A[i] *= B[i];
    }

    fft(A, k, true);

    for (int i = 0; i <= CMAX; i++) {
        ans[CMAX - i] += A[i].real + 0.5;
    }
}

void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    memset(a, 0, sizeof(int) * (CMAX + 10));
    memset(b, 0, sizeof(int) * (CMAX + 10));
    memset(ans, 0, sizeof(ans));
    int v;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v);
        a[v]++;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &v);
        b[v]++;
    }

    solve1(0, CMAX);
    solve2();
}

int main() {
    for (int s = 2; s <= NMAX; s <<= 1) {
        wtable[s] = my_exp(2 * M_PI / s);
        iwtable[s] = my_exp(-2 * M_PI / s);
    }

    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        while (q--) {
            int c;
            scanf("%d", &c);
            printf("%u\n", ans[c]);
        }
    }

    return 0;
}
