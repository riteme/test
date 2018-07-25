#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 50000

struct Edge {
    int u, v, w;
};

static int n, m;
static Edge edges[MMAX + 10];
static Edge *ref[MMAX + 10];
static int father[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++)
        father[i] = i;
}

inline int find_set(int x) {
    return father[x] == x ? x : father[x] = find_set(father[x]);
}

static int kruskal() {
    int answer = 0;

    sort(ref + 1, ref + m + 1,
         [](const Edge *a, const Edge *b) {
            return a->w < b->w;   
         });

    make_set();
    int cnt = 0;
    int pos = 1;
    while (cnt < n - 1) {
        Edge *e = ref[pos++];
        int u = find_set(e->u);
        int v = find_set(e->v);
        
        if (u != v) {
            answer += e->w;
            father[u] = v;
            cnt++;
        }
    }

    return answer;
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        ref[i] = edges + i;
    }

    printf("%d\n", kruskal());

    return 0;
}
