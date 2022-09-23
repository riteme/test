#include <cstdio>

int main() {
    int n;
    double ans = 0.0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        double r;
        scanf("%lf", &r);
        ans += r * r;
    }
    printf("%.12lf\n", ans / 2);
    return 0;
}