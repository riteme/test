/**
 * 好智障，对于这种题目不熟悉几次分析错误......
 *
 * 首先是差分，可以递归前计算一次之前的贡献，递归完后再计算一次，
 * 两次相减就是自己的答案，这个思想可以推广到可减的运算上
 *
 * 然后是特殊情况的判定：
 *
 *     1 (1)
 *   /   \
 * 2 (0)   3 (0)
 * 然后路径从2 -> 3
 * 这个路径会被拆成2 -> 1和1 -> 3，注意我们向下的深度减1了，
 * 所以1处会被记录两次答案......
 * 所以解决办法就是，特判之，预先加上答案，然后计算标记时同时应用加和减的
 */

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define LOGN 20

static int n, m;
static vector<int> G[NMAX + 10];
static int dist[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static int appear_time[NMAX + 10];
static int start[NMAX + 10];
static int endpoint[NMAX + 10];
static int lca[NMAX + 10];
static int answer[NMAX + 10];
static vector<int> upadd[NMAX + 10];
static vector<int> downadd[NMAX + 10];
static vector<int> updel[NMAX + 10];
static vector<int> downdel[NMAX + 10];
static int upcnt[NMAX * 2 + 10];
static int downcnt[NMAX * 2 + 10];
static bool marked[NMAX + 10];

static void build_tree(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            dist[v] = dist[x] + 1;
            f[v][0] = x;

            build_tree(v);
        }
    }
}

inline int evaluate_lca(int u, int v) {
    if (dist[u] < dist[v])
        swap(u, v);

    int delta = dist[u] - dist[v];
    for (int i = LOGN; i >= 0; i--)
        if ((delta >> i) & 1)
            u = f[u][i];

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }

    return f[u][0];
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    dist[1] = NMAX;
    build_tree(1);

    for (int j = 1; j <= LOGN; j++)
        for (int i = 1; i <= n; i++)
            f[i][j] = f[f[i][j - 1]][j - 1];

    for (int i = 1; i <= n; i++)
        scanf("%d", appear_time + i);

    for (int i = 1; i <= m; i++) {
        int s, t;
        scanf("%d%d", &s, &t);

        if (s == t) {
            if (appear_time[s] == 0)
                answer[s]++;

            m--;
            i--;
        } else {
            start[i] = s;
            endpoint[i] = t;
            lca[i] = evaluate_lca(s, t);
        }
    }
}

enum PathType {
    DOWN,
    UP
};

inline void add_path(int u, int v, PathType type, int extra) {
    if (u == v)
        return;

    if (type == UP) {
        assert(extra == 0);

        upadd[u].push_back(dist[u]);
        updel[v].push_back(dist[u]);
    } else {
        downadd[v].push_back(dist[u] - extra);
        downdel[u].push_back(dist[u] - extra);
    }
}

static void calc(int x) {
    marked[x] = true;
    answer[x] -= upcnt[dist[x] + appear_time[x]] +
                 downcnt[dist[x] - appear_time[x]];

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v])
            calc(v);
    }

    for (size_t i = 0; i < upadd[x].size(); i++)
        upcnt[upadd[x][i]]++;
    for (size_t i = 0; i < downadd[x].size(); i++)
        downcnt[downadd[x][i]]++;
    for (size_t i = 0; i < downdel[x].size(); i++)
        downcnt[downdel[x][i]]--;
    for (size_t i = 0; i < updel[x].size(); i++)
        upcnt[updel[x][i]]--;

    answer[x] += upcnt[dist[x] + appear_time[x]] +
                 downcnt[dist[x] - appear_time[x]];
}

int main() {
    // freopen("running.in", "r", stdin);

    initialize();

    for (int i = 1; i <= m; i++) {
        int delta = dist[start[i]] - dist[lca[i]];

        if (appear_time[lca[i]] == delta)
            answer[lca[i]]++;

        add_path(start[i], lca[i], UP, 0);
        add_path(lca[i], endpoint[i], DOWN, delta);
    }

    memset(marked, 0, sizeof(marked));
    calc(1);

    for (int i = 1; i <= n; i++)
        printf("%d ", answer[i]);
    printf("\n");

    return 0;
}
