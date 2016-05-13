#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 20

#define INVALID_SAY "They have disappeared."

struct Edge {
    int u;
    int v;
    int w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n;
static vector<Edge *> G[NMAX + 10];

namespace Splay {
static int parent[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];

static void left_rotate(int x) {
    int y = left[x];
    left[x] = right[y];
    if (left[x]) {
        parent[left[x]] = x;
    }
    right[y] = x;

    if (parent[x]) {
        if (left[parent[x]] == x) {
            left[parent[x]] = y;
        } else {
            right[parent[x]] = y;
        }
    }

    parent[y] = parent[x];
    parent[x] = y;
}

static void right_rotate(int x) {
    int y = right[x];
    right[x] = left[y];
    if (right[x]) {
        parent[right[x]] = x;
    }
    left[y] = x;

    if (parent[x]) {
        if (left[parent[x]] == x) {
            left[parent[x]] = y;
        } else {
            right[parent[x]] = y;
        }
    }

    parent[y] = parent[x];
    parent[x] = y;
}

static int splay(int x) {
    while (parent[x]) {
        int p1 = parent[x];
        int p2 = parent[p1];

        if (p2 == 0) {
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

    return x;
}

static int min_node(int x) {
    while (left[x]) {
        x = left[x];
    }  // while

    splay(x);
    return x;
}

static int max_node(int x) {
    while (right[x]) {
        x = right[x];
    }  // while

    splay(x);
    return x;
}

template <typename TCompare>
static int _insert(int x, int v, TCompare &cmp) {
    if (!x) {
        return v;
    }

    if (cmp(v, x)) {
        left[x] = _insert(left[x], v, cmp);
        parent[left[x]] = x;
    } else {
        right[x] = _insert(right[x], v, cmp);
        parent[right[x]] = x;
    }
}

template <typename TCompare>
static int insert(int x, int v, TCompare &cmp) {
    _insert(x, v, cmp);
    return splay(v);
}

static int remove(int x) {
    splay(x);
    int l = left[x];
    int r = right[x];

    parent[l] = parent[r] = left[x] = right[x] = 0;

    if (!l) {
        return r;
    } else if (!r) {
        return l;
    } else {
        int m = max_node(l);
        // splay(m);
        right[m] = r;
        parent[r] = m;

        return m;
    }
}

}  // namespace Splay

static vector<int> roots;
static int size[NMAX + 10];
static int dist[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static vector<int> children[NMAX + 10];
static int top[NMAX + 10];
static int tree[NMAX + 10];
static int first[NMAX + 10];
static int second[NMAX + 10];

static void make_root() {
    f[1][0] = 0;
}

inline void add_edge(int u, int v, int w) {
    Edge *e = new Edge;

    e->u = u;
    e->v = v;
    e->w = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static void read_graph() {
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        add_edge(u, v, c);
    }  // for
}

static void initialize() {
    scanf("%d", &n);

    read_graph();
}

int main() {
    initialize();

    return 0;
}  // function main
