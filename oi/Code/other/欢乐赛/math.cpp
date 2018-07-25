#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

static double *w;

int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);

    int n;
    scanf("%d", &n);

    w = new double[n + 1];
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        int tmp;
        scanf("%d", &tmp);

        w[i] = double(tmp);
        sum += 1.0 / w[i];
    }

    double result = 0.0;
    for (int i = 1; i <= n; i++) {
        double x = ((1.0 / w[i]) / sum) * n;
        result += w[i] * (x * x);
    }

    printf("%.4f", result);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
