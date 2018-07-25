#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

#define NMAX 1000

static int x[NMAX + 10];
static int y[NMAX + 10];
static int count[NMAX + 10];
static int bucket[NMAX + 10];
static int sorted[NMAX + 10];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", x + i, y + i);
        sorted[i] = i;
    }  // for

    for (int i = 1; i <= n; i++)
        count[y[i]]++;
    for (int i = 1; i <= n; i++)
        count[i] += count[i - 1];
    for (int i = n; i >= 1; i--) {
        bucket[count[y[i]]] = i;
        count[y[i]]--;
    }
    for (int i = 1; i <= n; i++)
        sorted[i] = bucket[i];

    putchar('\n');
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", x[sorted[i]], y[sorted[i]]);
    }  // for

    for (int i = 1; i <= n; i++)
        count[i] = 0;
    for (int i = 1; i <= n; i++)
        count[x[sorted[i]]]++;
    for (int i = 1; i <= n; i++)
        count[i] += count[i - 1];
    for (int i = n; i >= 1; i--) {
        bucket[count[x[sorted[i]]]] = sorted[i];
        count[x[sorted[i]]]--;
    }
    for (int i = 1; i <= n; i++)
        sorted[i] = bucket[i];

    putchar('\n');
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", x[sorted[i]], y[sorted[i]]);
    }  // for

    return 0;
}  // function main
