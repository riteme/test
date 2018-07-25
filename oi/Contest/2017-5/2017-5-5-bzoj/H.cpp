#include <cmath>
#include <cstdio>

#include <algorithm>

using namespace std;

inline double len(double a, double b) {
    return sqrt(a * a + b * b);
}

int main() {
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);

    double ans[] = {
        len(a, b),     len(a, c),
        len(b, c),     min(len(a + b, c), min(len(a + c, b), len(b + c, a))),
        c + min(a, b), b + min(a, c),
        a + min(b, c)};

    printf("%.15lf\n", *max_element(ans, ans + 7));

    return 0;
}  // function main
