#define M_PI 3.141592653589793
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        double a, b, r, d;
        scanf("%lf%lf%lf%lf", &a, &b, &r, &d);
        double t = (180 - d) / 180.0 * M_PI;
        double x = (a + r) * cos(t) - b * sin(t);
        double y = (a + r) * sin(t) + b * cos(t);
        if (y >= 0) printf("%.12lf\n", hypot(x, y) - r);
        else printf("%.12lf\n", fabs(fabs(x) - r));
    }
    return 0;
}
