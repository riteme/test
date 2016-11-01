#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 200000
#define EPSILON 0.0000001

static int n;
static double seq[NMAX + 10];

static double evaluate(double x) {
    double answer = 0.0;
    double f = 0.0;
    for (int i = 1; i <= n; i++) {
        f += seq[i] - x;

        if (f < 0)
            f = 0;

        answer = max(answer, f);
    }

    f = 0.0;
    for (int i = 1; i <= n; i++) {
        f -= (seq[i] - x);

        if (f < 0)
            f = 0;

        answer = max(answer, f);
    }

    return answer;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", seq + i);
}

int main() {
    freopen("weakness.in", "r", stdin);
    freopen("weakness.out", "w", stdout);
    initialize();

    double left = -10001, right = 10001;
    double leftans = evaluate(-10001), rightans = evaluate(10001);
    while (fabs(leftans - rightans) > EPSILON) {
        double lmid = left + (right - left) / 3;
        double rmid = lmid + (right - left) / 3;
        double lans = evaluate(lmid);
        double rans = evaluate(rmid);

        if (lans > rans) {
            left = lmid;
            leftans = lans;
        } else {
            right = rmid;
            rightans = rans;
        }
    }

    printf("%.6lf\n", evaluate((left + right) / 2));

    fclose(stdin);
    fclose(stdout);
    return 0;
}
