#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n;
static i64 len[256];
static char str[NMAX + 10];

void eval() {
    char last;
    i64 i, c;
    for (i = 0, c = 0; str[i]; i++) {
        if (!c) {
            last = str[i];
            c = 1;
        } else {
            if (str[i] == last) c++;
            else {
                len[last] = max(len[last], c);
                c = 1;
                last = str[i];
            }
        }
    }
    len[last] = max(len[last], c);
}

int main() {
    scanf("%d", &n);
    scanf("%s", str);
    eval();
    n--;
    while (n--) {
        scanf("%s", str);
        i64 A, B;
        for (A = 0; str[A] == str[0]; A++) ;
        if (!str[A]) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == str[0]) len[c] += (len[c] + 1) * A;
                else len[c] = len[c] ? 1 : 0;
            }
        } else {
            i64 L = strlen(str);
            for (B = 0; B < L && str[L - B - 1] == str[L - 1]; B++) ;
            for (char c = 'a'; c <= 'z'; c++) {
                if (str[0] == str[L - 1] && c == str[0] && len[c]) len[c] = A + B + 1;
                else if (c == str[0]) len[c] = A + (len[c] > 0);
                else if (c == str[L - 1]) len[c] = B + (len[c] > 0);
                else len[c] = len[c] ? 1 : 0;
            }
        }
        for (char c = 'a'; c <= 'z'; c++)
            if (len[c] > 1000000001) len[c] = 1000000001;
        eval();
    }
    i64 ans = 0;
    for (char c = 'a'; c <= 'z'; c++) ans = max(ans, len[c]);
    printf("%lld\n", ans);
    return 0;
}
