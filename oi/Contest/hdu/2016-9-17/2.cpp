#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define NMAX 500000
#define STRLENGTH 100000

typedef long long int64;

static double table[NMAX + 10];
static char s[STRLENGTH];

int main() {
    for (int i = 1; i <= NMAX; i++) {
        table[i] = table[i - 1] + 1.0 / ((double)i * (double)i);
    }  // for

    while (scanf("%s", s) != EOF) {
        int l = strlen(s);

        if (l > 7)
            printf("%.5lf\n", table[NMAX]);
        else {
            int pos = atoi(s);
            if (pos >= NMAX)
                printf("%.5lf\n", table[NMAX]);
            else
                printf("%.5lf\n", table[pos]);
        }
    }  // while

    return 0;
}  // function main
