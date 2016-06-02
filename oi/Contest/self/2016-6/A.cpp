#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

static bool dfs(int n, double a, double b, double c, double d) {
    if (n == 1)
        if (a == 24.0)
            return true;

    if (n == 4) {
        if (dfs(3, a + b, c, d, 0))
            return true;
        if (dfs(3, a + c, b, d, 0))
            return true;
        if (dfs(3, a + d, c, b, 0))
            return true;
        if (dfs(3, b + c, a, d, 0))
            return true;
        if (dfs(3, b + d, a, c, 0))
            return true;
        if (dfs(3, c + d, a, b, 0))
            return true;

        if (dfs(3, a - b, c, d, 0))
            return true;
        if (dfs(3, a - c, b, d, 0))
            return true;
        if (dfs(3, a - d, c, b, 0))
            return true;
        if (dfs(3, b - c, a, d, 0))
            return true;
        if (dfs(3, b - d, a, c, 0))
            return true;
        if (dfs(3, c - d, a, b, 0))
            return true;
        if (dfs(3, b - a, c, d, 0))
            return true;
        if (dfs(3, c - a, b, d, 0))
            return true;
        if (dfs(3, d - a, c, b, 0))
            return true;
        if (dfs(3, c - b, a, d, 0))
            return true;
        if (dfs(3, d - b, a, c, 0))
            return true;
        if (dfs(3, d - c, a, b, 0))
            return true;

        if (dfs(3, a * b, c, d, 0))
            return true;
        if (dfs(3, a * c, b, d, 0))
            return true;
        if (dfs(3, a * d, c, b, 0))
            return true;
        if (dfs(3, b * c, a, d, 0))
            return true;
        if (dfs(3, b * d, a, c, 0))
            return true;
        if (dfs(3, c * d, a, b, 0))
            return true;

        if (b != 0.0 && dfs(3, a / b, c, d, 0))
            return true;
        if (c != 0.0 && dfs(3, a / c, b, d, 0))
            return true;
        if (d != 0.0 && dfs(3, a / d, c, b, 0))
            return true;
        if (c != 0.0 && dfs(3, b / c, a, d, 0))
            return true;
        if (d != 0.0 && dfs(3, b / d, a, c, 0))
            return true;
        if (d != 0.0 && dfs(3, c / d, a, b, 0))
            return true;
        if (a != 0.0 && dfs(3, b / a, c, d, 0))
            return true;
        if (a != 0.0 && dfs(3, c / a, b, d, 0))
            return true;
        if (a != 0.0 && dfs(3, d / a, c, b, 0))
            return true;
        if (b != 0.0 && dfs(3, c / b, a, d, 0))
            return true;
        if (b != 0.0 && dfs(3, d / b, a, c, 0))
            return true;
        if (c != 0.0 && dfs(3, d / c, a, b, 0))
            return true;
    } else if (n == 3) {
        if (dfs(2, a + b, c, 0, 0))
            return true;
        if (dfs(2, a + c, b, 0, 0))
            return true;
        if (dfs(2, b + c, a, 0, 0))
            return true;

        if (dfs(2, a - b, c, 0, 0))
            return true;
        if (dfs(2, a - c, b, 0, 0))
            return true;
        if (dfs(2, b - c, a, 0, 0))
            return true;
        if (dfs(2, b - a, c, 0, 0))
            return true;
        if (dfs(2, c - a, b, 0, 0))
            return true;
        if (dfs(2, c - b, a, 0, 0))
            return true;

        if (dfs(2, a * b, c, 0, 0))
            return true;
        if (dfs(2, a * c, b, 0, 0))
            return true;
        if (dfs(2, b * c, a, 0, 0))
            return true;

        if (b != 0.0 && dfs(2, a / b, c, 0, 0))
            return true;
        if (c != 0.0 && dfs(2, a / c, b, 0, 0))
            return true;
        if (c != 0.0 && dfs(2, b / c, a, 0, 0))
            return true;
        if (a != 0.0 && dfs(2, b / a, c, 0, 0))
            return true;
        if (a != 0.0 && dfs(2, c / a, b, 0, 0))
            return true;
        if (b != 0.0 && dfs(2, c / b, a, 0, 0))
            return true;
    } else if (n == 2) {
        if (dfs(1, a + b, 0, 0, 0))
            return true;

        if (dfs(1, a - b, 0, 0, 0))
            return true;
        if (dfs(1, b - a, 0, 0, 0))
            return true;

        if (dfs(1, a * b, 0, 0, 0))
            return true;

        if (b != 0.0 && dfs(1, a / b, 0, 0, 0))
            return true;
        if (a != 0.0 && dfs(1, b / a, 0, 0, 0))
            return true;
    }

    return false;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        double a, b, c, d;
        scanf("%lf%lf%lf%lf", &a, &b, &c, &d);

        puts(dfs(4, a, b, c, d) ? "Yes" : "No");
    }  // for

    return 0;
}  // function main
