#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define T 50

int n, L;
int X[NMAX + 10], B[NMAX + 10];
double w[NMAX + 10][NMAX + 10];
double f[NMAX + 10];
int p[NMAX + 10];

void print(int i) {
    if (!i) return;
    print(p[i]);
    printf("%d ", i);
}

int main() {
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", X + i, B + i);
    for (int i = 0; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
        w[i][j] = w[j][i] = sqrt(abs(X[j] - X[i] - L));

    double l = 0, r = 1e6;
    for (int _t = 0; _t < T; _t++) {
        double K = (l + r) * 0.5;
        for (int i = 1; i <= n; i++) {
            f[i] = 1e99;
            for (int j = 0; j < i; j++) {
                double val = f[j] + w[j][i] - K * B[i];
                if (val < f[i]) {
                    f[i] = val;
                    p[i] = j;
                }
            }
        }

        if (f[n] <= 0) r = K;
        else l = K;
    }

    print(n);
    puts("");

    return 0;
}