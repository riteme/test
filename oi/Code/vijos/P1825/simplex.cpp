// #define NDEBUG

#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 10000
#define EPS 1e-9
#define INF 1e100

class Simplex {
 public:
    Simplex(int _n, int _m) : n(_n), m(_m) {
        memset(A, 0, sizeof(A));
    }

    void append(int x, int l, int r, double w) {
        for (int i = m + l; i <= m + r; i++) {
            A[i][x] = 1;
        }

        A[0][x] = -w;
    }

    void set_min(int x, double minv) {
        A[m + x][0] = -minv;
    }

    double solve() {
        srand(time(0));

        while (true) {
            int x = 0, y = 0;
            for (int i = 1; i <= n; i++) {
                if (B[i] && A[i][0] < -EPS && (!y || (rand() & 1)))
                    y = i;
            }

            if (!y)
                break;

            for (int i = 1; i <= n; i++) {
                if (A[y][i] > EPS && (!x || (rand() & 1)))
                    x = i;
            }

            assert(x);
            pivot(x, y);
        }

        while (true) {
            double k = INF;
            int x, y;
            for (x = 1; x <= n; x++) {
                if (!B[x] && A[0][x] > EPS)
                    break;
            }

            if (x > n)
                break;

            for (int i = 1; i <= n; i++) {
                if (!B[i])
                    continue;

                double d = A[i][x] > -EPS ? INF : -A[i][0] / A[i][x];
                if (d < k) {
                    k = d;
                    y = i;
                }
            }

            assert(k < INF);
            pivot(x, y);
        }

        return A[0][0];
    }

 private:
    void pivot(int x, int y) {
        double r = -A[y][x];
        A[y][x] = -1;

        for (int i = 0; i <= m; i++) {
            A[y][i] /= r;
        }

        for (int i = 0; i <= n; i++) {
            if (i == x)
                continue;

            r = A[i][x];
            A[i][x] = 0;
            for (int j = 0; j <= m; j++) {
                A[i][j] += A[i][x] * A[y][j];
            }
        }
    }

    int n, m;
    double A[NMAX + 10][NMAX + 10];
};

static Simplex *solver;

void initialize() {
    int n, m;
    scanf("%d%d", &n, &m);
    solver = new Simplex(m, n);

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        solver->set_min(i, a);
    }

    for (int i = 1; i <= m; i++) {
        int l, r, w;
        scanf("%d%d%d", &l, &r, &w);
        solver->append(i, l, r, w);
    }
}

int main() {
    initialize();
    int ans = round(solver->solve());
    printf("%d\n", ans);

    return 0;
}
