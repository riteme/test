#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000 
#define EPS 1e-9

static double a[NMAX + 10], t[NMAX + 10];
static int seq[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, l;
        scanf("%d%d", &n, &l);
        double L = l * 1000;
        for (int i = 1; i <= n; i++) {
            seq[i] = i;
            scanf("%lf%lf", a + i, t + i);
            t[i] /= 1e6;
        }
        sort(seq + 1, seq + n + 1, [](int x, int y) {
            return a[x] > a[y];
        });
        double v = 0, x = 0, ct = 0;
        for (int i = 1; i <= n && x < L; i++) {
            if (a[i] < EPS) break;
            double nx = v * t[i] + 0.5*a[i]*t[i]*t[i] + x;
            if (nx > L) {
                double nt = (-v + sqrt(v*v + 2 * a[i] * (L - x))) / a[i];
                ct += nt;
                v += a[i]*nt;
                x = L;
                break;
            } else {
                x = nx;
                v += a[i] * t[i];
                ct += t[i];
            }
        }
        ct += (L - x) / v;
        printf("%.10lf\n", ct);
    }
    return 0;
}
