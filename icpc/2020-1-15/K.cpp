#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000

typedef long long i64;

char s[NMAX + 10];

int n;
i64 p[NMAX + 10];

void mul(i64 k) {
    // printf("k = %lld\n", k);
    n++;
    for (int i = n; i; i--)
        p[i] = p[i - 1] - k * p[i];
    p[0] = -k * p[0];
}

int main() {
    scanf("%s", s + 1);
    p[0] = 1;
    int i;
    for (i = 1; s[i + 1]; i++)
        if (s[i] != s[i + 1]) mul(2 * i + 1);

    int sgn = s[i] == 'H' ? 1 : -1;
    printf("%d\n", n);
    for (int k = n; k >= 0; k--)
        printf("%lld ", p[k] * sgn);
    puts("");
    return 0;
}