#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define QMAX 1000

struct Tree {
    Tree() : current(1) {
        memset(exist, 0, sizeof(exist));
        memset(father, 0, sizeof(father));
        memset(depth, 0, sizeof(depth));
        exist[1] = true;
    }

    int current;
    bool exist[QMAX + 10];
    int father[QMAX + 10];
    int depth[QMAX + 10];

    void set_current(int u) {
        if (exist[u])
            current = u;
    }

    void append(int u) {
        exist[u] = true;
        depth[u] = depth[current] + 1;
        father[u] = current;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        while (depth[u] != depth[v]) {
            u = father[u];
        }

        while (u != v) {
            u = father[u];
            v = father[v];
        }

        return u;
    }

    int distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

static int n, q;
static Tree T[NMAX + 10];

int main() {
    scanf("%d%d", &n, &q);

    int t = 1;
    while (q--) {
        int type;
        scanf("%d", &type);

        switch (type) {
            case 0: {
                int l, r;
                scanf("%d%d", &l, &r);

                t++;
                for (int i = l; i <= r; i++) {
                    T[i].append(t);
                }
            } break;

            case 1: {
                int l, r, x;
                scanf("%d%d%d", &l, &r, &x);

                for (int i = l; i <= r; i++) {
                    T[i].set_current(x);
                }
            } break;

            case 2: {
                int x, u, v;
                scanf("%d%d%d", &x, &u, &v);

                printf("%d\n", T[x].distance(u, v));
            } break;
        }
    }
}
