#include <cstdio>
#include <cmath>

#include <algorithm>

using namespace std;

#define EPSILON 0.0000001

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

#define NMAX 1000
#define XMIN -100001

struct Point {
    double x;
    double y;
    int a;
    int b;

    bool operator<(const Point &b) const {
        return x < b.x || (almost_equal(x, b.x) && y < b.y);
    }
};

static int n, q;
static double A[NMAX + 10];
static double B[NMAX + 10];
static double C[NMAX + 10];
static int pcnt;
static Point P[NMAX * NMAX + 100];
static int rnk[NMAX + 10];
static int sorted[NMAX + 10];

inline double f(int i, double x) {
    return A[i] * x * x + B[i] * x + C[i];
}

inline double df(int i, double x) {
    return 2 * A[i] * x + B[i];
}

static bool cmp(const int a, const int b) {
    return f(a, XMIN) > f(b, XMIN);
}

static void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", A + i, B + i, C + i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            double deltaA = A[i] - A[j];
            double deltaB = B[i] - B[j];
            double deltaC = C[i] - C[j];
            double delta = deltaB * deltaB - 4 * deltaA * deltaC;

            if (almost_equal(deltaA, 0.0)) {
                if (almost_equal(deltaB, 0.0))
                    continue;

                double x = -deltaC / deltaB;
                P[++pcnt] = {x, f(i, x), i, j};
                continue;
            }

            if (delta < 0)
                continue;

            double x1 = (-deltaB + sqrt(delta)) / (2 * deltaA);
            double x2 = (-deltaB - sqrt(delta)) / (2 * deltaA);

            P[++pcnt] = {x1, f(i, x1), i, j};
            if (delta > 0.0)
                P[++pcnt] = {x2, f(i, x2), i, j};
        }
    }
}

static double X[NMAX * NMAX + 100];
static int curve[NMAX * NMAX + 100];

int main() {
    freopen("function.in", "r", stdin);
    freopen("function.out", "w", stdout);
    initialize();

    sort(P + 1, P + pcnt + 1);

    int top;
    for (int i = 1; i <= n; i++)
        sorted[i] = i;
    
    sort(sorted + 1, sorted + n + 1, cmp);
    top = sorted[1];
    
    for (int i = 1; i <= n; i++) {
        rnk[sorted[i]] = i;
    }

    for (int i = 0; i <= pcnt; i++)
        X[i] = XMIN;
    curve[0] = top; 

    for (int i = 1; i <= pcnt; i++) {
        Point &p = P[i];

        if (df(p.a, p.x) > df(p.b, p.x)) {
            if (rnk[p.a] > rnk[p.b])
                swap(rnk[p.a], rnk[p.b]);
        } else {
            if (rnk[p.a] < rnk[p.b])
                swap(rnk[p.a], rnk[p.b]);
        }

        if (rnk[p.a] == 1)
            top = p.a;
        else if (rnk[p.b] == 1)
            top = p.b;

        X[i] = p.x;
        curve[i] = top;
    }

    while (q--) {
        double u;
        scanf("%lf", &u);

        int left = 0, right = pcnt;

        while (left + 1 < right) {
            int mid = (left + right) / 2;

            if (X[mid] <= u)
                left = mid;
            else
                right = mid;
        }

        if (left != right && X[right] <= u)
            left = right;

        printf("%lld\n", static_cast<long long>(f(curve[left], u)));
    }
}
