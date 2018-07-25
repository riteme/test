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

    return x;
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

static bool marked[NMAX + 10];
static int size[NMAX + 10];
static int depth[NMAX + 10];
static int dist[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static vector<int> children[NMAX + 10];

static bool cmp(const int a, const int b) {
    return depth[a] < depth[b];
}

static void make_root(int x) {
    size[x] = 1;

    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (!marked[v]) {
            marked[v] = true;
            f[v][0] = x;
            dist[v] = dist[x] + e->w;
            depth[v] = depth[x] + 1;

            make_root(v);

            children[x].push_back(v);
            size[x] += size[v];
        }
    }  // for
}

static void make_root() {
    f[1][0] = 0;
    dist[1] = 0;
    depth[1] = 0;
    marked[1] = true;
    make_root(1);
}

static vector<int> roots;
static int top[NMAX + 10];
static int first[NMAX + 10];
static int last[NMAX + 10];
static int tree[NMAX + 10];

static void decompose(int x) {
    int next = 0;
    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (size[v] > size[next]) {
            next = v;
        }
    }  // for

    if (next) {
        top[next] = top[x];
        last[top[x]] = next;
        tree[top[x]] = Splay::insert(tree[top[x]], next, cmp);
        decompose(next);
    }

    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (v != next) {
            top[v] = v;
            first[v] = v;
            last[v] = v;
            tree[v] = v;
            roots.push_back(v);

            decompose(v);
        }
    }  // for
}

static void decompose() {
    top[1] = 1;
    first[1] = 1;
    last[1] = 1;
    tree[1] = 1;
    roots.push_back(1);

    decompose(1);
}

static void initialize_lca() {
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }  // for
    }      // for
}

static int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    int distance = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if (distance & (1 << i)) {
            u = f[u][i];
        }
    }  // for

    if (u == v) {
        return u;
    }

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }  // for

    return f[u][0];
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
    make_root();
    decompose();
    initialize_lca();
}

inline int _distance(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return dist[a] + dist[b] - 2 * dist[lca(a, b)];
}

static int p1, p2;

static int compute_max() {
    int answer = 0;
    for (unsigned i = 0; i < roots.size(); i++) {
        int c = roots[i];
        if (dist[last[c]] - dist[first[c]] > answer) {
            answer = dist[last[c]] - dist[first[c]];
            p1 = last[c];
            p2 = first[c];
        }
    }  // for

    for (unsigned i = 0; i < roots.size(); i++) {
        for (unsigned j = i + 1; j < roots.size(); j++) {
            int a = roots[i];
            int b = roots[j];

            if (_distance(first[a], first[b]) > answer) {
                answer = _distance(first[a], first[b]);
                p1 = first[a];
                p2 = first[b];
            }
            if (_distance(first[a], last[b]) > answer) {
                answer = _distance(first[a], last[b]);
                p1 = first[a];
                p2 = last[b];
            }
            if (_distance(last[a], first[b]) > answer) {
                answer = _distance(last[a], first[b]);
                p1 = last[a];
                p2 = first[b];
            }
            if (_distance(last[a], last[b]) > answer) {
                answer = _distance(last[a], last[b]);
                p1 = last[a];
                p2 = last[b];
            }
        }  // for
    }      // for

    return answer;
}

static int whitecnt;
static bool is_white[NMAX + 10];

static void print() {
    printf("whitecnt = %d\n", whitecnt);
    for (unsigned i = 0; i < roots.size(); i++) {
        int c = roots[i];
        printf("chain %d: first = %d, last = %d, tree = %d\n", c, first[c],
               last[c], tree[c]);
    }  // for

    putchar('\n');
}

int main() {
    initialize();
    // puts("Initialized.");

    whitecnt = n;
    for (int i = 1; i <= n; i++) {
        is_white[i] = true;
    }  // for

    int answer = compute_max();

    int q;
    char command[2];
    scanf("%d", &q);
    while (q > 0) {
        // print();
        scanf("%s", command);

        switch (command[0]) {
            case 'A': {
                if (answer < 0) {
                    puts(INVALID_SAY);
                } else {
                    printf("%d\n", answer);
                }
            } break;
            case 'C': {
                int u;
                scanf("%d", &u);

                if (!is_white[u]) {
                    is_white[u] = true;
                    whitecnt++;

                    int t = top[u];
                    tree[t] = Splay::insert(tree[t], u, cmp);

                    // Update first & last
                    if (Splay::left[u] == 0) {
                        first[t] = u;
                    }
                    if (Splay::right[u] == 0) {
                        last[t] = u;
                    }

                    for (unsigned i = 0; i < roots.size(); i++) {
                        int c = roots[i];

                        if (_distance(first[c], u) > answer) {
                            answer = _distance(first[c], u);
                            p1 = u;
                            p2 = first[c];
                        }
                        if (_distance(last[c], u) > answer) {
                            answer = _distance(last[c], u);
                            p1 = u;
                            p2 = last[c];
                        }
                    }  // for
                } else {
                    is_white[u] = false;
                    whitecnt--;

                    int t = top[u];
                    tree[t] = Splay::remove(u);
                    first[t] = Splay::min_node(tree[t]);
                    last[t] = Splay::max_node(tree[t]);

                    if (whitecnt == 0) {
                        answer = -1;
                    } else if (whitecnt == 1) {
                        answer = 0;
                    } else if (u == p1 || u == p2) {
                        answer = compute_max();
                    }
                }
            } break;
        }  // switch to command[0]

        q--;
    }  // while

    return 0;
}  // function main
