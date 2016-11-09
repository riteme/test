#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define INFTY 1000000000

static int f[30][15][10][8][5];

static int dp(int a, int b, int c, int d, int e) {
    if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0)
        return 0;
    if (a < 0 || b < 0 || c < 0 || d < 0 || e < 0)
        return INFTY;


    if (f[a][b][c][d][e])
        return f[a][b][c][d][e];

    int &answer = f[a][b][c][d][e];
    answer = INFTY;
    
#define MINIMIZE(state) answer = min(answer, (state) + 1);

    MINIMIZE(dp(a - 1, b, c, d, e))

    MINIMIZE(dp(a, b - 1, c, d, e))

    MINIMIZE(dp(a, b, c - 1, d, e))
    MINIMIZE(dp(a - 1, b, c - 1, d, e))
    MINIMIZE(dp(a, b - 1, c - 1, d, e))
    MINIMIZE(dp(a, b + 1, c - 2, d, e))
    MINIMIZE(dp(a + 1, b, c - 2, d, e))
    MINIMIZE(dp(a, b, c, d - 1, e))
    MINIMIZE(dp(a, b + 1, c - 1, d - 1, e))
    MINIMIZE(dp(a, b, c - 1, d, e - 1))

    MINIMIZE(dp(a, b, c, d - 1, e))
    MINIMIZE(dp(a - 2, b, c, d - 1, e))
    MINIMIZE(dp(a, b - 1, c, d - 1, e))
    MINIMIZE(dp(a - 1, b + 1, c - 1, d - 1, e))
    MINIMIZE(dp(a - 1, b, c + 1, d - 2, e))
    MINIMIZE(dp(a - 1, b, c, d - 1, e - 1))
    MINIMIZE(dp(a + 1, b, c - 1, d - 1, e))
    MINIMIZE(dp(a + 1, b - 1, c + 1, d - 2, e))
    MINIMIZE(dp(a + 1, b - 1, c, d - 1, e - 1))
    MINIMIZE(dp(a, b + 1, c, d - 2, e))
    MINIMIZE(dp(a, b + 1, c - 1, d - 1, e - 1))
    MINIMIZE(dp(a, b, c, d - 1, e - 2))
    MINIMIZE(dp(a, b - 2, c, d - 1, e))
    MINIMIZE(dp(a + 1, b - 1, c - 1, d - 1, e))
    MINIMIZE(dp(a, b, c, d - 2, e))
    MINIMIZE(dp(a + 2, b, c - 2, d - 1, e))
    MINIMIZE(dp(a + 1, b + 1, c - 1, d - 2, e))
    MINIMIZE(dp(a, b + 2, c, d - 3, e))

    MINIMIZE(dp(a, b, c, d, e - 1))
    MINIMIZE(dp(a, b, c, d, e - 2))

#undef MINIMIZE

    return answer;
}

static int n;
static int cnt[20];

int solve();

inline void put_seq(int &answer, int limit, int minlen) {
    for (int i = 3; i <= 14 - minlen + 1; i++) {
        for (int j = i; j <= 14 && cnt[j] >= limit; j++) {
            if (j - i + 1 >= minlen) {
                for (int k = i; k <= j; k++)
                    cnt[k] -= limit;
                answer = min(answer, solve() + 1);
                for (int k = i; k <= j; k++)
                    cnt[k] += limit;
            }
        }
    }
}

int solve() {
    int a = 0, b = 0, c = 0, d = 0, e = cnt[15] + cnt[16];
    for (int i = 2; i <= 14; i++) {
        if (cnt[i] == 1)
            a++;
        else if (cnt[i] == 2)
            b++;
        else if (cnt[i] == 3)
            c++;
        else if (cnt[i] == 4)
            d++;
    }

    int answer = dp(a, b, c, d, e);

    put_seq(answer, 1, 5);
    put_seq(answer, 2, 3);
    put_seq(answer, 3, 2);

    return answer;
}

int main() {
    int t;
    scanf("%d%d", &t, &n);

    while (t--) {
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= n; i++) {
            int x, c;
            scanf("%d%d", &x, &c);

            if (x == 0 && c == 1)
                cnt[15] = 1;
            else if (x == 0 && c == 2)
                cnt[16] = 1;
            else if (x == 1)
                cnt[14]++;
            else
                cnt[x]++;
        }

        printf("%d\n", solve());
    }

    return 0;
}
