#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define DMAX 100

static int n, d, k;
static int vec[NMAX + 10][DMAX + 10];
static int self[NMAX + 10];
static int tmp[DMAX * DMAX + 10];

inline int dot(int *A, int *B) {
    int ret = 0;

    for (int i = 1; i <= d; i++) {
        ret += A[i] * B[i];
    }

    return ret;
}

void initialize() {
    scanf("%d%d%d", &n, &d, &k);

    int v;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= d; j++) {
            scanf("%d", &v);
            vec[i][j] = v % k;
        }

        self[i] = dot(vec[i], vec[i]) % k;
    }
}

bool test2(int *X) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += X[i];
    }

    memset(tmp, 0, sizeof(int) * (d + 1));

    for (int j = 1; j <= d; j++) {
        for (int i = 1; i <= n; i++) {
            if (X[i])
                tmp[j] += vec[i][j];
        }

        tmp[j] &= 1;
    }

    for (int i = 1; i <= n; i++) {
        int v = dot(vec[i], tmp) & 1;

        if (v != ((X[i] * self[i] + cnt - X[i]) & 1)) {
            int j;
            for (j = 1; j <= n; j++) {
                if (i == j || dot(vec[i], vec[j]) & 1)
                    continue;

                if (i > j)
                    swap(i, j);
                printf("%d %d\n", i, j);
                return true;
            }

            assert(false);
        }
    }

    return false;
}

bool test3(int *X) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += X[i];
    }

    memset(tmp, 0, sizeof(int) * (d * d + 1));

    for (int a = 1; a <= d; a++) {
        for (int b = 1; b <= d; b++) {
            int p = (a - 1) * d + b;
            for (int i = 1; i <= n; i++) {
                tmp[p] += X[i] * vec[i][a] * vec[i][b];
            }

            tmp[p] %= k;
        }
    }

    for (int i = 1; i <= n; i++) {
        int v = 0;
        for (int a = 1; a <= d; a++) {
            for (int b = 1; b <= d; b++) {
                v += tmp[(a - 1) * d + b] * vec[i][a] * vec[i][b];
            }
        }

        v %= k;

        if (v != (X[i] * self[i] * self[i] + cnt - X[i]) % k) {
            int j;
            for (j = 1; j <= n; j++) {
                if (i == j || dot(vec[i], vec[j]) % k)
                    continue;

                if (i > j)
                    swap(i, j);
                printf("%d %d\n", i, j);
                return true;
            }

            assert(false);
        }
    }

    return false;
}

static int X[NMAX + 10];

int main() {
    srand(time(0));
    initialize();

    // int found = 3;
    // while (--found) {
        for (int i = 1; i < n; i++) {
            X[i] = 1;
        }

        if ((k == 2 && test2(X)) ||
            (k == 3 && test3(X)))
            return 0;
    // }

    // if (!found)
        puts("-1 -1");

    return 0;
}
