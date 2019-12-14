#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define SIGMA 27

static int n, q;
static int idx[NMAX + 10], ans[NMAX + 10];
static char s[NMAX + 10];
static int C1[SIGMA], C2[SIGMA][SIGMA], C3[SIGMA][SIGMA][SIGMA];
static int B[SIGMA][SIGMA][SIGMA];
static int pre[NMAX + 10], nxt[NMAX + 10];

char chr(int i) {
    return i <= n ? s[i] : 0;
}

bool cmp(int i, int j) {
    for ( ; chr(i) == chr(j); i++, j++) ;
    return chr(i) < chr(j);
}

#define GET_PREFIX \
    char c1 = chr(i), c2 = chr(i + 1), c3 = chr(i + 2);

void insert(int i) {
    GET_PREFIX;
    for (int j = c1 + 1; j < SIGMA; j++)
        C1[j]++;
    for (int j = c2 + 1; j < SIGMA; j++)
        C2[c1][j]++;
    for (int j = c3 + 1; j < SIGMA; j++)
        C3[c1][c2][j]++;

    int &p = B[c1][c2][c3];
    if (p) {
        nxt[i] = p;
        pre[i] = pre[p];
        pre[p] = nxt[pre[p]] = i;
    } else {
        p = i;
        pre[i] = nxt[i] = i;
    }
}

void remove(int i) {
    GET_PREFIX;
    for (int j = c1 + 1; j < SIGMA; j++)
        C1[j]--;
    for (int j = c2 + 1; j < SIGMA; j++)
        C2[c1][j]--;
    for (int j = c3 + 1; j < SIGMA; j++)
        C3[c1][c2][j]--;

    int &p = B[c1][c2][c3];
    if (p == i)
        p = nxt[i] == i ? 0 : nxt[i];
    nxt[pre[i]] = nxt[i];
    pre[nxt[i]] = pre[i];
}

int query(int i) {
    GET_PREFIX;
    int r = C1[c1] + C2[c1][c2] + C3[c1][c2][c3];
    int p = B[c1][c2][c3], j = p;
    //printf("r = %d\n", r);
    do {
        //printf("%d ", j);
        r += j != i && cmp(j + 3, i + 3);
        j = nxt[j];
    } while (p != j);
    //puts("");
    return r + 1;
}

void initialize() {
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            char buf[8];
            scanf("%s", buf);
            s[++n] = buf[0] - 'a' + 1;
        } else
            scanf("%d", idx + i);
    }
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++)
        insert(i);

    for (int i = q; i >= 1; i--)
    if (idx[i])
        ans[i] = query(idx[i]);
    else {
        remove(n);
        if (n > 1) remove(n - 1);
        if (n > 2) remove(n - 2);
        n--;
        insert(n);
        if (n > 1) insert(n - 1);
    }

    for (int i = 1; i <= q; i++)
        if (ans[i]) printf("%d\n", ans[i]);

    return 0;
}
