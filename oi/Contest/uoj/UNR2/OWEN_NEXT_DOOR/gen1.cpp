#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500000
#define BASE 2333

typedef unsigned long long u64;

static int n, _;
static int str[NMAX + 10];
static u64 c[NMAX + 10], rc[NMAX + 10], bin[NMAX + 10];

inline u64 h(u64 *s, int l, int r) {
    return s[r] - s[l - 1] * bin[r - l + 1];
}

inline bool par(int l, int r) {
    if (l == r)
        return true;
    int m = (l + r) / 2;
    return h(c, l, m) == h(rc, n - r + 1, n - m + ((r - l + 1) % 2 ? 1 : 0));
}

void initialize() {
    scanf("%d%d%d%d", &n, &_, &_, &_);

    for (int i = 1; i <= n; i++) {
        char buf[4];
        scanf("%s", buf);
        str[i] = buf[0] - 'a' + 1;
    }  // for

    bin[0] = 1;
    for (int i = 1; i <= n; i++) {
        c[i] = c[i - 1] * BASE + str[i];
        bin[i] = bin[i - 1] * BASE;
    }  // for

    for (int i = 1; i <= n; i++) {
        rc[i] = rc[i - 1] * BASE + str[n - i + 1];
    }  // for
}

int main() {
    initialize();

    int ans1 = 1, ans2 = 0;
    for (int i = 2; i <= n; i++) {
        if (ans1 + 2 <= i && par(i - ans1 - 1, i))
            ans1 += 2;
        if (ans2 + 2 <= i && par(i - ans2 - 1, i))
            ans2 += 2;
    }  // for

    printf("%d\n", max(ans1, ans2));

    return 0;
}  // function main
