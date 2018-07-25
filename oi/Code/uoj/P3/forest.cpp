/**
 * LCT 暴力枚举
 * 从小至大枚举a的最大值，同时为了使b尽可能小，利用最小生成树的性质就可以维护
 * 使用LCT来动态维护这个最小生成树
 * 注意只有在1和n连通的时候才更新答案
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define MMAX 100000

struct Edge {
    int id;
    int u, v, a, b;
};  // struct Edge

static int n, m;

static Edge edges[MMAX + 10];
static Edge *sorted[MMAX + 10];

static int parent[NMAX + MMAX + 10];
static int left[NMAX + MMAX + 10];
static int right[NMAX + MMAX + 10];
static bool reversed[NMAX + MMAX + 10];
static int maxedge[NMAX + MMAX + 10];

static void initialize_lct() {
    memset(parent, 0, sizeof(parent));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(reversed, false, sizeof(reversed));
    memset(maxedge, 0, sizeof(maxedge));
}

inline void pushdown(int x) {
    if (x > 0 && reversed[x]) {
        swap(left[x], right[x]);

        reversed[left[x]] ^= true;
        reversed[right[x]] ^= true;
        reversed[x] = false;
    }
}

inline int choose_max(int a, int b) {
    if (a == 0 || maxedge[a] == 0) {
        return maxedge[b];
    }

    if (b == 0 || maxedge[b] == 0) {
        return maxedge[a];
    }

    if (edges[maxedge[a]].b > edges[maxedge[b]].b) {
        return maxedge[a];
    } else {
        return maxedge[b];
    }
}

inline void update(int x) {
    maxedge[x] = choose_max(left[x], right[x]);

    if (x > n) {
        int e = x - n;

        if (edges[e].b > edges[maxedge[x]].b) {
            maxedge[x] = e;
        }
    }
}

static void left_rotate(int x) {
    assert(x > 0);
    assert(left[x] > 0);
    assert(!reversed[x]);
    assert(!reversed[left[x]]);

    int y = left[x];
    left[x] = right[y];
    if (left[x] > 0) {
        parent[left[x]] = x;
    }
    right[y] = x;

    if (parent[x] > 0) {
        if (left[parent[x]] == x) {
            left[parent[x]] = y;
        } else {
            right[parent[x]] = y;
        }
    }

    parent[y] = parent[x];
    parent[x] = y;

    update(x);
    update(y);
}

static void right_rotate(int x) {
    assert(x > 0);
    assert(right[x] > 0);
    assert(!reversed[x]);
    assert(!reversed[right[x]]);

    int y = right[x];
    right[x] = left[y];
    if (right[x] > 0) {
        parent[right[x]] = x;
    }
    left[y] = x;

    if (parent[x] > 0) {
        if (left[parent[x]] == x) {
            left[parent[x]] = y;
        } else {
            right[parent[x]] = y;
        }
    }

    parent[y] = parent[x];
    parent[x] = y;

    update(x);
    update(y);
}

static void clear_marks(int x) {
    if (x <= 0) {
        return;
    }

    clear_marks(parent[x]);
    pushdown(x);
}

static void splay(int x) {
    clear_marks(x);

    while (parent[x] > 0) {
        int p1 = parent[x];
        int p2 = parent[p1];

        if (p2 <= 0) {
            if (left[p1] == x) {
                left_rotate(p1);
            } else {
                right_rotate(p1);
            }
        } else {
            if (left[p1] == x) {
                if (left[p2] == p1) {
                    left_rotate(p2);
                    left_rotate(p1);
                } else {
                    left_rotate(p1);
                    right_rotate(p2);
                }
            } else {
                if (left[p2] == p1) {
                    right_rotate(p1);
                    left_rotate(p2);
                } else {
                    right_rotate(p2);
                    right_rotate(p1);
                }
            }
        }
    }  // while
}

static void access(int x) {
    splay(x);
    parent[right[x]] = -x;
    right[x] = 0;
    update(x);

    while (parent[x] != 0) {
        int top = -parent[x];

        splay(top);
        parent[right[top]] = -top;
        parent[x] = top;
        right[top] = x;
        update(top);

        x = top;
    }  // while
}

static void link(int x, int y) {
    access(x);
    splay(x);
    parent[y] = x;
    right[x] = y;
    update(x);
}

static void cut(int x, int f) {
    access(f);
    splay(x);
    parent[x] = 0;
}

static void make_root(int x) {
    access(x);
    splay(x);
    reversed[x] ^= true;
}

static int find_root(int x) {
    access(x);
    splay(x);
    while (left[x] != 0) {
        x = left[x];
    }  // while
    splay(x);
    return x;
}

static bool cmp(const Edge *a, const Edge *b) {
    return a->a < b->a;
}

static void read_graph() {
    for (int i = 1; i <= m; i++) {
        Edge &e = edges[i];
        scanf("%d%d%d%d", &e.u, &e.v, &e.a, &e.b);
        e.id = i;
        sorted[i] = &e;
    }  // for

    // sort(sorted + 1, sorted + m + 1,
    // [](const Edge *a, const Edge *b) { return a->b < b->b; });
    // /*stable_*/ sort(sorted + 1, sorted + m + 1,
    // [](const Edge *a, const Edge *b) { return a->a < b->a; });
    sort(sorted + 1, sorted + m + 1, cmp);
}

static void initialize() {
    scanf("%d%d", &n, &m);

    read_graph();
    initialize_lct();
}

int main() {
    initialize();

    int p = 1;
    int answer = INT_MAX;
    while (p <= m) {
        // printf("Considering %d...\n", p);
        Edge *e = sorted[p++];
        int u = e->u, v = e->v;

        if (u == v) {
            continue;
        }

        if (find_root(u) != find_root(v)) {
            make_root(v);
            link(u, e->id + n);
            link(e->id + n, v);

            // printf("Selected %d -- %d (%d, %d)\n", u, v, e->a, e->b);
        } else {
            make_root(u);
            access(v);
            splay(v);

            int t = maxedge[v];

            if (e->b < edges[t].b) {
                // printf("Selected %d -- %d (%d, %d);
                // Replaced %d -- %d (%d,
                // %d)\n",
                // u, v, e->a, e->b, edges[t].u, edges[t].v, edges[t].a,
                // edges[t].b);

                make_root(t + n);
                cut(edges[t].u, t + n);
                cut(edges[t].v, t + n);

                make_root(v);
                link(u, e->id + n);
                link(e->id + n, v);
            }
        }

        if (find_root(1) == find_root(n)) {
            make_root(1);
            access(n);
            splay(1);
            int amax = sorted[p - 1]->a, bmax = edges[maxedge[1]].b;
            answer = min(answer, amax + bmax);
        }
    }  // while

    if (answer == INT_MAX) {
        puts("-1");
    } else {
        printf("%d\n", answer);
    }

    return 0;
}  // function main
