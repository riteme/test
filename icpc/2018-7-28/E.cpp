/**
 * Time complexity: O(n)
 * Max query times: 2n - 2
 */

#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
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

static int qcnt;
inline void query(int x, int y, int &a, int &b) {
    qcnt++;
    printf("? %d %d\n", x, y);
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

    queue<int> q;
    int xy, yx, x = 1;
    for (int y = 2; y <= n; y++) {
        if (!x) {
            if (!q.empty()) {
                x = q.front();
                q.pop();
            } else {
                x = y;
                continue;
            }
        }

        query(x, y, xy, yx);
        if (xy == 1 && yx == 1) {
            link(find(x), find(y));
            q.push(y);
        } else {
            fucked[x] = fucked[y] = true;
            x = 0;
        }
    }

    for (int x = 1; x <= n; x++) {
        if (!fucked[x]) {
            id[x] = find(x);
            cnt[id[x]]++;
        }
    }

    int v = max_element(cnt + 1, cnt + n + 1) - cnt;
    x = find_if(id + 1, id + n + 1, [v](int z) {return z == v;}) - id;
    seq[++m] = x;
    for (int y = 1; y <= n; y++) {
        if (x == y) continue;
        if (id[x] == id[y]) seq[++m] = y;
        else if (id[y] && id[x] != id[y]) continue;
        else {
            query(x, y, xy, yx);
            if (xy == 1) seq[++m] = y;
        }
    }

    printf("! %d", m);
    for (int i = 1; i <= m; i++)
        printf(" %d", seq[i]);
    putchar('\n');

    fprintf(stderr, "query: %d\n", qcnt);

    return 0;
}
