#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 1000

static int64 n;
static int zero_x, zero_y;
static int64 answer;
static int64 target_sum;
static int64 matrix[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%I64d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%I64d", &matrix[i][j]);

            if (matrix[i][j] == 0) {
                zero_x = i;
                zero_y = j;
            }
        }  // for
    }      // for
}

static bool check() {
    for (int i = 1; i <= n; i++) {
        int64 sum = 0;
        for (int j = 1; j <= n; j++) {
            sum += matrix[i][j];
        }  // for

        if (sum != target_sum)
            return false;
    }  // for

    for (int i = 1; i <= n; i++) {
        int64 sum = 0;
        for (int j = 1; j <= n; j++) {
            sum += matrix[j][i];
        }  // for

        if (sum != target_sum) {
            return false;
        }
    }  // for

    int64 sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += matrix[i][i];
    }  // for

    if (sum != target_sum)
        return false;

    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += matrix[i][n - i + 1];
    }  // for

    if (sum != target_sum) {
        return false;
    }

    return true;
}

int main() {
    initialize();

    if (n == 1) {
        puts("10086");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (i != zero_x) {
            for (int j = 1; j <= n; j++) {
                target_sum += matrix[i][j];
            }  // for
            break;
        }
    }  // for

    int64 zero_sum = 0;
    for (int i = 1; i <= n; i++) {
        zero_sum += matrix[zero_x][i];
    }  // for

    answer = target_sum - zero_sum;

    if (answer < 1 || answer > 1000000000000000000L) {
        puts("-1");
        return 0;
    }

    matrix[zero_x][zero_y] = answer;

    printf("%I64d", check() ? answer : -1L);

    return 0;
}  // function main
