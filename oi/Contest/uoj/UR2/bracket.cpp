// #define NDEBUG

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, m;
static char s[NMAX + 10];
static struct {
    int l, r;
} op[NMAX + 10];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);

    for (int i = 1, j = 2; i <= n / 2; i++) {
        if (s[i] == '(')
            continue;

        for (j = max(i + 1, j); j <= n && s[j] != '('; j++);

        op[++m] = {i, j};
        swap(s[i], s[j]);
    }

    printf("%d\n", m);
    for (int i = 1; i <= m; i++) {
        printf("%d %d\n", op[i].l, op[i].r);
    }

    return 0;
}
