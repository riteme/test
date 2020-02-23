#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, K;
int h[NMAX + 10];
int f[NMAX + 10];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
        scanf("%d", h + i);

    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = i - 1; j >= 1 && h[i] - h[j] <= K; j--)
            f[i] = max(f[i], f[j] + 1);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}