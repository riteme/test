#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>

using namespace std;

#define NMAX 100000
#define LOGN 17

#define INFTY 2000000000.0

#define A 0
#define B 1

typedef long long int64;

static int n;
static int64 h[NMAX + 10];
static int sorted[NMAX + 10];
static int listnext[NMAX + 10];
static int listprev[NMAX + 10];
static int anext[NMAX + 10];
static int bnext[NMAX + 10];
static int f[NMAX + 10][LOGN + 1][2];
static int64 asum[NMAX + 10][LOGN + 1][2];
static int64 bsum[NMAX + 10][LOGN + 1][2];

static bool cmp(const int i, const int j) {
    return h[i] < h[j];
}

inline int choose_min(int id, int &left, int &right) {
    int answer = 0;
    if (left == 0) {
        answer = right;
        right = listnext[right];
    } else if (right == 0) {
        answer = left;
        left = listprev[left];
    } else {
        int64 leftdist = abs(h[left] - h[id]);
        int64 rightdist = abs(h[right] - h[id]);

        if (leftdist < rightdist ||
            (leftdist == rightdist && h[left] < h[right])) {
            answer = left;
            left = listprev[left];
        } else {
            answer = right;
            right = listnext[right];
        }
    }

    if (right > n)
        right = 0;

    return answer;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", h + i);
        sorted[i] = i;
    }  // for

    sort(sorted + 1, sorted + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        int p = sorted[i];
        if (i > 1)
            listprev[p] = sorted[i - 1];
        if (i < n)
            listnext[p] = sorted[i + 1];
    }  // for

    for (int i = 1; i <= n; i++) {
        int left = listprev[i];
        int right = listnext[i];

        bnext[i] = choose_min(i, left, right);
        anext[i] = choose_min(i, left, right);

        if (listprev[i])
            listnext[listprev[i]] = listnext[i];
        if (listnext[i])
            listprev[listnext[i]] = listprev[i];
    }  // for

    for (int i = 1; i <= n; i++) {
        f[i][0][A] = anext[i];
        f[i][0][B] = bnext[i];

        if (anext[i])
            asum[i][0][A] = abs(h[anext[i]] - h[i]);
        asum[i][0][B] = 0;

        bsum[i][0][A] = 0;
        if (bnext[i])
            bsum[i][0][B] = abs(h[bnext[i]] - h[i]);
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            if (j == 1) {
                f[i][1][A] = f[f[i][0][A]][0][B];
                f[i][1][B] = f[f[i][0][B]][0][A];

                asum[i][1][A] = asum[i][0][A] + asum[f[i][0][A]][0][B];
                asum[i][1][B] = asum[i][0][B] + asum[f[i][0][B]][0][A];

                bsum[i][1][A] = bsum[i][0][A] + bsum[f[i][0][A]][0][B];
                bsum[i][1][B] = bsum[i][0][B] + bsum[f[i][0][B]][0][A];
            } else {
                f[i][j][A] = f[f[i][j - 1][A]][j - 1][A];
                f[i][j][B] = f[f[i][j - 1][B]][j - 1][B];

                asum[i][j][A] =
                    asum[i][j - 1][A] + asum[f[i][j - 1][A]][j - 1][A];
                asum[i][j][B] =
                    asum[i][j - 1][B] + asum[f[i][j - 1][B]][j - 1][B];

                bsum[i][j][A] =
                    bsum[i][j - 1][A] + bsum[f[i][j - 1][A]][j - 1][A];
                bsum[i][j][B] =
                    bsum[i][j - 1][B] + bsum[f[i][j - 1][B]][j - 1][B];
            }
        }  // for
    }      // for
}

inline void query(int s, int64 X, int64 &oa, int64 &ob) {
    int64 adist = 0;
    int64 bdist = 0;

    for (int i = LOGN; i >= 0; i--) {
        int64 dist = asum[s][i][A] + bsum[s][i][A];
        if (dist <= X) {
            X -= dist;
            adist += asum[s][i][A];
            bdist += bsum[s][i][A];
            s = f[s][i][A];
        }
    }  // for

    oa = adist;
    ob = bdist;
}

int main() {
    initialize();

    int64 x0;
    int m;
    scanf("%lld%d", &x0, &m);

    int answer = 0;
    double rate = INFTY;

    for (int i = 1; i <= n; i++) {
        int64 adist, bdist;
        query(i, x0, adist, bdist);

        if (bdist == 0) {
            if (rate >= INFTY && h[answer] < h[i])
                answer = i;
        } else {
            double result = (double)adist / (double)bdist;

            if (result < rate) {
                answer = i;
                rate = result;
            }
        }
    }  // for

    printf("%d\n", answer);

    while (m--) {
        int s;
        int64 x1;
        scanf("%d%lld", &s, &x1);

        int64 adist, bdist;
        query(s, x1, adist, bdist);
        printf("%lld %lld\n", adist, bdist);
    }  // while

    return 0;
}  // function main
