#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 1000000

static int n, m;
static char name[NMAX + 10][32];
static int HP[NMAX + 10], AT[NMAX + 10], DF[NMAX + 10];
static struct {
    int i, j, k;
} ans[MMAX + 10];

int combat(int i, int j) {
    int di = max(0, AT[j] - DF[i]);
    int dj = max(0, AT[i] - DF[j]);
    if (di == 0 && dj == 0)
        return 0;
    if (di == 0)
        return 1;
    if (dj == 0)
        return -1;
    int ki = (HP[i] + di - 1) / di;
    int kj = (HP[j] + dj - 1) / dj;
    if (ki == kj)
        return 0;
    return ki > kj ? 1 : -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s%d%d%d", name[i], HP + i, AT + i, DF + i);

    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
    for (int k = j + 1; k <= n; k++) {
        int ai = 0, aj = 0, ak = 0;
        int vij = combat(i, j);
        int vik = combat(i, k);
        int vjk = combat(j, k);
        ai += vij + vik;
        aj += vjk - vij;
        ak -= vik + vjk;

        if (vij && vik && vjk && ai == 0 && aj == 0 && ak == 0)
            ans[m++] = {i, j, k};
    }

    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        auto &p = ans[i];
        printf("%s %s %s\n", name[p.i], name[p.j], name[p.k]);
    }

    return 0;
}