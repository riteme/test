#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100000

// Timer
static int timeit() {
    static int current = 1;
    return current++;
}

// Public Stack
static int stacksize;
static int _stack[NMAX + 10];

inline void refresh_stack() {
    stacksize = 0;
}

inline void push_stack(int x) {
    _stack[stacksize++] = x;
}

inline int pop_stack() {
    return _stack[--stacksize];
}

inline bool empty_stack() {
    return stacksize == 0;
}

class Heap {
 public:
};  // class Heap

// Declarations
static int n;
static vector<int> G[NMAX + 10];
static int center[NMAX + 10];
static int timestamp[NMAX + 10];
static Heap heap[NMAX + 10];

inline bool invalid_edge(int u, int v) {
    return timestamp[u] > timestamp[v];
}

// Choose center of subtree
static int size[NMAX + 10];
static int father[NMAX + 10];

static void update_size(int x) {
    push_stack(x);
    size[x] = 1;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!invalid_edge(x, v) && father[x] != v) {
            father[v] = x;

            update_size(v);
            size[x] += size[v];
        }
    }  // for
}

static int choose_center(int x) {
    refresh_stack();
    update_size(x);

    int c = 0;
    int m = INT_MAX;
    while (!empty_stack()) {
        int u = pop_stack();
        int maxsize = 0;

        for (unsigned i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (invalid_edge(u, v)) {
                continue;
            }

            if (v == father[u]) {
                maxsize = max(maxsize, size[v] - size[u]);
            } else {
                maxsize = max(maxsize, size[v]);
            }
        }  // for

        if (maxsize < m) {
            c = u;
            m = maxsize;
        }
    }  // while

    return c;
}

static void dfs(int x, int f) {
    center[x] = f;
    timestamp[x] = timeit();
    x = choose_center(x);

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (invalid_edge(x, v)) {
            continue;
        }

        dfs(v, x);

    }  // for
}

static void read_graph() {
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
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
