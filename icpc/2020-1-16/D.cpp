#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define A "Monocarp"
#define B "Bicarp"

int n;
char s[NMAX + 10];

int main() {
    scanf("%d%s", &n, s);
    int a = 0, b = 0, ac = 0, bc = 0;
    for (int i = 0; i < n / 2; i++) {
        a += s[i] == '?' ? 0 : s[i] - '0';
        ac += s[i] == '?';
    }
    for (int i = n / 2; i < n; i++) {
        b += s[i] == '?' ? 0 : s[i] - '0';
        bc += s[i] == '?';
    }

    if (ac == bc)
        puts(a == b ? B : A);
    else {
        int d = abs(ac - bc) / 2;
        if ((ac > bc && a + d * 9 != b) ||
            (bc > ac && b + d * 9 != a))
            puts(A);
        else puts(B);
    }

    return 0;
}