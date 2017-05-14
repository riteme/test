#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000

static int n;
static char a[NMAX + 10], b[NMAX + 10], c[NMAX + 10];

int main() {
    scanf("%s%s", a, b);
    n = strlen(a);
    sort(a, a + n);
    sort(b, b + n);

    int h1 = 0, t1 = n / 2 + ((n & 1) ? 0 : -1);
    int h2 = n - n / 2, t2 = n - 1;
    int i = 0, j = n - 1;
    for (int p = 0; p < n / 2; p++) {
        if (a[h1] >= b[t2])
            c[j--] = a[t1--];
        else
            c[i++] = a[h1++];

        if (b[t2] <= a[h1])
            c[j--] = b[h2++];
        else
            c[i++] = b[t2--];
    }  // for

    if (n & 1)
        c[i] = a[h1];

    printf("%s\n", c);

    return 0;
}  // function main
