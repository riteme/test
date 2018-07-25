#define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At #%d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#define DEBUG(message, ...) printf(message, __VA_ARGS__);
#else
#define TRACE
#define DEBUG
#endif  // IFNDEF NDEBGU

#define NMAX 1000
#define INVALID 0
#define VALID 1

typedef long long int64;

static int n, m;
static int64 f[NMAX + 10][NMAX + 10];
static char data[NMAX + 10][NMAX + 10];
static char buffer[NMAX + 10];
static vector<int> lines[NMAX + 10];
static vector<int> columns[NMAX + 10];
static int lptr[NMAX + 10];
static int cptr[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%s", buffer + 1);

        for (int j = 1; j <= m; j++) {
            data[i][j] = buffer[j] == '0' ? INVALID : VALID;
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int64 area = (i * j) * (i * j);
            f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + area;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (data[i][j] == VALID && data[i][j + 1] == INVALID)
                lines[i].push_back(j);
        }  // for
    }      // for

    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (data[i][j] == VALID && data[i + 1][j] == INVALID)
                columns[j].push_back(i);
        }  // for
    }      // for
}

int main() {
    // freopen("santiago.in", "r", stdin);
    // freopen("santiago.out", "w", stdout);
    initialize();

    int64 answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (data[i][j] == VALID) {
                DEBUG("i = %d, j = %d\n", i, j);
                assert(lptr[i] < lines[i].size());
                assert(cptr[j] < columns[j].size());

                int right = lines[i][lptr[i]];
                int bottom = columns[j][cptr[j]];
                DEBUG("right = %d, bottom = %d\n", right, bottom);

                DEBUG("+ %lld\n", f[right - j + 1][bottom - i + 1]);
                answer += f[right - j + 1][bottom - i + 1];
            }

            if (lptr[i] + 1 < lines[i].size() && j >= lines[i][lptr[i]])
                lptr[i]++;
            if (cptr[j] + 1 < columns[j].size() && i >= columns[j][cptr[j]])
                cptr[j]++;
        }  // for
    }      // for

    printf("%lld\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
