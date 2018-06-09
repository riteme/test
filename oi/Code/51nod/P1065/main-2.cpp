// See OI-notes

#include <cstdio>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

#define chkmin(a, b) if (a > b) a = b;
#define chkmax(a, b) if (a < b) a = b;

typedef long long i64;

static int n;
static struct Prefix {
    i64 sum;
    int l, r;

    bool operator<(const Prefix &b) const {
        return sum < b.sum;
    }
} seq[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &seq[i].sum);
        seq[i].sum += seq[i - 1].sum;
        seq[i].l = i;
    }

    sort(seq, seq + n + 1);

    int p = 0;
    for (int i = 0; i <= n; i++) {
        if (seq[i].sum != seq[p].sum) {
            seq[++p] = seq[i];
        }

        chkmin(seq[p].l, seq[i].l);
        chkmax(seq[p].r, seq[i].l);
    }

    i64 ans = LLONG_MAX;
    for (int i = 1; i <= p; i++) {
        if (seq[i - 1].l < seq[i].r)
            ans = min(ans, seq[i].sum - seq[i - 1].sum);
    }

    printf("%lld\n", ans);
    return 0;
}
