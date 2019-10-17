#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define pi 3.141592653589793
#define EPS 1e-9

bool eq(double x, double y) {
    return fabs(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0), z(0) {}
    vec(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    double x, y, z;

    double len() const {
        return sqrt(x * x + y * y + z * z);
    }

    vec operator+(const vec &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    vec operator-(const vec &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    bool operator==(const vec &v) const {
        return eq(x, v.x) && eq(y, v.y) && eq(z, v.z);
    }
};

double dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        vec O, S, T;
        double R;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
            &O.x, &O.y, &O.z, &R,
            &S.x, &S.y, &S.z, &T.x, &T.y, &T.z);
        if (S == T) puts("0.0");
        else {
            double D1 = (O - S).len(), D2 = (O - T).len(), D = (T - S).len();
            double s = dot(O - S, T - S) / D;
            double d = sqrt(D1 * D1 - s * s);
            if (dot(O - S, T - S) <= -EPS || dot(O - T, S - T) <= -EPS ||
                d >= R - EPS)
                printf("%.12lf\n", D);
            else {
                double a = acos(max(-1.0, min(1.0, dot(S - O, T - O) / D1 / D2)));
                double b1 = acos(max(-1.0, min(1.0, R / D1)));
                double b2 = acos(max(-1.0, min(1.0, R / D2)));
                double y = a - b1 - b2;
                double L = sqrt(D1 * D1 - R * R) + sqrt(D2 * D2 - R * R) + y * R;
                printf("%.12lf\n", L);
            }
        }
    }
    return 0;
}
