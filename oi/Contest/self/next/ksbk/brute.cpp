#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define KMAX LLONG_MAX

typedef long long int64;

static int n;
static int64 k;
static int a[NMAX + 10];
static int b[NMAX + 10];
static int p[NMAX + 10];

int main() {
    freopen("ksbk.in", "r", stdin);
    freopen("ksbk-brute.out", "w", stdout);

    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", p + i);

    int *current = b, *last = a;
    for (int64 j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++)
            current[p[i]] = last[i];

        swap(current, last);
    }  // for

    for (int i = 1; i <= n; i++)
        printf("%d ", last[i]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
