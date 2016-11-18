#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long int64;

static int n, m;
static int64 h[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];

static bool test(int64 x) {
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    int i = 1;
    for (int p = 1; p <= n; p++) {
        assert(i >= p);

        while (i <= n && h[i] < x - (i - p))
            i++;

        if (i <= n)
            right[p] = i;
    }
    
    i = n;
    for (int p = n; p >= 1; p--) {
        assert(i <= p);

        while (i >= 1 && h[i] < x - (p - i))
            i--;

        if (i >= 1)
            left[p] = i;
    }

    int64 sum = 0;
    int p = 1;

    while (p <= n && left[p] == 0)
        p++;
    
    if (right[p]) {
        for (int i = left[p] + 1; i <= right[p] - 1; i++) {
            if (i == p)
                sum += x - h[i] - 1;
            else
                sum += x - abs(p - i) - h[i];
        }

        if (sum + 1 <= m)
            return true;

        p++;
    }

    for (; p <= n; p++) {
        assert(left[p]);
        if (right[p] == 0)
            break;

        for (int i = left[p - 1] + 1; i <= left[p]; i++) {
            if (p - 1 == i)
                sum -= x - 1 - abs(p - 1 - i) - h[i];
            else
                sum -= x - abs(p - 1 - i) - h[i];
        }

        for (int i = right[p - 1]; i < right[p]; i++) {
            sum += x - abs(p - 1 - i) - h[i];
        }

        if (left[p] < p - 1)
            sum -= p - 1 - left[p] - 1;
        sum += right[p] - p - 1;

        if (sum + 1 <= m)
            return true;
    }

    return false;
}

int main() {
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%lld", h + i);
    
    int64 left = 0, right = 2000000000;

    for (int i = 1; i <= n; i++)
        left = max(left, h[i]);

    while (left + 1 < right) {
        int64 mid = (left + right) / 2;

        if (test(mid))
            left = mid;
        else
            right = mid;
    }

    if (left != right && test(right))
        left = right;

    printf("%lld\n", left);

    return 0;
}
