/**
 * Time complexity: O(n^2)
 * Max query times: 2n - 2
 */

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 5000

inline int get_state() {
    char c;
    do {
        c = getchar();
    } while (c != '+' && c != '-');
    return c == '+' ? 1 : 0;
}

inline void query(int x, int y, int &a, int &b) {
    printf("? %d %d\n\n", x, y);
    fflush(stdout);
    a = get_state();
    b = get_state();
}

static int n;
static int fa[NMAX + 10], id[NMAX + 10], cnt[NMAX + 10];
static int m, seq[NMAX + 10];
static bool fucked[NMAX + 10];

int find(int x) {
    return fa[x] > 0 ? fa[x] = find(fa[x]) : x;
}

void link(int x, int y) {
    if (fa[x] > fa[y]) swap(x, y);
    if (fa[x] == fa[y]) fa[x]--;
    fa[y] = x;
}

int main() {
    scanf("%d", &n);

    int xy, yx;
    for (int x = 1; x <= n; x++) {
        if (fucked[x]) continue;
        for (int y = x + 1; y <= n; y++) {
            if (fucked[x] || fucked[y]) continue;
            int idx = find(x), idy = find(y);
            if (idx == idy) continue;

            query(x, y, xy, yx);
            if (xy == 1 && yx == 1) link(idx, idy);
            else fucked[x] = fucked[y] = true;
        }
    }

    for (int x = 1; x <= n; x++) {
        if (!fucked[x]) {
            id[x] = find(x);
            cnt[id[x]]++;
        }
    }

    int v = max_element(cnt + 1, cnt + n + 1) - cnt;
    int x = find_if(id + 1, id + n + 1, [v](int z) {return z == v;}) - id;
    seq[++m] = x;
    for (int y = 1; y <= n; y++) {
        if (x == y) continue;
        query(x, y, xy, yx);
        if (xy == 1) seq[++m] = y;
    }

    printf("! %d", m);
    for (int i = 1; i <= m; i++)
        printf(" %d", seq[i]);
    putchar('\n');

    return 0;
}
