/**
 * 昂贵的聘礼
 * SPFA版 32ms
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
static ntype dist[NMAX + 10];
static ntype maxlevel;
static ntype minlevel;
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

void spfa(ntype s) {
    for (ntype i = 0; i <= n; i++) {
        dist[i] = INFTY;
    }  // for
    dist[s] = 0LL;

    queue<ntype> q;
    q.push(s);

    while (!q.empty()) {
        ntype u = q.front();
        q.pop();

        for (unsigned i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            ntype v = e->to;

            if (minlevel <= L[v] and L[v] <= maxlevel and
                dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;

                q.push(v);
            }  // if
        }      // for
    }          // while
}

int main() {
    initialize();

    // 枚举等级范围
    answer = INFTY;
    for (minlevel = L[1] - m; minlevel <= L[1]; minlevel++) {
        maxlevel = minlevel + m;

        spfa(0);

        if (dist[1] < answer) {
            answer = dist[1];
        }
    }  // for

    printf(FMT, answer);

    return 0;
}  // function main
