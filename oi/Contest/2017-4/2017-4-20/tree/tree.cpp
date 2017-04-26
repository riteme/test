// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define SPSIZE (NMAX * 2)

class Splay {
 public:
    Splay() {
        memset(value, 0, sizeof(value));
        memset(sum, 0, sizeof(sum));
        memset(father, 0, sizeof(father));
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
    }

    void splay(int x, int to = 0) {
        assert(x);

        while (father[x] != to) {
            int f = father[x];
            int pf = father[f];
            
            if (pf != to) {
                if (f == left[pf] && x == left[f])
                    left_rotate(pf);
                else if (f == right[pf] && x == right[f])
                    right_rotate(pf);
            }

            if (x == left[f])
                left_rotate(f);
            else
                right_rotate(f);
        }
    }

    void modify(int x, int v) {
        splay(x);
        value[x] = v;
        sum[x] = v + sum[left[x]] + sum[right[x]];
    }

    int query(int l, int r) {
        splay(l);
        splay(r, l);
        return sum[left[r]];
    }

    int maxnode(int u) {
        while (right[u]) {
            u = right[u];
        }

        return u;
    }

    int minnode(int u) {
        while (left[u]) {
            u = left[u];
        }

        return u;
    }

    int prev(int u) {
        splay(u);
        return maxnode(left[u]);
    }

    int next(int u) {
        splay(u);
        return minnode(right[u]);
    }

    void update(int x) {
        assert(x);

        sum[x] = value[x] + sum[left[x]] + sum[right[x]];
    }

    int value[SPSIZE + 10];
    int sum[SPSIZE + 10];
    int father[SPSIZE + 10];
    int left[SPSIZE + 10];
    int right[SPSIZE + 10];

    void left_rotate(int x) {
        assert(x);
        assert(left[x]);

        int y = left[x];
        left[x] = right[y];
        right[y] = x;

        if (left[x])
            father[left[x]] = x;
        father[y] = father[x];
        father[x] = y;
        if (father[y]) {
            if (x == left[father[y]])
                left[father[y]] = y;
            else
                right[father[y]] = y;
        }

        sum[y] = sum[x];
        sum[x] = value[x] + sum[left[x]] + sum[right[x]];
    }

    void right_rotate(int x) {
        assert(x);
        assert(right[x]);

        int y = right[x];
        right[x] = left[y];
        left[y] = x;

        if (right[x])
            father[right[x]] = x;
        father[y] = father[x];
        father[x] = y;
        if (father[y]) {
            if (x == left[father[y]])
                left[father[y]] = y;
            else
                right[father[y]] = y;
        }

        sum[y] = sum[x];
        sum[x] = value[x] + sum[left[x]] + sum[right[x]];
    }

    void print_and_check(int u) {
        if (!u)
            return;

        print_and_check(left[u]);
        if (left[u])
            assert(father[left[u]] == u);
        printf("%d ", u);
        print_and_check(right[u]);
        if (right[u])
            assert(father[right[u]] == u);
    }
};

static int n, q;
static Splay sp;
static set<int> left;

typedef set<int>::iterator iterator_t;

void initialize() {
    scanf("%d%d", &n, &q);

    int w;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w);
        sp.value[i] = sp.sum[i] = w;
    }

    sp.right[n + n] = n + 1;
    sp.father[n + 1] = n + n;
    for (int i = n; i >= 2; i--) {
        if (i < n) {
            sp.right[n + i] = i + 1;
            sp.father[i + 1] = n + i;
            sp.sum[n + i] += sp.sum[i + 1];
        }

        sp.right[i] = n + i;
        sp.father[n + i] = i;
        sp.sum[i] += sp.sum[n + i];
    }

    sp.right[1] = 2;
    sp.father[2] = 1;
    sp.sum[1] += sp.sum[2];

    sp.right[n + 1] = n * 2 + 1;
    sp.father[n * 2 + 1] = n + 1;
    
    sp.right[n * 2 + 2] = 1;
    sp.father[1] = n * 2 + 2;
    sp.sum[n * 2 + 2] = sp.sum[1];

    left.insert(1);
    left.insert(2);
    left.insert(n + 1);
}

void change(int x, int l, int r) {
    int u = l;
    for (iterator_t beg = left.upper_bound(l);
         u <= r;) {
        int v = min(r, *beg - 1);
        int p = sp.prev(u), q = sp.next(n + v);
        assert(p);
        assert(q);
        u = v + 1;

        sp.splay(p);
        sp.splay(q, p);
        int root = sp.left[q];
        assert(root);
        sp.left[q] = 0;
        sp.father[root] = 0;
        sp.update(q);

        root = sp.minnode(root);
        sp.splay(root);

        sp.splay(x);
        sp.splay(n + x, x);
        sp.left[root] = sp.left[n + x];
        sp.left[n + x] = root;
        sp.father[sp.left[root]] = root;
        sp.father[root] = n + x;
        sp.update(root);
        sp.update(x);

        iterator_t tmp = beg;
        beg++;

        if (*tmp <= r)
            left.erase(tmp);
    }

    left.insert(l);
    left.insert(r + 1);
}

void modify(int x, int v) {
    sp.modify(x, v);
}

int query(int x) {
    int p = sp.prev(x), q = sp.next(n + x);
    assert(p);
    assert(q);
    sp.splay(p);
    sp.splay(q, p);
    return sp.sum[sp.left[q]];
}

int main() {
    // freopen("data.in", "r", stdin);
#ifdef USE_FILE_IO
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#endif
    initialize();

    while (q--) {
        int t;
        scanf("%d", &t);

        switch (t) {
            case 0: {
                int x, l, r;
                scanf("%d%d%d", &x, &l, &r);

                // for (int i = 1; i <= SPSIZE; i++) {
                //     if (sp.father[i] == 0) {
                //         sp.print_and_check(i);
                //         printf("\n");
                //         break;
                //     }
                // }

                change(x, l, r);
            } break;

            case 1: {
                int x, v;
                scanf("%d%d", &x, &v);
                modify(x, v);
            } break;

            case 2: {
                int x;
                scanf("%d", &x);
                printf("%d\n", query(x));
            } break;
        }
    }

    return 0;
}
