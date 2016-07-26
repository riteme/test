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
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", p + i);

    int *current = b, *last = a;
    for (int64 j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++)
            current[i] = last[p[i]];

        swap(current, last);
    }  // for

    for (int i = 1; i <= n; i++)
        printf("%d ", last[i]);

    return 0;
}  // function main
