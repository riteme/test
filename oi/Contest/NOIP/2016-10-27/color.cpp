#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 50000
#define SQRTN 250

static int n, q;
static int color[NMAX + 10];
static int cnt[NMAX + 10];
static int allcolor;

static int bigcnt;
static int bigpre[SQRTN + 10][NMAX + 10];

static int smallright[SQRTN + 10][NMAX + 10];

static bool query(int left, int right, int k) {
    if (k == 0)
        return true;

    if (k > SQRTN) {
        int maxcnt = 0;
        for (int i = 1; i <= bigcnt; i++) {
            maxcnt = max(maxcnt, bigpre[i][right] - bigpre[i][left - 1]);
        }

        return maxcnt >= k;
    } else
        return smallright[k][left] <= right;
}

static int tcnt[NMAX + 10];
static int vcnt[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d", color + i);

        cnt[color[i]]++;
        
        if (cnt[color[i]] == 1)
            allcolor++;
    }

    for (int c = 1; c <= n; c++) {
        if (cnt[c] > SQRTN) {
            bigcnt++;

            for (int i = 1; i <= n; i++) {
                if (color[i] == c)
                    bigpre[bigcnt][i] = 1;

                bigpre[bigcnt][i] += bigpre[bigcnt][i - 1];
            }
        }
    }

    for (int k = 1; k <= SQRTN; k++) {
        memset(tcnt, 0, sizeof(tcnt));
        memset(vcnt, 0, sizeof(vcnt));
        tcnt[0] = allcolor;
        int high = 0;
        int i = 1, j = 0;

        while (i <= n) {
            while (j < n && high < k) {
                j++;
                int c = color[j];
                tcnt[c]++;
                vcnt[tcnt[c] - 1]--;
                vcnt[tcnt[c]]++;

                while (vcnt[high + 1])
                    high++;
            }

            if (high >= k)
                smallright[k][i] = j;
            else
                smallright[k][i] = INT_MAX;

            int c = color[i];
            tcnt[c]--;
            vcnt[tcnt[c] + 1]--;
            vcnt[tcnt[c]]++;
            while (high > 0 && !vcnt[high])
                high--;
            i++;
        }
    }
}

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    initialize();

    while (q--) {
        int left, right, k;
        scanf("%d%d%d", &left, &right, &k);

        puts(query(left, right, k) ? ">_<" : "QAQ");
    }

    return 0;
}
