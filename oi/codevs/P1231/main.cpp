#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ntype;

struct Edge {
    int u;
    int v;
    ntype w;

    int another(int x) { return u == x ? v : u; }
};

static int n, m;
static Edge E[100010];
static Edge *ptr[100010];
static vector<Edge *> G[100010];
static int data[100010];

inline void make_set(int n) {
    for (int i = 1; i <= n; i++) { data[i] = i; }
}

inline int find_set(int x) {
    if (x != data[x]) { data[x] = find_set(data[x]); }

    return data[x];
}

inline int union_set(int a, int b) { data[find_set(a)] = find_set(b); }

bool compare(const Edge *a, const Edge *b) { return a->w < b->w; }

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d %d %lld", &E[i].u, &E[i].v, &E[i].w);

        G[E[i].u].push_back(&E[i]);
        G[E[i].v].push_back(&E[i]);
        ptr[i] = &E[i];
    }

    ntype answer = 0;

    sort(ptr + 1, ptr + m + 1, compare);
    make_set(n);
    for (int i = 1; i <= m; i++) {
        int u = ptr[i]->u;
        int v = ptr[i]->v;
        int w = ptr[i]->w;

        if (find_set(u) != find_set(v)) {
            union_set(u, v);
            answer += w;
        }
    }

    printf("%lld", answer);

    return 0;
}
