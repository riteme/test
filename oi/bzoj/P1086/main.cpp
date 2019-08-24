/**
 * See L67
 */

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, B;
static vector<int> G[NMAX + 10];
static int cnt;
static int id[NMAX + 10];
static int capital[NMAX + 10];
static bool marked[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &B);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }
}

static int top;
static int stk[NMAX + 10];

static void dfs(int x) {
    int head = top;
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (marked[v])
            continue;

        dfs(v);

        if (top - head >= B) {
            cnt++;
            capital[cnt] = x;

            while (top > head) {
                int p = stk[--top];
                id[p] = cnt;
            }
        }
    }

    stk[top++] = x;
}

int main() {
    // freopen("bzoj_1086.in", "r", stdin);
    // freopen("bzoj_1086.out", "w", stdout);
    initialize();

    dfs(1);

    int newid = cnt;
    // Why the code below lead to WA?
    // if (top >= B) {
    //     newid = ++cnt;
    //     capital[cnt] = 1;
    // } else {
    //     for (size_t i = 0; i < G[1].size(); i++) {
    //         int p = G[1][i];

    //         if (id[p]) {
    //             newid = id[p];
    //             break;
    //         }
    //     }
    // }

    if (newid) {
        while (top) {
            int p = stk[--top];
            id[p] = newid;
        }
    }

    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) {
        printf("%d ", id[i]);
    }
    putchar('\n');

    for (int i = 1; i <= cnt; i++) {
        printf("%d ", capital[i]);
    }
    putchar('\n');

    return 0;
}
