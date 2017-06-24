#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 5000
#define EPS 1e-9

typedef long double number;

static int n, q;
static number A, B, lastans = 0.1;
static struct Point {
    number x, y, z;
} P[NMAX + 10];

number val(number v) {
    number l = -1000, r = 1000;
    while (r - l > 1e-16) {
        number x = (l + r) * 0.5;
        number y = A * x - B * sin(x);

        if (y < v)
            l = x;
        else
            r = x;
    }

    return (l - 1) / lastans;
}

void initialize() {
    scanf("%d%d%Lf%Lf", &n, &q, &A, &B);

    for (int i = 1; i <= n; i++) {
        scanf("%Lf%Lf%Lf", &P[i].x, &P[i].y, &P[i].z);
    }
}

int main() {
    initialize();

    while (q--) {
        int type, i;
        number a, b, c, d;
        scanf("%d%Lf%Lf%Lf%Lf", &type, &a, &b, &c, &d);
        a = val(a);
        b = val(b);
        c = val(c);
        d = val(d);

        if (type == 0) {
            i = round(a);
            P[i] = {b, c, d};
        } else {
            for (i = 1; i <= n; i++) {
                Point &p = P[i];
                number s = sqrt(
                    pow(p.x - a, 2) +
                    pow(p.y - b, 2) +
                    pow(p.z - c, 2));
                
                if (fabs(s - d) < EPS)
                    break;
            }

            printf("%d\n", i);
            lastans = i;
        }
    }

    return 0;
}
