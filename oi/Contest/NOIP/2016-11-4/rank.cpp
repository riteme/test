#include <cmath>
#include <cstdio>

#include <algorithm>

using namespace std;

#define EPSILON 0.000000001

inline int ceiling(double x) {
    int down = x;
    if (fabs((double) down - x) < EPSILON)
        return down;
    return down + 1;
}

int main() {
    freopen("rank.in", "r", stdin);
    freopen("rank.out", "w", stdout);

    int n, A, S;
    scanf("%d%d%d", &n, &A, &S);

    if (n * A >= S)
        printf("1 ");
    else
        printf("%d ", ceiling(((double) S - n * A) / (100.0 - A)) + 1);

    if (A == 100)
        printf("1\n");
    else
        printf("%d\n", min(n - 1, (S - A) / (A + 1)) + 1);

    return 0;
}
