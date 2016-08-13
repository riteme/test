#define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

#ifndef NDEBGU
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif  // IFNDEF NDEBGU

using namespace std;

#define NMAX 1000
#define VALID 1
#define INVALID 0

static int n, m;
static char data[NMAX + 10][NMAX + 10];
static int pre[NMAX + 10][NMAX + 10];
static char buffer[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%s", buffer + 1);

        for (int j = 1; j <= m; j++) {
            data[i][j] = buffer[j] == '0' ? INVALID : VALID;

            if (data[i][j] == VALID)
                pre[i][j] = 1;
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }  // for
    }      // for
}

int main() {
    // freopen("santiago.in", "r", stdin);
    // freopen("santiago.out", "w", stdout);
    initialize();

    long long answer = 0;
    for (int w = 1; w <= n; w++) {
        for (int h = 1; h <= m; h++) {
            long long area = w * h;
            for (int i = 1; i <= n - w + 1; i++) {
                for (int j = 1; j <= m - h + 1; j++) {
                    int count = pre[i + w - 1][j + h - 1] -
                                pre[i + w - 1][j - 1] - pre[i - 1][j + h - 1] +
                                pre[i - 1][j - 1];
                    if (count == area)
                        answer += area * area;
                }  // for
            }      // for
        }          // for
    }              // for

    printf("%lld\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
