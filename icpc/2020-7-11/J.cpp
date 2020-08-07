// #define NDEBUG
#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long i64;

#define MEMSIZE 3000000
#define NMAX 100000

struct Node {
    int l, r;
    i64 sum, mark;
    Node *lch, *rch;

    i64 gsum() {
        return sum + mark * (r - l + 1);
    }

    void update() {
        sum = lch->gsum() + rch->gsum();
    }

    // void push() {
    //     if (mark) {
    //         sum += mark * (r - l + 1);
    //         assert(lch);
    //         lch->mark += mark;
    //         rch->mark += mark;
    //         mark = 0;
    //     }
    // }
};

Node mem[MEMSIZE];
size_t mempos;

Node *allocate(int _l, int _r) {
    assert(mempos < MEMSIZE);
    Node *p = mem + mempos;
    mempos++;
    p->l = _l;
    p->r = _r;
    p->sum = p->mark = 0;
    p->lch = p->rch = 0;
    return p;
}

Node *copy(Node *x) {
    assert(mempos < MEMSIZE);
    Node *p = mem + mempos;
    mempos++;
    memcpy(p, x, sizeof(Node));
    return p;
}

i64 query(Node *x, int L, int R, i64 mark = 0) {
    if (L <= x->l && x->r <= R)
        return x->gsum() + mark * (x->r - x->l + 1);

    mark += x->mark;
    int m = (x->l + x->r) / 2;

    i64 rax = 0;
    if (L <= m)
        rax += query(x->lch, L, R, mark);
    if (R > m)
        rax += query(x->rch, L, R, mark);
    return rax;
}

Node *modify(Node *x, int L, int R, i64 v) {
    x = copy(x);

    if (L <= x->l && x->r <= R)
        x->mark += v;
    else {
        int m = (x->l + x->r) / 2;

        if (L <= m)
            x->lch = modify(x->lch, L, R, v);
        if (R > m)
            x->rch = modify(x->rch, L, R, v);

        x->update();
    }

    return x;
}

Node *build(int L, int R) {
    Node *x = allocate(L, R);
    if (L < R) {
        int m = (L + R) / 2;
        x->lch = build(L, m);
        x->rch = build(m + 1, R);
    }
    return x;
}

int n, q;
i64 a[NMAX + 10];
struct range {
    int l, r;
} ran[NMAX + 10];

i64 nsort(i64 x) {
    int d[10];
    for (int i = 0; i < 10; i++) {
        d[i] = x ? x % 10 + 1 : 0;
        x /= 10;
    }
    sort(d, d + 10);
    i64 v = 0;
    for (int i = 9; i >= 0; i--)
        v = v * 11 + d[i];
    return v;
}

Node *tr[NMAX + 10];

void initialize() {
    for (int i = 1; i <= n; i++) {
        i64 x;
        scanf("%lld", &x);
        a[i] = nsort(x);
    }

    unordered_map<i64, int> c1, c2;
    int pcnt = 0;
    int i, j = 1, k = 1;
    for (i = 1; i <= n; i++) {
        j = max(i, j);
        k = max(i, k);
        while (j <= n && c1[a[j]] < 1)
            c1[a[j++]]++;
        while (k <= n && ((pcnt == 0) ? (c2[a[k]] < 2) : (c2[a[k]] < 1))) {
            if (c2[a[k]] == 1)
                pcnt++;
            c2[a[k++]]++;
        }
        if (i < j)
            c1[a[i]]--;
        if (i < k) {
            if (c2[a[i]] == 2)
                pcnt--;
            c2[a[i]]--;
        }
        ran[i] = {j, k};
    }

    mempos = 0;
    tr[n + 1] = build(1, n);
    for (i = n; i >= 1; i--) {
        if (ran[i].l < ran[i].r)
            tr[i] = modify(tr[i + 1], ran[i].l, ran[i].r - 1, +1);
        else
            tr[i] = tr[i + 1];
    }
}

void _main() {
    initialize();

    i64 lastans = 0;
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l += lastans;
        r -= lastans;
        assert(1 <= l && l <= r && r <= n);
        // printf("query [%d, %d]\n", l, r);

        lastans = query(tr[l], l, r);
        printf("%lld\n", lastans);
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        _main();
    }

    return 0;
}