#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 500;

int n, m;
int A[NMAX + 10], B[NMAX + 10];
double C[NMAX + 10];
int D[NMAX + 10], E[NMAX + 10];
int w[NMAX + 10];

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%lf%d%d%d", A + i, B + i, C + i, D + i, E + i, w + i);
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        double c;
        int d, e;
        scanf("%d%d%lf%d%d", &a, &b, &c, &d, &e);

        int minw = -1, minj;
        for (int j = 1; j <= n; j++) {
            if (A[j] >= a && B[j] >= b && C[j] >= c && D[j] >= d && E[j] >= e) {
                if (minw < 0 || w[j] < minw) {
                    minw = w[j];
                    minj = j;
                }
            }
        }

        printf("%d\n", minj);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
