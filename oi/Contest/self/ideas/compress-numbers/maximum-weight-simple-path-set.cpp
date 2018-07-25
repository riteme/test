#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 1000
#define MMAX 5000

struct Edge {
    int id;
    int from;
    int to;
    int w;
};  // struct Edge

static int n, m;
static Edge edges[MMAX + 10];
static vector<Edge *> in[NMAX + 10];
static vector<Edge *> out[NMAX + 10];
static Edge *nxt[NMAX + 10];
static Edge *pre[NMAX + 10];
static bool marked[MMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        edges[i].id = i;
        edges[i].from = u;
        edges[i].to = v;
        edges[i].w = w;
        in[v].push_back(edges + i);
        out[u].push_back(edges + i);
    }
}

inline bool is_father(int u, int v) {
    while (u != v && pre[v])
        v = pre[v]->from;

    return u == v;
}

int main() {
    initialize();

    queue<int> q;
    for (int i = 1; i <= m; i++) {
        q.push(i);
        marked[i] = true;
    }  // for

    int answer = 0;
    while (!q.empty()) {
        int id = q.front();
        marked[id] = false;
        q.pop();

        Edge &e = edges[id];
        int u = e.from;
        int v = e.to;
        int w = e.w;

        if (u == v)
            continue;

        int lost = 0;
        int d1 = 0, d2 = 0, d3 = 0;
        if (nxt[u]) {
            lost += nxt[u]->w;
            d1 = nxt[u]->id;
        }

        if (pre[v]) {
            lost += pre[v]->w;
            d2 = pre[v]->id;
        }

        if (is_father(v, u) && nxt[v]) {
            lost += nxt[v]->w;
            d3 = nxt[v]->id;
        }

        if (lost < w) {
            answer += w - lost;

            if (nxt[u])
                pre[nxt[u]->to] = nullptr;
            if (pre[v])
                nxt[pre[v]->from] = nullptr;

            nxt[u] = pre[v] = &e;

            if (d3) {
                if (nxt[v])
                    pre[nxt[v]->to] = nullptr;

                nxt[v] = nullptr;
            }

            for (size_t i = 0; i < out[v].size(); i++) {
                Edge *e = out[v][i];

                if (!marked[e->id]) {
                    q.push(e->id);
                    marked[e->id] = true;
                }
            }  // for

            for (size_t i = 0; i < in[u].size(); i++) {
                Edge *e = in[u][i];

                if (!marked[e->id]) {
                    q.push(e->id);
                    marked[e->id] = true;
                }
            }  // for

            marked[id] = true;

            if (d1)
                q.push(d1);
            if (d2)
                q.push(d2);
            if (d3)
                q.push(d3);
        }
    }

    memset(marked, 0, sizeof(marked));
    printf("%d\n", answer);
    
    for (int i = 1; i <= n; i++) {
        if (marked[i])
            continue;

        int father = i;
        while (pre[father])
            father = pre[father]->from;

        while (true) {
            printf("%d ", father);
            marked[father] = true;

            if (nxt[father])
                father = nxt[father]->to;
            else
                break;
        }  // while

        printf("\n");
    }  // for
    

    return 0;
}  // function main
