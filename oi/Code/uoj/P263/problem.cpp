#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000

typedef long long int64;

static int64 t, k;
static int64 c[NMAX + 10][NMAX + 10];
static int64 answer[NMAX + 10][NMAX + 10];

int main() {
    scanf("%lld%lld", &t, &k);

    for (int i = 0; i <= NMAX; i++)
        c[i][0] = c[i][i] = 1;

    for (int i = 1; i <= NMAX; i++) {
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;

            if (!c[i][j])
                answer[i][j] = 1;
        }
    }

    for (int i = 1; i <= NMAX; i++)
        for (int j = 1; j <= NMAX; j++)
            answer[i][j] += answer[i - 1][j] + answer[i][j - 1] - answer[i - 1][j - 1];

    while (t--) {
        int64 n, m;
        scanf("%lld%lld", &n, &m);

        printf("%lld\n", answer[n][m]);
    }

    return 0;
}
