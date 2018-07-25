// 借教室
// Codevs: AC
// Vijos: 4 TLE

#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 1000000
#define MEMORY_SIZE 2097151

#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)
#define PARENT(x) (x >> 1)

// #define FMT "%lld"
// typedef long long ntype;
#define FMT "%d"
typedef int ntype;

struct Reservation {
    Reservation() : start(0), end(0), need(0) {}
    Reservation(ntype s, ntype t, ntype d) : start(s), end(t), need(d) {}

    ntype start;
    ntype end;
    ntype need;
};  // struct Reservation

struct Node {
    Node() : pos(1), l(0), r(0), sum(0) {}
    Node(ntype _l, ntype _r) : pos(1), l(_l), r(_r), sum(0) {}

    ntype pos;
    ntype l;
    ntype r;
    ntype sum;
};

static ntype n, m;
static ntype r[NMAX + 10];
static Reservation q[MMAX + 10];
static Node heap[MEMORY_SIZE];
static bool flag;
static ntype id;

Node *build_tree(ntype lb, ntype rb, ntype p = 1);
void insert(ntype s, ntype t, ntype value, ntype p = 1);
ntype query(ntype d, ntype p = 1);

inline ntype read() {
    ntype x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}

void initialize();
void quit();

int main() {
    initialize();

    for (int i = 1; i <= m; i++) {
        insert(q[i].start, q[i].end, -q[i].need, 1);
    }  // for

    ntype j = m + 1;
    for (ntype i = 1; i <= n; i++) {
        while (query(i, 1) < 0) {
            j--;
            insert(q[j].start, q[j].end, q[j].need, 1);
        }  // while
    }      // for

    if (j != m + 1) {
        flag = true;
        id = j;
    }

    quit();
    return 0;
}  // function main

void initialize() {
    n = read();
    m = read();

    for (int i = 1; i <= n; i++) r[i] = read();
    for (int i = 1; i <= m; i++)
        q[i].need = read(), q[i].start = read(), q[i].end = read();

    flag = false;
    id = 0;

    build_tree(1, n);
}

void quit() {
    if (!flag)
        puts("0");
    else {
        puts("-1");
        printf(FMT, id);
    }
}

Node *build_tree(ntype lb, ntype rb, ntype p) {
    Node *x = &heap[p];
    x->l = lb;
    x->r = rb;

    if (lb != rb) {
        ntype mid = (lb + rb) / 2;
        build_tree(lb, mid, LEFT(p));
        build_tree(mid + 1, rb, RIGHT(p));
        x->sum = 0;
    } else
        x->sum = r[lb];

    return x;
}

void insert(ntype s, ntype t, ntype value, ntype p) {
    Node *x = &heap[p];

    if (s <= x->l and x->r <= t)
        x->sum += value;
    else {
        ntype mid = (x->l + x->r) / 2;

        if (t <= mid)
            insert(s, t, value, LEFT(p));
        else if (s > mid)
            insert(s, t, value, RIGHT(p));
        else {
            insert(s, t, value, LEFT(p));
            insert(s, t, value, RIGHT(p));
        }
    }
}

ntype query(ntype d, ntype p) {
    ntype result = 0;

recursive:
    Node *x = &heap[p];

    if (d == x->l and d == x->r) return result + x->sum;

    result += x->sum;
    ntype mid = (x->l + x->r) / 2;

    if (d <= mid)
        p = LEFT(p);
    else
        p = RIGHT(p);

    goto recursive;
}
