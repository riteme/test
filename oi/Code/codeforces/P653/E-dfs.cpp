/**
 * 给你一张巨大的完全无向图，其中某些边被删除。
 * 询问在剩下的图中是否存在一棵生成树，并且这棵树的1号点要有k条边
 *
 * n <= 3e5
 *
 * 使用DFS或BFS进行联通性检查。但不能直接遍历，否则时间复杂度为O(n^2)
 * 使用线性数据结构来维护一个还未被访问过的节点集合，每次访问都从中找出适合的节点来访问
 * 对于被删除的边就什么也不做，直到这个集合内的每个点都无法再被访问为止。
 * 如果有剩余的点，则说明图不联通。
 * 每个点只会访问一次，一般情况下哈希表的事件复杂度为O(1)，整个过程为O(n + m)
 * m为被删去的边数
 *
 * 因为生成的树中1号点要有k条边，那么说明将1号点删除后，整张图会分裂为至多k的联通分量。
 * 遍历原来1号点的邻居即可得知联通分量的个数。
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 300000

typedef pair<int, int> ForbiddenPair;

namespace std {
template <>
struct hash<ForbiddenPair> {
    auto operator()(const ForbiddenPair &p) const -> size_t {
        auto h = hash<int>();

        return h(p.first) * h(p.second);
    }
};  // struct hash<ForbiddenPair>
}

static int n, m, k;
static int degree1;
static unordered_set<ForbiddenPair> forbidden;
static list<int> unvisited;

static void initialize() {
    scanf("%d%d%d", &n, &m, &k);
    degree1 = n - 1;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        forbidden.insert({ u, v });
        forbidden.insert({ v, u });

        if (v == 1 || u == 1)
            degree1--;
    }  // for
}

static void dfs(int x, int &cnt) {
    // printf("dfs: x = %d\n", x);
    cnt++;

    while (true) {
        auto iter = find_if(
            unvisited.begin(),
            unvisited.end(),
            [x](int current) {
                return forbidden.find({ x, current }) == forbidden.end();
            });

        if (iter == unvisited.end())
            break;

        int v = *iter;
        unvisited.erase(iter);
        dfs(v, cnt);
    }  // while
}

static int dfs(int x) {
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (i != x)
            unvisited.push_back(i);
    }  // for

    dfs(x, cnt);

    // printf("dfs: cnt = %d\n", cnt);

    return cnt;
}

static int count_subtree(int x) {
    unvisited.clear();

    for (int i = 1; i <= n; i++) {
        if (i != x)
            unvisited.push_back(i);
    }  // for

    int cnt = 0;
    while (true) {
        auto iter = find_if(
            unvisited.begin(),
            unvisited.end(),
            [x](int current) {
                return forbidden.find({ x, current }) == forbidden.end();
            });

        if (iter == unvisited.end())
            break;

        int reserve;
        int v = *iter;
        unvisited.erase(iter);
        dfs(v, reserve);
        cnt++;
    }  // while

    // printf("count: cnt = %d\n", cnt);
    return cnt;
}

int main() {
    initialize();

    if (degree1 < k)
        printf("impossible");
    else if (dfs(1) != n)
        printf("impossible");
    else {
        if (count_subtree(1) > k)
            printf("impossible");
        else
            printf("possible");
    }

    return 0;
}  // function main
