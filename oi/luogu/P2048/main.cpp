#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500000
#define LOGN 19

typedef long long i64;

int n, K, L, R;
i64 a[NMAX + 10];
int mi[LOGN][NMAX + 10], lg[NMAX + 10];

void initialize() {
    scanf("%d%d%d%d", &n, &K, &L, &R);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
        mi[0][i] = i;
    }
    for (int j = 0; j + 1 < LOGN; j++)
    for (int i = 0; i + (1 << j) <= n; i++) {
        int l = mi[j][i], r = mi[j][i + (1 << j)];
        mi[j + 1][i] = a[l] < a[r] ? l : r;
    }
}

int rmq(int l, int r) {
    int k = lg[r - l + 1];
    int i = mi[k][l], j = mi[k][r - (1 << k) + 1];
    return a[i] < a[j] ? i : j;
}

struct State {
    i64 delta;
    int l, r, p;

    i64 val() const {
        return delta - a[p];
    }

    bool operator<(const State &z) const {
        return val() < z.val();
    }
};

priority_queue<State> q;

void push(int l, int r, i64 delta) {
    if (l > r) return;
    int p = rmq(l, r);
    q.push({delta, l, r, p});
}

int main() {
    initialize();

    // range of left endpoints for right endpoint i is [i - R, i - L]
    // i = 0..n
    for (int i = L; i <= n; i++)
        push(max(0, i - R), i - L, a[i]);

    i64 ans = 0;
    while (K--) {
        auto u = q.top();
        q.pop();
        // printf("delta = %lld, [%d, %d]: %d\n", u.delta, u.l, u.r, u.p);
        ans += u.val();
        push(u.l, u.p - 1, u.delta);
        push(u.p + 1, u.r, u.delta);
    }

    printf("%lld\n", ans);
    return 0;
}