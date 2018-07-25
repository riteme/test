#include <cstdio>
#include <cstring>

#define NMAX 200

inline int score(int a, int b) {
    if (a == 0) {
        if (b == 2 || b == 3)
            return 1;
    } else if (a == 1) {
        if (b == 0 || b == 3)
            return 1;
    } else if (a == 2) {
        if (b == 1 || b == 4)
            return 1;
    } else if (a == 3) {
        if (b == 2 || b == 4)
            return 1;
    } else if (a == 4) {
        if (b == 0 || b == 1)
            return 1;
    }

    return 0;
}

static int n;
static int na, nb;
static int apos, bpos;
static int A[NMAX + 10], B[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &na, &nb);

    for (int i = 0; i < na; i++) {
        scanf("%d", A + i);
    }  // for

    for (int i = 0; i < nb; i++) {
        scanf("%d", B + i);
    }  // for

    int ascore = 0, bscore = 0;
    for (int i = 1; i <= n; i++) {
        ascore += score(A[apos], B[bpos]);
        bscore += score(B[bpos], A[apos]);

        apos++;
        bpos++;
        apos %= na;
        bpos %= nb;
    }  // for

    printf("%d %d\n", ascore, bscore);

    return 0;
}  // function main
