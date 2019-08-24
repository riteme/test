#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n;
static i64 seq[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        seq[i] += seq[i - 1];
    }

    i64 ans = LLONG_MAX;
    set<i64> q;
    q.insert(0);
    for (int i = 1; i <= n; i++) {
        i64 v = seq[i] + *q.upper_bound(-seq[i]);
        if (v > 0)
            ans = min(ans, v);
        q.insert(-seq[i]);
    }

    printf("%lld", ans);
    return 0;
}
