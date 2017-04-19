#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300
#define SMAX 2048

static int n, m;
static char seq[NMAX + 10];
static char tmp[NMAX + 10];
static int mask[NMAX + 10];
static int cnt[70000];
static int low[SMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    scanf("%s", seq + 1);

    for (int i = 1; i <= n; i++) {
        scanf("%s", tmp);
        for (int j = 0; j < m; j++) {
            if (tmp[j] == '1')
                mask[i] |= 1 << j;
        }
    }

    for (int i = 1; i < (1 << 16); i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }

    for (int i = 0; i <= 11; i++) {
        low[1 << i] = i;
    }
}

static int f[NMAX + 10][NMAX + 10][SMAX + 10];

inline int code(char c) {
    return c == '(' ? 1 : -1;
}

inline int bitcnt(int s) {
    return cnt[s >> 16] + cnt[s & ((1 << 16) - 1)];
}

inline int lowbit(int s) {
    return low[s & (-s)];
}

int dp(int n, int k, int s) {
    if (k < 0)
        return -1;
    if (n == 1) {
        if (k == code(seq[1]))
            return s == 0 ? m + 1 : -1;
        if (k != 0 || bitcnt(s) != 1)
            return -1;

        int b = lowbit(s);
        if (mask[n] & (1 << b))
            return b + 1;
        return -1;
    }

    if (f[n][k][s])
        return f[n][k][s];

    int &ret = f[n][k][s];
    ret = -1;
    if (dp(n - 1, k - code(seq[n]), s) > 0)
        ret = m + 1;

    if (ret < 0) {
        for (int i = 1; i <= m; i++) {
            if ((s & (1 << (i - 1))) && (mask[n] & (1 << (i - 1)))) {
                if (dp(n - 1, k, s ^ (1 << (i - 1))) > 0) {
                    ret = i;
                    break;
                }
            }
        }
    }

    return ret;
}

static int sol[NMAX + 10];
static int sorted[SMAX + 10];

int main() {
#ifdef NDEBUG
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif
    initialize();

    for (int s = 0; s < (1 << m); s++) {
        sorted[s] = s;
    }
    sort(sorted, sorted + (1 << m), [](const int a, const int b) {
        return bitcnt(a) > bitcnt(b);
    });

    for (int i = 0; i < (1 << m); i++) {
        int s = sorted[i];

        if (dp(n, 0, s) > 0) {
            int k = 0;
            for (int i = n; i >= 1; i--) {
                sol[i] = dp(i, k, s);

                if (sol[i] <= m)
                    s ^= 1 << (sol[i] - 1);
                else {
                    k -= code(seq[i]);
                    sol[i] = -1;
                }
            }

            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", sol[i]);
    }

    return 0;
}
