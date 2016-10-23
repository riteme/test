#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

#define EPSILON 0.000001
template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

#define NMAX 29

static int n;
static int initial[NMAX + 10];
static int target[NMAX + 10];
static double A[NMAX + 10][NMAX + 10];
static double x[NMAX + 10];
static double y[NMAX + 10];

static void initialize() {
    memset(A, 0, sizeof(A));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(initial, 0, sizeof(initial));
    memset(target, 0, sizeof(target));

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", initial + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", target + i);
    for (int i = 1; i <= n; i++)
        A[i][i] = 1.0;
    for (int i = 1; i <= n; i++)
        x[i] = (initial[i] != target[i]);

    int u, v;
    while (scanf("%d%d", &u, &v)) {
        if (u == 0)
            break;

        A[v][u] = 1.0;
    }  // while
}

static bool test(int line) {
    bool flag = true;
    for (int i = 1; i <= n && flag; i++)
        if (!almost_equal(A[line][i], 0.0))
            flag = false;

    if (flag && !almost_equal(x[line], 0.0))
        return false;
    return true;
}

static int gauss() {
    int line = 1, pivot = 1;
    int freeman = 0;

    while (line <= n && pivot <= n) {
        int next = line;
        for (int i = line + 1; i <= n; i++)
            if (fabs(A[i][pivot]) > fabs(A[next][pivot]))
                next = i;

        if (almost_equal(A[next][pivot], 0.0)) {
            if (!test(line))
                return -1;

            freeman++;
        } else {
            for (int i = pivot; i <= n; i++)
                swap(A[next][i], A[line][i]);
            swap(x[next], x[line]);

            for (int i = line + 1; i <= n; i++) {
                double ratio = A[i][pivot] / A[line][pivot];

                for (int j = pivot; j <= n; j++)
                    A[i][j] -= ratio * A[line][j];
                x[i] -= ratio * x[line];
            }  // for

            line++;
        }

        pivot++;
    }  // while

    for (int i = line + 1; i <= n; i++)
        if (!test(i))
            return -1;

    if (freeman > 0)
        return freeman;

    pivot = n;
    while (pivot > 0) {
        y[pivot] = x[pivot] / A[pivot][pivot];

        if (!almost_equal(y[pivot], round(y[pivot])))
            return -1;

        for (int i = 1; i < pivot; i++)
            x[i] -= A[i][pivot] * y[pivot];

        pivot--;
    }  // while

    return 0;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();
        int answer = gauss();

        if (answer < 0)
            printf("Oh,it's impossible~!!\n");
        else
            printf("%d\n", 1 << answer);
    }  // while

    return 0;
}  // function main
