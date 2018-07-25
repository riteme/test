#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define INFTY 200000000000000
#define NMAX 100

typedef long long int64;

static int n, m, k;
static int seq[NMAX + 10];
static int64 P[NMAX + 10][NMAX + 10];
static int64 f[NMAX + 10][NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }  // for

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%I64d", &P[i][j]);
        }  // for
    }      // for

    for (int i = 0; i <= NMAX; i++) {
        for (int j = 0; j <= NMAX; j++) {
            for (int l = 0; l <= NMAX; l++) {
                f[i][j][l] = -1;
            }  // for
        }      // for
    }          // for
}

static int64 dfs(int length, int lastc, int splited) {
    if (f[length][lastc][splited] >= 0)
        return f[length][lastc][splited];

    if (length == 1) {
        if (splited != 1)
            return INFTY;

        if (seq[1] == 0)
            return P[1][lastc];
        else {
            if (seq[1] != lastc)
                return INFTY;
            else
                return 0;
        }
    }
    if (splited > length)
        return INFTY;
    if (splited <= 0)
        return INFTY;

    if (seq[length] == 0) {
        int64 answer = INFTY;

        for (int c = 1; c <= m; c++) {
            answer = min(answer,
                         dfs(length - 1, c, splited - (c == lastc ? 0 : 1)) +
                             P[length][lastc]);
        }  // for

        f[length][lastc][splited] = answer;
        return answer;
    } else {
        if (seq[length] != lastc)
            return INFTY;

        int64 answer = INFTY;

        for (int c = 1; c <= m; c++) {
            answer =
                min(answer, dfs(length - 1, c, splited - (c == lastc ? 0 : 1)));
        }  // for

        f[length][lastc][splited] = answer;
        return answer;
    }
}

static int64 evaluate() {
    if (seq[n] == 0) {
        int64 answer = INFTY;

        for (int i = 1; i <= m; i++) {
            answer = min(answer, dfs(n, i, k));
        }  // for

        return answer;
    } else {
        return dfs(n, seq[n], k);
    }
}

int main() {
    initialize();

    int64 answer = evaluate();

    if (answer >= INFTY)
        puts("-1");
    else
        printf("%I64d", answer);

    return 0;
}  // function main
