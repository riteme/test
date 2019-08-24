#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

inline bool judge(int a, int b) {
    if (a == 1) {
        if (b == 3 || b == 4)
            return true;
    } else if (a == 2) {
        if (b == 1 || b == 4)
            return true;
    } else if (a == 3) {
        if (b == 2 || b == 5)
            return true;
    } else if (a == 4) {
        if (b == 3 || b == 5)
            return true;
    } else if (a == 5) {
        if (b == 1 || b == 2)
            return true;
    }

    return false;
}

static int n, na, nb;
static int a[1000];
static int b[1000];

int main() {
    scanf("%d%d%d", &n, &na, &nb);

    for (int i = 0; i < na; i++) {
        scanf("%d", a + i);
        a[i]++;
    }  // for

    for (int i = 0; i < nb; i++) {
        scanf("%d", b + i);
        b[i]++;
    }  // for

    int apos = 0;
    int bpos = 0;
    int ascore = 0;
    int bscore = 0;
    for (int i = 0; i < n; i++) {
        if (a[apos] != b[bpos]) {
            if (judge(a[apos], b[bpos]))
                ascore++;
            else
                bscore++;
        }

        apos++;
        bpos++;
        apos %= na;
        bpos %= nb;
    }  // for

    printf("%d %d\n", ascore, bscore);

    return 0;
}  // function main
