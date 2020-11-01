#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 61717
#define NMAX 100000

typedef long long i64;

int cnt;
i64 key[NMAX + 10];
int nxt[NMAX + 10];
int head[MOD];

i64 H(i64 x) {
    return x * 0xfc1824de19260817;
}

void insert(i64 x) {
    int pos = x % MOD;
    if (pos < 0)
        pos += MOD;
    for (int i = head[pos]; i; i = nxt[i]) {
        if (key[i] == x)
            return;
    }
    key[++cnt] = x;
    nxt[cnt] = head[pos];
    head[pos] = cnt;
}

bool contain(i64 x) {
    int pos = x % MOD;
    if (pos < 0)
        pos += MOD;
    for (int i = head[pos]; i; i = nxt[i]) {
        if (key[i] == x)
            return true;
    }
    return false;
}

int n;
i64 a[6][300];

void _main() {
    scanf("%d", &n);
    cnt = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= 5; i++)
    for (int j = 1; j <= n; j++) {
        scanf("%lld", a[i] + j);
    }

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        insert(-(a[1][i] + a[2][j]));
    }

    bool ok = false;
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
    for (int k = 1; k <= n; k++) {
        if (contain(a[3][i] + a[4][j] + a[5][k])) {
            ok = true;
            goto aha;
        }
    }

aha:
    puts(ok ? "Yes" : "No");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
