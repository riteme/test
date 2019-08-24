/**
 * WC2011 Xor
 * 如何解决这个问题：
 * 1. 解的形式：一条从1到n的路径加上一些环
 * 由于图是联通的，所以我们的路径可以走到任意一个环并回到原来的位置
 *
 * 如何构造这样的解：
 * 关键的一点就是我们可以利用有限的环来构造出图中所有的环。
 * 考虑到两个有公共边界的环，将它们的异或和异或起来将得到一个更大的环
 * 并且公共边界消失了
 *
 * 有限的环是通过DFS找出来的，但是为什么O(m)个环就可以完成所有的环
 * 不会证，我觉得原因应该是它们包含了所有的边
 *
 * 此外还需要一条1到n的路径，非常神奇，我们只用随便用一条路径来初始化即可。
 * 因为如果有更好的路径，那么它们的非公共部分会构成一个环
 * 这样通过一个环的异或就可变化到最优路径上去
 *
 * 最优性依靠异或线性基来保证
 */

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define MMAX 100000
#define SPACESIZE 62

typedef long long int64;

struct DirectedEdge {
    DirectedEdge(int _to, int64 _w)
        : to(_to), w(_w) {}

    int to;
    int64 w;
};

static int n, m;
static vector<DirectedEdge *> G[NMAX + 10];
static int64 answer;
static int64 basis[SPACESIZE + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        int64 w;
        scanf("%d%d%lld", &u, &v, &w);

        G[u].push_back(new DirectedEdge(v, w));
        G[v].push_back(new DirectedEdge(u, w));
    }
}

inline void update_basis(int64 x) {
    for (int i = SPACESIZE - 1; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (basis[i])
                x ^= basis[i];
            else {
                basis[i] = x;
                break;
            }
        }
    }
}

static int64 dist[NMAX + 10];
static bool marked[NMAX + 10];

static void dfs(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        DirectedEdge *e = G[x][i];
        int v = e->to;

        if (!marked[v]) {
            dist[v] = dist[x] ^ e->w;

            dfs(v);
        } else
            update_basis(dist[x] ^ dist[v] ^ e->w);
    }
}

int main() {
    initialize();
    dfs(1);

    answer = dist[n];
    for (int i = SPACESIZE - 1; i >= 0; i--) {
        if (!((answer >> i) & 1))
            answer ^= basis[i];
    }

    printf("%lld\n", answer);

    return 0;
}
