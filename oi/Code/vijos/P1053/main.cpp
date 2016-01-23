#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

#define NMAX 1000
#define MMAX 100000
#define INFTY 200000000000
#define TEST_LIMIT 30

#define FMT "%lld"
typedef long long ntype;

#define INVALID "-1"
#define NO_PATH "NoPath"

struct Edge {
    ntype u;
    ntype v;
    ntype w;

    ntype another(ntype x) {
        return u == x ? v : u;
    }
};  // struct Edge

static ntype n;
static ntype m;
static ntype s;
static bool flag;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static ntype dist[NMAX + 10];
static ntype answer[NMAX + 10];
static bool marked[NMAX + 10];
static ntype cnt[NMAX + 10];

void initialize() {
    scanf(FMT FMT FMT, &n, &m, &s);

    for (int i = 0; i < m; i++) {
        ntype u, v, w;
        scanf(FMT FMT FMT, &u, &v, &w);

        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
        G[u].push_back(&edges[i]);
        // G[v].push_back(&edges[i]);
    }  // for

    flag = false;
}

void spfa_slf(ntype source) {
    ntype x = dist[source] + 1;
    deque<ntype> q;
    q.push_back(source);
    cnt[source]++;

    while (!q.empty() and !flag) {
        ntype u = *q.begin();
        marked[u] = true;
        q.pop_front();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            ntype v = e->v;

            // printf("dist[" FMT "] = " FMT ", dist[" FMT "] = " FMT
            // ", e->w = " FMT "\n",
            // v, dist[v], u, dist[u], e->w);

            if (dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;

                if (!q.empty() and dist[v] < dist[*q.begin()])
                    q.push_front(v);
                else
                    q.push_back(v);

                cnt[v]++;

                if (cnt[v] > TEST_LIMIT) {
                    flag = true;
                }
            }
        }  // for
    }      // while
}

void compute() {
    dist[s] = 0;
    spfa_slf(s);
}

int main() {
    initialize();

    memset(cnt, 0, sizeof(cnt));
    memset(marked, false, sizeof(marked));
    for (int i = 1; i <= n; i++) {
        dist[i] = INFTY;
    }  // for
    compute();

    for (int i = 1; i <= n; i++) {
        answer[i] = dist[i];
    }  // for

    for (int i = 1; i <= n; i++) {
        if (!marked[i]) {
            dist[i] = 0;

            spfa_slf(i);
        }
    }  // for

    if (flag) {
        printf(INVALID);
    } else {
        for (int i = 1; i <= n; i++) {
            if (answer[i] < INFTY)
                printf(FMT "\n", answer[i]);
            else
                printf(NO_PATH "\n");
        }  // for
    }

    return 0;
}  // function main
