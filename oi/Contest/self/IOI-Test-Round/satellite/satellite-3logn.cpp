#include "satellite.h"

#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100

static int n;
static int nxt[NMAX + 10];

struct List {
    int head, tail;

    void initialize(int u) {
        head = tail = u;
    }

    void contract(const List &b) {
        if (head)
            nxt[tail] = b.head;
        else
            head = b.head;
        if (b.tail)
            tail = b.tail;
    }

    void output(int *a, int &p) {
        for (int i = head; i; i = nxt[i]) {
            a[p++] = i;
        }  // for
    }
};  // struct List

static int fa[NMAX + 10];
static List li[NMAX + 10];

inline int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}

inline void link(int u, int v) {
    u = find(u), v = find(v);

    if (u != v) {
        fa[u] = v;
        li[v].contract(li[u]);
    }
}

void initialize(int _n) {
    srand(time(0));
    n = _n;

    for (int i = 1; i <= n; i++) {
        li[i].initialize(i);
    }  // for
}

static int m;
static int seq[NMAX + 10];
static int l1, r1, q1[NMAX + 10], l2, r2, q2[NMAX + 10];

void search(int &u, int &v) {
    m = 0;
    for (int i = 1; i <= n; i++) {
        if (!fa[i])
            seq[m++] = i;
    }  // for

    for (int i = 0; i <= 6; i++) {
        l1 = l2 = r1 = r2 = 0;

        for (int j = 0; j < m; j++) {
            if ((seq[j] >> i) & 1)
                li[seq[j]].output(q1, r1);
            else
                li[seq[j]].output(q2, r2);
        }  // for

        if (query(q1, r1, q2, r2))
            break;
    }  // for

    r1--, r2--;
    while (l1 < r1) {
        int mid = (l1 + r1) / 2;

        if (query(q1 + l1, mid - l1 + 1, q2, r2 + 1))
            r1 = mid;
        else
            l1 = mid + 1;
    }  // while

    while (l2 < r2) {
        int mid = (l2 + r2) / 2;

        if (query(q1 + l1, 1, q2 + l2, mid - l2 + 1))
            r2 = mid;
        else
            l2 = mid + 1;
    }  // while

    u = q1[l1], v = q2[l2];
    link(u, v);
}
