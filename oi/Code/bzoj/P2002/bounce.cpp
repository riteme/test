#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;

// LCT
static int parent[NMAX + 10];
static int size[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];

static void initialize_lct() {
    for (int i = 1; i <= n + 1; i++) {
        parent[i] = 0;
        size[i] = 1;
        left[i] = 0;
        right[i] = 0;
    }  // for

    parent[0] = size[0] = left[0] = right[0] = 0;
}

inline void update(int x) {
    size[x] = size[left[x]] + size[right[x]] + 1;
}

inline int left_rotate(int x) {
    assert(x != 0);
    assert(left[x] != 0);

    int y = left[x];
    left[x] = right[y];
    parent[left[x]] = x;
    right[y] = x;

    if (parent[x] > 0) {
        if (x == left[parent[x]])
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    } else  // parent[x] <= 0
        parent[y] = parent[x];

    parent[y] = parent[x];
    parent[x] = y;

    update(x);
    update(y);

    return x;
}

inline int right_rotate(int x) {
    assert(x != 0);
    assert(right[x] != 0);

    int y = right[x];
    right[x] = left[y];
    parent[right[x]] = x;
    left[y] = x;

    if (parent[x] > 0) {
        if (x == left[parent[x]])
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    } else  // parent[x] <= 0
        parent[y] = parent[x];

    parent[y] = parent[x];
    parent[x] = y;

    update(x);
    update(y);

    return x;
}

inline void splay(int x) {
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
    update(x);
}

inline void disconnect(int x) {
    assert(x != 0);

    splay(x);
    if (right[x] > 0) {
        parent[right[x]] = -x;
        right[x] = 0;
        update(x);
    }
}

static void access(int x) {
    disconnect(x);

    while (parent[x] != 0) {
        int top = -parent[x];
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
    // assert(father(x) != 0);

    int f = father(x);
    access(f);
    splay(x);
    parent[x] = 0;
}

static void link(int x, int y) {
    assert(left[y] == 0);

    access(x);
    splay(y);
    connect(x, y);
}

static void print() {
    for (int i = 1; i <= n + 1; i++) {
        printf(
            "parent[%d] = %d, left[%d] = %d, right[%d] = %d, size[%d] = %d\n",
            i, parent[i], i, left[i], i, right[i], i, size[i]);
    }  // for
}

static void initialize() {
    scanf("%d", &n);
    initialize_lct();

    for (int i = 1; i <= n; i++) {
        int next;
        scanf("%d", &next);

        if (i + next > n) {
            link(n + 1, i);
        } else {
            link(i + next, i);
        }
    }  // for
    // print();
}

int main() {
    initialize();

    int m;
    scanf("%d", &m);
    while (m > 0) {
        int command, x, y;
        scanf("%d", &command);

        switch (command) {
            case 1:
                scanf("%d", &x);
                x++;
                access(x);

                if (parent[x] > 0) {
                    splay(x);
                }

                printf("%d\n", size[left[x]]);
                break;

            case 2:
                scanf("%d%d", &x, &y);
                x++;
                // print();
                cut(x);

                if (x + y > n) {
                    link(n + 1, x);
                } else {
                    link(x + y, x);
                }
                break;
        }  // switch to command

        m--;
    }  // while

    return 0;
}  // function main
