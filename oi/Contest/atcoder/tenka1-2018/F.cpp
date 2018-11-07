// Only 54 RE
#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 300000
#define MOD 998244353

static int n;
static int A[NMAX * 2 + 10], l[NMAX + 10], r[NMAX + 10], c[NMAX + 10];
static vector<int> op[NMAX + 10];

inline int nxt(int i) {
    return i < n ? i + 1 : 1;
}

inline int pre(int i) {
    return i > 1 ? i - 1 : n;
}

inline int pos(int i) {
    return i < 1 ? i + n : (i > n ? i - n : i);
}

inline i64 fac(int x) {
    i64 r = 1;
    for (; x; x--) r = r * x % MOD;
    return r;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", A + i);
    memcpy(A + n + 1, A + 1, sizeof(int) * n);
    if (all_of(A + 1, A + n + 1, [](int x) { return x == A[1]; }))
        printf("%lld\n",
            all_of(A + 1, A + n + 1, [](int x) { return x == 1; }) ? fac(n) : 0);
    else {
        int d = 0, s = 1;
        i64 ans = 1, cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (i == 1 && A[1] == A[n]) {
                while (A[i + 1] == A[1]) i++;
                s = i + 1;
                continue;
            }
            if (l[A[i]]) ans = 0;
            l[A[i]] = i;
            for (r[A[i]] = i; A[r[A[i]] + 1] == A[i]; r[A[i]]++) ;
            if (A[i] == 1) d = r[A[i]] - l[A[i]] + 1;
            i = r[A[i]];
        }

        for (int i = 1; i <= n; i++) {
            if (!l[i]) continue;
            int pl = l[i] - d + 1;
            if (pl < 1) {
                op[1].push_back(i);
                op[pos(r[i]) + 1].push_back(-i);
                op[pos(pl)].push_back(i);
            } else if (r[i] > n) {
                op[1].push_back(i);
                op[pos(r[i]) + 1].push_back(-i);
                op[pos(pl)].push_back(i);
            } else {
                op[pos(pl)].push_back(i);
                op[pos(r[i]) + 1].push_back(-i);
            }
        }
        set<int> q;
        for (int i = 1; i <= n; i++) {
            for (int v : op[i]) {
                if (v > 0) q.insert(v);
                else q.erase(q.find(-v));
            }
            if (!q.empty()) c[*q.rbegin()]++;
        }

        for (int i = n; i >= 1; i--) {
            if (!l[i]) {
                cnt++;
                continue;
            }
            int len = r[i] - l[i] + 1;
            if (r[i] > n) r[i] -= n;
            if (len > d) ans = 0;
            if (A[pre(l[i])] < i && A[nxt(r[i])] < i)
                ans = ans * (d - len + 1) % MOD;
            for (int j = 0; j < c[i] - 1; j++, cnt--) ans = ans * cnt % MOD;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
