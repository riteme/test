#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1100000

typedef long long i64;

static int n;
static char S[NMAX + 10];
static int cnt[NMAX + 10];

void initialize() {
    scanf("%s", S + 1);
    n = strlen(S + 1);
}

i64 solve(int l, int r) {
    if (l >= r)
        return 0;

    int m = (l + r) >> 1;
    i64 ret = solve(l, m) + solve(m + 1, r);

    int lcnt = 0, rcnt = 0;
    for (int i = m + 1; i <= r; i++) {
        if (S[i] == ')') {
            if (lcnt)
                lcnt--;
            else
                rcnt++;
        } else
            lcnt++;

        if (!lcnt)
            cnt[rcnt]++;
    }

    lcnt = rcnt = 0;
    for (int i = m; i >= l; i--) {
        if (S[i] == '(') {
            if (rcnt)
                rcnt--;
            else
                lcnt++;
        } else
            rcnt++;

        if (!rcnt)
            ret += cnt[lcnt];
    }

    lcnt = rcnt = 0;
    for (int i = m + 1; i <= r; i++) {
        if (S[i] == ')') {
            if (lcnt)
                lcnt--;
            else
                rcnt++;
        } else
            lcnt++;

        cnt[rcnt] = 0;
    }

    return ret;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        initialize();
        printf("%lld\n", solve(1, n));
    }

    return 0;
}
