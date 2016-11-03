#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long int64;

static int n, m;
static int64 S;
static int64 w[NMAX + 10];
static int64 v[NMAX + 10];
static int l[NMAX + 10];
static int r[NMAX + 10];

static void initialize() {
    scanf("%d%d%lld", &n, &m, &S);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", w + i, v + i);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", l + i, r + i);
    }
}

static int64 cnt[NMAX + 10];
static int64 vcnt[NMAX + 10];

static int64 test(int64 W, bool fake = true) {
    memset(cnt, 0, sizeof(cnt));
    memset(vcnt, 0, sizeof(vcnt));

    int64 remain = 0;
    if (fake)
        remain = S;

    for (int i = 1; i <= n; i++) {
        if (w[i] >= W) {
            cnt[i] = 1;
            vcnt[i] = v[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
        vcnt[i] += vcnt[i - 1];
    }

    for (int i = 1; i <= m; i++) {
        int64 value = (cnt[r[i]] - cnt[l[i] - 1]) * (vcnt[r[i]] - vcnt[l[i] - 1]);

        if (fake) {
            remain -= value;

            if (remain < 0)
                break;
        } else
            remain += value;
    }

    if (fake)
        return remain;
    else
        return abs(remain - S);
}

int main() {
    initialize();

    int64 left = 0, right = 1000001;
    while (left + 1 < right) {
        int64 mid = (left + right) / 2;

        if (test(mid) >= 0)
            right = mid;
        else
            left = mid;
    }

    if (left != right && test(left) < 0)
        left = right;

    int64 answer1 = test(left);
    int64 answer2 = test(left - 1, false);

    printf("%lld\n", min(answer1, answer2));

    return 0;
}
