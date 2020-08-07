#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

#define L 11
#define N 5000

typedef bitset<N + 1> bits;

const char *str = "114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919114514191911451419191145141919";
int s[100], pw[100];
bool ok[L + 1][L + 1];
bits f[L + 1][L + 1];

int num(int l, int r) {
    return s[r] - s[l - 1] * pw[r - l + 1];
}

void solve(int l, int r) {
    if (ok[l][r])
        return;
    ok[l][r] = true;

    auto &v = f[l][r];

    if (l + 7 > r) {
        int n = num(l, r);
        if (n <= N)
            v[n] = 1;
    }

    for (int m = l; m < r; m++) {
        solve(l, m);
        solve(m + 1, r);

        auto &vl = f[l][m];
        auto &vr = f[m + 1][r];

        for (int i = 1; i <= N; i++) if (vl[i]) {
            v |= vr << i;
        }

        for (int i = 1; i <= N; i++)
        for (int j = 1; i * j <= N; j++)
        if (vl[i] && vr[j])
            v[i * j] = 1;
    }
}

int ans[N + 1];

int main() {
    pw[0] = 1;
    for (int i = 1; i < 100; i++) {
        pw[i] = pw[i - 1] * 10;
    }
    for (int i = 1; i < 100; i++) {
        s[i] = s[i - 1] * 10 + str[i - 1] - '0';
    }

    solve(1, L);
    memset(ans, 0, sizeof(ans));
    for (int r = 1; r <= L; r++) {
        for (int i = 1; i <= N; i++)
        if (f[1][r][i] && ans[i] == 0)
            ans[i] = r;
    }

    for (int i = 1; i <= N; i++) {
        if (ans[i] == 0)
            ans[i] = -1;
    }

    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int n;
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }

    return 0;
}