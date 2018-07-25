#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 100
#define CMAX 6

static int n;
static int score[NMAX + 10];
static int cnt[NMAX + 10][CMAX + 10];

static int judge(int x) {
    int result = 0;

    int m = *min_element(&cnt[x][1], &cnt[x][7]);
    result += 4 * m;
    for (int i = 1; i <= 6; i++)
        cnt[x][i] -= m;

    int zerocnt = 0;
    m = INT_MAX;
    for (int i = 1; i <= 6; i++) {
        if (cnt[x][i] == 0) {
            zerocnt++;
            continue;
        }

        m = min(m, cnt[x][i]);
    }  // for

    if (zerocnt == 1) {
        result += 2 * m;
        for (int i = 1; i <= 6; i++)
            if (cnt[x][i] > 0)
                cnt[x][i] -= m;
    }

    zerocnt = 0;
    m = INT_MAX;
    for (int i = 1; i <= 6; i++) {
        if (cnt[x][i] == 0) {
            zerocnt++;
            continue;
        }

        m = min(m, cnt[x][i]);
    }  // for

    if (zerocnt > 2)
        return result;
    result += m;

    return result;
}

static int winner() {
    int m = *max_element(score + 1, score + n + 1);
    int mcnt = 0, mindex = 0;
    for (int i = 1; i <= n; i++)
        if (score[i] == m) {
            mindex = i;
            mcnt++;
        }

    if (mcnt > 1)
        return 0;
    return mindex;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        memset(score, 0, sizeof(score));
        memset(cnt, 0, sizeof(cnt));

        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", score + i);

            for (int j = 1; j <= score[i]; j++) {
                int type;
                scanf("%d", &type);

                cnt[i][type]++;
            }  // for
        }      // for

        for (int i = 1; i <= n; i++)
            score[i] += judge(i);

        int win = winner();
        if (win == 0)
            puts("tie");
        else if (win == 1)
            puts("chef");
        else
            printf("%d\n", win);
    }  // while

    return 0;
}  // function main
