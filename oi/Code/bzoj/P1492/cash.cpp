#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static double S;
static double A[NMAX + 10];
static double B[NMAX + 10];
static double r[NMAX + 10];
static double f[NMAX + 10];

inline double w(double s, int a) {
    return (r[a] / (A[a] * r[a] + B[a])) * s;
}

static void initialize() {
    ios::sync_with_stdio(false);
    // scanf("%d%f", &n, &S);
    cin >> n >> S;

    for (int i = 1; i <= n; i++) {
        // scanf("%f%f%f", A + i, B + i, r + i);
        cin >> A[i] >> B[i] >> r[i];
    }  // for
}

int main() {
    initialize();

    f[1] = w(S, 1);
    double answer = S;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            double x = A[i] * f[j] + B[i] * (f[j] / r[j]);

            if (x > answer) {
                answer = x;
            }
        }  // for

        f[i] = w(answer, i);
    }  // for

    // printf("%.3lf", A[n] * f[n] + B[n] * (f[n] / r[n]));
    cout << setprecision(3) << fixed;
    cout << A[n] * f[n] + B[n] * (f[n] / r[n]);

    return 0;
}  // function main
