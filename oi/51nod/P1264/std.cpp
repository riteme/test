#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iomanip>
#include <climits>
#include <queue>
using namespace std;

#define OJ

#ifdef OJ
typedef long long llong;
typedef unsigned long long ullong;
#define SCANF64(k) scanf("%I64d", &k)
#define PRINT64(k) printf("%I64d\n", k)
#define REOPENIN()  
#define REOPENOUT()
#else
typedef long long llong;
typedef unsigned long long ullong;
#define SCANF64(k) scanf("%lld", &k)
#define PRINT64(k) printf("%lld\n", k)
#define REOPENIN() freopen("in.txt", "r", stdin)
#define REOPENOUT() freopen("out.txt", "w", stdout)
#endif

#define SAME_SIGN(x, y) (x*y > 0)

bool intersect(double *lineA, double*lineB)
{
    //A1*x + B1*y + C1 = 0
    double A1 = lineA[3] - lineA[1];
    double B1 = lineA[0] - lineA[2];
    double C1 = lineA[2]*lineA[1] - lineA[0]*lineA[3];

    double v1 = A1*lineB[0] + B1*lineB[1] + C1;
    double v2 = A1*lineB[2] + B1*lineB[3] + C1;
    if ((v1 == 0 && v2 == 0) || SAME_SIGN(v1, v2)) {
        return false;
    }

    double A2 = lineB[3] - lineB[1];
    double B2 = lineB[0] - lineB[2];
    double C2 = lineB[2]*lineB[1] - lineB[0]*lineB[3];
    v1 = A2*lineA[0] + B2*lineA[1] + C2;
    v2 = A2*lineA[2] + B2*lineA[3] + C2;
    if (SAME_SIGN(v1, v2)) {
        return false;
    }
    return true;

}

int main ()
{
    REOPENIN();
    //REOPENOUT();

    int T;
    double coor[8];
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 8; ++i) {
            scanf("%lf", &coor[i]);
        }
        if (intersect(coor, coor+4)) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    return 0; 
}
