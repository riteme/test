#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static char s[NMAX + 10];
static int n, nxt[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 2, j = 0; i <= n; i++) {
            for ( ; j && s[j + 1] != s[i]; j = nxt[j]) ;
            if (s[j + 1] == s[i]) j++;
            nxt[i] = j;
        }
        int l = nxt[n];
        int p = n - l;
        //fprintf(stderr, "l = %d, p = %d\n", l, p);
        if (p == n || n % p)
            printf("%d\n", p - l % p);
        else
            puts("0");
    }
    return 0;
}
