#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define INF 0x3f3f3f3f

static int seq[100];
static int f[100][100];

int dp(int l, int r) {
    if (l == r)
        return -seq[l];
    if (f[l][r] < INF)
        return f[l][r];

    int &ans = f[l][r], cnt = r - l + 1;
    if (cnt & 1)
        ans = min(dp(l + 1, r) - seq[l], dp(l, r - 1) - seq[r]);
    else
        ans = max(dp(l + 1, r) + seq[l], dp(l, r - 1) + seq[r]);

    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }

    memset(f, 0x3f, sizeof(f));
    printf("%d\n", dp(1, n));

    return 0;
}
