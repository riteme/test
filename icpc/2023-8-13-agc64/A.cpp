#include <cstdio>
#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 1000;

int cnt[NMAX + 10];
int last = 0;

void submit(int x) {
    printf("%d ", x);
    fflush(stdout);
    assert(cnt[x] > 0);
    cnt[x]--;
    if (last) {
        assert(abs(last - x) >= 1);
        assert(abs(last - x) <= 2);
    } else {
        assert(x == 1);
    }
    last = x;
}

void finalize() {
    puts("");
    assert(last <= 3);
}

int get_d(int x) {
    if (x <= 3)
        return 1;
    return cnt[x - 2] > cnt[x - 1] ? 2 : 1;
}

void solve(int n) {
    int q = 1;
    for (int i = 0; i < n * (n + 1) / 2; i++) {
        submit(q);
        int u = 0;
        for (int d = 2; d >= -2; d--) {
            if (d == 0 || q + d > n || q + d < 1 || cnt[q + d] == 0)
                continue;
            if (!u || cnt[q + d] > cnt[u])
                u = q + d;
        }
        q = u;
    }

    finalize();
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        cnt[i] = i;
    }
    solve(n);
    for (int i = 1; i <= n; i++) {
        assert(cnt[i] == 0);
    }
    return 0;
}
