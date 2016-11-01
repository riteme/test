#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 100000

static int n;
static int X[NMAX + 10];
static int Y[NMAX + 10];
static int TL, TR, BL, BR, LT, LB, RT, RB;

template <typename TCompare>
inline bool check(int x, int y, const TCompare &cmpx, const TCompare &cmpy) {
    for (int i = 1; i <= n; i++) {
        if (!cmpx(X[i], x) || !cmpy(Y[i], y))
            return false;
    }

    return true;
}

static bool cmpN(const int a, const int b) {
    return a >= b;
}

static bool cmpS(const int a, const int b) {
    return a <= b;
}

static bool cmpW(const int a, const int b) {
    return a <= b;
}

static bool cmpE(const int a, const int b) {
    return a >= b;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", X + i, Y + i);
    }

    TL = TR = BL = BR = RT = RB = LT = LB = 0;
}

int main() {
    freopen("lighthouses.in", "r", stdin);
    freopen("lighthouses.out", "w", stdout);

    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        for (int i = 1; i <= n; i++) {
            if (Y[i] > Y[TL] || (Y[i] == Y[TL] && X[i] < X[TL]))
                TL = i;
            if (Y[i] > Y[TR] || (Y[i] == Y[TR] && X[i] > X[TR]))
                TR = i;
            if (Y[i] < Y[BL] || (Y[i] == Y[BL] && X[i] < X[BL]))
                BL = i;
            if (Y[i] < Y[BR] || (Y[i] == Y[BR] && X[i] > X[BR]))
                BR = i;
            if (X[i] < X[LT] || (X[i] == X[LT] && Y[i] > Y[LT]))
                LT = i;
            if (X[i] < X[LB] || (X[i] == X[LB] && Y[i] < Y[LB]))
                LB = i;
            if (X[i] > X[RT] || (X[i] == X[RT] && Y[i] > Y[RT]))
                RT = i;
            if (X[i] > X[RB] || (X[i] == X[RB] && Y[i] < Y[RB]))
                RB = i;
        }

        if (check(X[TL], Y[TL], cmpE, cmpS) ||
            check(X[TR], Y[TR], cmpW, cmpS) ||
            check(X[BL], Y[BL], cmpE, cmpN) ||
            check(X[BR], Y[BR], cmpW, cmpN) ||
            check(X[LT], Y[LT], cmpE, cmpS) ||
            check(X[LB], Y[LB], cmpE, cmpN) ||
            check(X[RT], Y[RT], cmpW, cmpS) ||
            check(X[RB], Y[RB], cmpW, cmpN))
            puts("1");
        else
            puts("2");
    }


    fclose(stdin);
    fclose(stdout);
    return 0;
}
