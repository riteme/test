#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 10000

static int n, m;

// LCT
static int parent[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static bool reversed[NMAX + 10];

static void print() {
    for (int i = 1; i <= n; i++) {
        printf(
            "parent[%d] = %d, left[%d] = %d, right[%d] = %d, reversed[% d] = % "
            "d\n ",
            i, parent[i], i, left[i], i, right[i], i, reversed[i]);
    }  // for
}

static void initialize_lct() {
    memset(parent, 0, sizeof(parent));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(reversed, 0, sizeof(reversed));
}

inline void pushdown(int x) {
    if (x > 0 && reversed[x]) {
        swap(left[x], right[x]);

        reversed[left[x]] ^= true;
        reversed[right[x]] ^= true;
        reversed[x] = false;
    }
}

inline int left_rotate(int x) {
    assert(x != 0);
    assert(left[x] != 0);
    assert(reversed[x] == false);
    assert(reversed[left[x]] == false);

    int y = left[x];
    left[x] = right[y];
    if (left[x] > 0)
        parent[left[x]] = x;
    right[y] = x;

    if (parent[x] > 0) {
        if (x == left[parent[x]])
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    }

    parent[y] = parent[x];
    parent[x] = y;

    return x;
}

inline int right_rotate(int x) {
    assert(x != 0);
    assert(right[x] != 0);
    assert(reversed[x] == false);
    assert(reversed[right[x]] == false);

    int y = right[x];
    right[x] = left[y];
    if (right[x] > 0)
        parent[right[x]] = x;
    left[y] = x;

    if (parent[x] > 0) {
        if (x == left[parent[x]])
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    }

    parent[y] = parent[x];
    parent[x] = y;

    return x;
}

static int stack[NMAX + 10];
inline void splay(int x) {
    int i = 0;
    for (int u = x; u > 0; u = parent[u]) {
        assert(i <= n);
        stack[++i] = u;
    }  // for

    for (; i > 0; i--) {
        pushdown(stack[i]);
    }  // for

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

// x -> y
inline void connect(int x, int y) {
    assert(x != 0);
    assert(y != 0);
    assert(right[x] == 0);
    assert(parent[y] <= 0);

    parent[y] = x;
    right[x] = y;
}

inline void disconnect(int x) {
    assert(x != 0);
    assert(parent[x] <= 0);

    if (right[x] > 0) {
        parent[right[x]] = -x;
        right[x] = 0;
    }
}

static void access(int x) {
    splay(x);
    disconnect(x);

    while (parent[x] != 0) {
        int top = -parent[x];

        assert(top > 0);
        splay(top);
        disconnect(top);
        connect(top, x);

        x = top;
    }  // while
}

inline int father(int x) {
    splay(x);
    if (left[x] == 0) {
        return -parent[x];
    } else {
        int f = left[x];
        while (right[f] != 0) {
            f = right[f];
        }  // while

        splay(f);
        return f;
    }
}

static void cut(int x) {
    assert(father(x) != 0);

    int f = father(x);
    access(f);
    splay(x);
    parent[x] = 0;
}

static void link(int x, int y) {
    assert(left[y] == 0 || (reversed[y] && right[y] == 0));

    access(x);
    splay(y);
    connect(x, y);
}

static void make_root(int x) {
    access(x);
    splay(x);
    reversed[x] ^= true;
}

static int find_root(int x) {
    access(x);

    splay(x);
    int top = x;
    while (left[top] != 0) {
        top = left[top];
    }  // while

    splay(top);
    return top;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    initialize_lct();
}

int main() {
    initialize();

    char buffer[10];
    int u, v;
    // int cnt = 0;
    while (m > 0) {
        scanf("%s%d%d", buffer, &u, &v);
        // printf("%d: %s %d %d\n", ++cnt, buffer, u, v);

        switch (buffer[0]) {
            case 'Q': {
                u = find_root(u);
                v = find_root(v);

                if (u == v)
                    puts("Yes");
                else
                    puts("No");
            } break;

            case 'C': {
                // if (find_root(u) != find_root(v)) {
                make_root(v);
                link(u, v);
                // }
            } break;

            case 'D': {
                if (find_root(u) == find_root(v)) {
                    if (father(v) == u)
                        cut(v);
                    else
                        cut(u);
                }
            } break;

            case 'F': {
                printf("%d, %d\n", find_root(u), find_root(v));
            } break;
        }  // switch to buffer[0]

        m--;
    }  // while

    return 0;
}  // function main
