#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 30

typedef long long i64;

static int n;
static i64 K;
static i64 a[NMAX + 10];
static int lpos, rpos;
static i64 left[1000000];
static i64 right[1000000];

inline void prod(i64 &dest, i64 src) {
    if (src > K / dest)
        dest = K + 1;
    else
        dest *= src;
}

int main() {
    scanf("%d%lld", &n, &K);

    for (int i = 0; i < n; i++) {
        scanf("%lld", a + i);

        if (a[i] <= 0 || K <= 0)
            return -1;
    }

    for (int s = 0; s < (1 << n / 2); s++) {
        left[lpos] = 1;
        for (int i = 0; i < n / 2; i++) {
            if ((s >> i) & 1)
                prod(left[lpos], a[i]);
        }

        lpos++;
    }

    for (int s = 0; s < (1 << (n - n / 2)); s++) {
        right[rpos] = 1;
        for (int i = n / 2; i < n; i++) {
            if ((s >> (i - n / 2)) & 1)
                prod(right[rpos], a[i]);
        }

        rpos++;
    }

    sort(left, left + lpos);
    sort(right, right + rpos);

    int ans = 0;
    lpos--;
    for (int i = 0; i < rpos; i++) {
        i64 std = K / right[i];
        while (lpos >= 0 && left[lpos] > std)
            lpos--;

        ans += lpos + 1;
    }

    printf("%d\n", ans - 1);

    return 0;
}
