// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LCTSIZE (NMAX * 2)

class FenwickArray {
 public:
    FenwickArray() {
        memset(arr, 0, sizeof(arr));
    }

    void initialize(int _n, int *_arr) {
        n = _n;

        for (int i = 1; i <= n; i++) {
            _modify(i, _arr[i]);
        }
    }

    void modify(int x, int val) {
        _modify(x, val);
    }

    int query(int l, int r) {
        return _query(r) - _query(l);
    }

 private:
    int n;
    int arr[NMAX + 10];

    void _modify(int x, int val) {
        for (; x <= n; x += x & (-x)) {
            arr[x] += val;
        }
    }

    int _query(int x) {
        int ret = 0;

        for (; x; x -= x & (-x)) {
            ret += arr[x];
        }

        return ret;
    }
};

class LCT {
 public:
    LCT() {
        memset(mark, 0, sizeof(mark));
        memset(value, 0, sizeof(mark));
        memset(father, 0, sizeof(father));
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
    }

    void splay(int x) {
        assert(x);
        clear_marks(x);

        while (father[x] > 0) {
            int f = father[x];
            int pf = father[f];

            if (pf > 0) {
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

    void access(int x) {
        assert(x);

        splay(x);
        father[right[x]] = -x;
        right[x] = 0;

        while (father[x]) {
            int u = -father[x];
            assert(top > 0);

            splay(u);
            father[right[u]] = -u;
            father[x] = u;
            right[u] = x;
            x = u;
        }
    }

    void link(int u, int v) {
        splay(v);
        assert(father[v] == 0);

        access(u);
        splay(u);
        father[v] = u;
        right[u] = v;
    }

    void cut(int u) {
        access(u);
        splay(u);

        int f = left[u];
        while (right[f]) {
            f = right[f];
        }

        access(f);
        father[u] = 0;
    }

    void modify(int x, int val) {
        access(x);
        splay(x);
        mark[x] += val;
    }

    int mark[LCTSIZE + 10];
    int value[LCTSIZE + 10];
    
 private:
    int father[LCTSIZE + 10];
    int left[LCTSIZE + 10];
    int right[LCTSIZE + 10];

    void pushdown(int x) {
        assert(x);

        if (mark[x]) {
            value[x] += mark[x];
            mark[left[x]] += mark[x];
            mark[right[x]] += mark[x];
            mark[x] = 0;
        }
    }

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
        if (father[y] > 0) {
            if (x == left[father[y]])
                left[father[y]] = y;
            else
                right[father[y]] = y;
        }
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
        if (father[y] > 0) {
            if (x == left[father[y]])
                left[father[y]] = y;
            else
                right[father[y]] = y;
        }
    }

    void clear_marks(int x) {
        if (father[x] > 0)
            clear_marks(x);
        pushdown(x);
    }
};

static int n, q;
static int val[NMAX + 10];
static FenwickArray arr;
static LCT lct;
static set<int> real;
static set<int> left;

typedef set<int>::iterator iterator_t;

void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d", val + i);
    }

    arr.initialize(n, val);
    left.insert(2);
    left.insert(n + 1);
    lct.value[1] = val[1];
    lct.value[n + 2] = arr->query(2, n);
    lct.link(1, n + 2);
}

template <typename T>
inline T nxt(T iter) {
    iter++;
    return iter;
}

template <typename T>
inline T pre(T iter) {
    iter--;
    return iter;
}

inline int father(int x) {
    return n + *(--left.upper_bound(x));
}

void change(int x, int l, int r) {
    iterator_t beg;
    for (beg = real.lower_bound(l);
         beg != real.end() && *beg <= r;) {
        int v = *beg;
        lct.modify(v, -val[v]);
        lct.cut(v);

        iterator_t tmp = beg;
        beg++;
        real.erase(tmp);
    }

    beg = left.upper_bound(l);
    assert(beg != left.begin());
    lct.modify(n + *pre(beg), -arr.query(l, *beg - 1));

    for (beg = left.lower_bound(l);
         nxt(beg) != left.end() && *nxt(beg) - 1 <= r;) {
        int l = *beg;
        int r = *nxt(beg) - 1;
        lct.modify(n + l, -arr.query(l, r));
        lct.cut(n + l);

        iterator_t tmp = beg;
        beg++;
        left.erase(tmp);
    }

    if (*beg != n + 1) {
        lct.modify(n + *beg, -arr.query(*beg, r));
        left.erase(beg);
    }

    if (!real.count(x)) {
        assert(lct.value[x] == 0);
        lct.link(father(x), x);
        lct.modify(x, val[x]);
    }
}

void modify(int x, int v) {

}

int query(int x) {

}

int main() {
#ifdef NDEBUG
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#endif
    initialize();

    while (q--) {
        int type;
        scanf("%d", &type);

        switch (type) {
            case 0: {
                int x, l, r;
                scanf("%d%d%d", &x, &l, &r);
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
