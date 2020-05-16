#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500

typedef long long i64;

int n;
i64 w[NMAX + 10][NMAX + 10];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", w[i] + j);

        i64 ans = w[0][n - 1];
        for (int i = 1; i < n - 1; i++)
            ans = min(ans, w[0][i] + w[i][n - 1]);

        printf("%lld\n", ans);
    }
    return 0;
}