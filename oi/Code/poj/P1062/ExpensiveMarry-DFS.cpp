/**
 * 昂贵的聘礼
 * 这个是毫无参考价值的DFS......
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100
#define INFTY 5000000000000000LL

#define FMT "%lld"
typedef long long ntype;

struct Edge {
    Edge(ntype _from, ntype _to, ntype _w) : from(_from), to(_to), w(_w) {}

    ntype from;
    ntype to;
    ntype w;
};  // struct Edge

static ntype m;
static ntype n;
static ntype L[NMAX + 10];
static vector<Edge> edges;
static vector<Edge *> G[NMAX + 10];
// static ntype dist[NMAX + 10];
static bool marked[NMAX + 10];
static ntype answer;

template <typename T>
inline T abs(const T &a) {
    return a < 0 ? -a : a;
}

void initialize() {
    scanf(FMT FMT, &m, &n);

    for (ntype i = 1; i <= n; i++) {
        ntype p, x;
        scanf(FMT FMT FMT, &p, L + i, &x);

        // 表示直接用金币换
        edges.push_back(Edge(0, i, p));

        while (x > 0) {
            ntype t, v;
            scanf(FMT FMT, &t, &v);

            edges.push_back(Edge(t, i, v));

            x--;
        }  // while
    }      // for

    // 构图
    for (unsigned i = 0; i < edges.size(); i++) {
        Edge &e = edges[i];
        G[e.from].push_back(&e);
    }  // for
}

// 逼我的
// 居然过了...... 16ms......
void dfs(ntype x, ntype dist, ntype maxlevel, ntype minlevel) {
    if (x == 1) {
        if (dist < answer) {
            answer = dist;
        }

        return;
    }

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        ntype v = e->to;

        if (!marked[v]) {
            if (x != 0 and
                (abs(maxlevel - L[v]) > m or abs(minlevel - L[v]) > m)) {
                continue;
            }

            if (dist + e->w < answer) {
                marked[v] = true;

                dfs(v, dist + e->w, max(maxlevel, L[v]), min(minlevel, L[v]));

                marked[v] = false;
            }
        }
    }  // for
}

int main() {
    initialize();

    memset(marked, false, sizeof(marked));
    answer = INFTY;
    dfs(0, 0, -INFTY, INFTY);

    // printf(FMT, dist[1]);
    printf(FMT, answer);

    return 0;
}  // function main
