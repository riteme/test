#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000

typedef long long int64;

static int n;
static int seq[NMAX + 10];
static int sorted[NMAX + 10];
static int64 before[NMAX + 10];
static int64 after[NMAX + 10];
static int64 fenwick[NMAX + 10];

inline void modify(int x, int64 v) {
    for (; x <= n; x += x & (-x))
        fenwick[x] += v;
}

inline int64 query(int r) {
    int64 answer = 0;

    for (; r; r -= r & (-r))
        answer += fenwick[r];

    return answer;
}

bool cmp(const int a, const int b) {
    return seq[a] < seq[b];
}

int main() {
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        sorted[i] = i;
    }

    sort(sorted + 1, sorted + n + 1, cmp);

    for (int i = 1; i <= n; i++)
        seq[sorted[i]] = i;

    for (int i = 1; i <= n; i++) {
        before[i] = query(seq[i]);
        modify(seq[i], 1);
    }

    memset(fenwick, 0, sizeof(fenwick));
    for (int i = n; i >= 1; i--) {
        after[i] = query(n - seq[i] + 1);
        modify(n - seq[i] + 1, 1);
    }

    int64 answer = 0;
    for (int i = 1; i <= n; i++)
        answer += before[i] * after[i];

    printf("%lld\n", answer);
}
