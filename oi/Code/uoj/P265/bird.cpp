#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define EPSILON 0.00000000001

typedef long double Number;

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

#define NMAX 18
#define STATEMAX 262144

static int n, m;
static int endpoint;
static Number X[NMAX + 10];
static Number Y[NMAX + 10];
static int sorted[NMAX + 10];
static int f[STATEMAX + 10];

static bool cmp(const int a, const int b) {
    return X[a] < X[b];
}

static void initialize() {
    memset(f, 0, sizeof(f));
    scanf("%d%d", &n, &m);
    endpoint = (1 << n) - 1;

    for (int i = 0; i < n; i++) {
        scanf("%Lf%Lf", X + i, Y + i);
        sorted[i] = i;
    }

    sort(sorted, sorted + n, cmp);
}

static int dfs(int state) {
    if (state == endpoint)
        return 0;

    if (f[state])
        return f[state];

    int &answer = f[state];
    answer = INT_MAX;
    for (int i = 0; i < n; i++) {
        if ((state >> i) & 1)
            continue;

        int current = state | (1 << i);
        answer = min(answer, dfs(current) + 1);

        for (int j = i + 1; j < n; j++) {
            if (((current >> j) & 1) ||
                almost_equal(X[sorted[i]], X[sorted[j]]))
                continue;

            int s = current | (1 << j);
            Number x0 = X[sorted[i]];
            Number x1 = X[sorted[j]];
            Number y0 = Y[sorted[i]];
            Number y1 = Y[sorted[j]];
            Number A = (y1 * x0 - y0 * x1) / (x0 * x1 * (x1 - x0));
            Number B = -x0 * A + y0 / x0;

            if (almost_equal(A, 0.0L) || (A > 0))
                continue;

            for (int k = 0; k < n; k++) {
                if ((s >> k) & 1)
                    continue;

                Number x = X[sorted[k]];
                Number y = Y[sorted[k]];
                if (almost_equal(A * x * x + B * x, y))
                    s |= 1 << k;
            }

            answer = min(answer, dfs(s) + 1);
        }

        break;
    }

    return answer;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        printf("%d\n", dfs(0));
    }

    return 0;
}
