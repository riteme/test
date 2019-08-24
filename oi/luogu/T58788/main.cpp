#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000000

static int n, r[NMAX + 10], pre[NMAX + 10];
static char str[NMAX + 10];
static char ans[NMAX + 10];

inline char mex(int i) {
    char r = 0;
    for (; (pre[i] >> r) & 1; r++) ;
    return r + 'a';
}

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    str[n + 1] = '$';
    int c = 1, p = 1;
    ans[1] = 'a';
    for (int i = 2; i <= n; i++) {
        int q = i <= p ? min(p, i + r[2 * c - i]) : i;
        for (; str[q + 1] == str[2 * i - q - 1]; q++) ;
        r[i] = q - i;
        ans[i] = i <= p ? ans[c * 2 - i] : mex(i);
        pre[q + 1] |= 1 << (ans[i - r[i] - 1] - 'a');
        if (q > p) {
            p = q;
            c = i;
        }
    }
    puts(ans + 1);
    return 0;
}
