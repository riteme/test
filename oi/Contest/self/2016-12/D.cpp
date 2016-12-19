#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 30000

static int n, m, q;
static int W[NMAX + 10];
static int opt[NMAX + 10];
static int U[NMAX + 10];
static int V[NMAX + 10];

#define LCTSIZE NMAX

class LCT {
 public:

    class Splays {
     public:
        void reset(int n) {
            memset(father, 0, sizeof(int) * (n + 1));
            memset(left, 0, sizeof(int) * (n + 1));
            memset(right, 0, sizeof(int) * (n + 1));
            memset(size, 0, sizeof(int) * (n + 1));
            memset(value, 0, sizeof(int) * (n + 1));
            memset(cnt, 0, sizeof(int) * 2 * (n + 1));
            memset(mark, 0, sizeof(int) * (n + 1));
            memset(reversed, 0, sizeof(bool) * (n + 1));
        }

        int father[LCTSIZE + 10];
        int left[LCTSIZE + 10];
        int right[LCTSIZE + 10];
        int size[LCTSIZE + 10];
        int value[LCTSIZE + 10];
        struct {
            int one;
            int none;
        } cnt[LCTSIZE + 10];
        int mark[LCTSIZE + 10];
        bool reversed[LCTSIZE + 10];

        void pushdown(int x) {
            if (!x)
                return;

            if (reversed[x]) {
                swap(left[x], right[x]);

                reversed[left[x]] ^= true;
                reversed[right[x]] ^= true;
                reversed[x] = false;
            }

            if (mark[x]) {
                value[x] = mark[x];
                mark[left[x]] = mark[x];
                mark[right[x]] = mark[x];

                cnt[x] = { 0, 0 };
                if (mark[x] == 1)
                    cnt[x].one = size[x];
                else
                    cnt[x].none = size[x];
                
                mark[x] = 0;
            }
        }

        void clear(int x) {
            if (x > 0) {
                clear(father[x]);
                pushdown(x);
            }
        }

        void update(int x) {
            pushdown(left[x]);
            pushdown(right[x]);

            if (!x)
                return;

            size[x] = 1;
            cnt[x] = { 0, 0 };

            if (value[x] == 1)
                cnt[x].one = 1;
            else if (value[x] == -1)
                cnt[x].none = 1;

            if (left[x]) {
                size[x] += size[left[x]];
                cnt[x].one += cnt[left[x]].one;
                cnt[x].none += cnt[left[x]].none;
            }

            if (right[x]) {
                size[x] += size[right[x]];
                cnt[x].one += cnt[right[x]].one;
                cnt[x].none += cnt[right[x]].none;
            }
        }

        void left_rotate(int x) {
            assert(x);
            assert(left[x]);

            int y = left[x];
            father[right[y]] = x;
            left[x] = right[y];
            right[y] = x;

            if (father[x] > 0) {
                if (x == left[father[x]])
                    left[father[x]] = y;
                else
                    right[father[x]] = y;
            }

            father[y] = father[x];
            father[x] = y;

            update(x);
            update(y);
        }

        void right_rotate(int x) {
            assert(x);
            assert(right[x]);

            int y = right[x];
            father[left[y]] = x;
            right[x] = left[y];
            left[y] = x;

            if (father[x] > 0) {
                if (x == left[father[x]])
                    left[father[x]] = y;
                else
                    right[father[x]] = y;
            }

            father[y] = father[x];
            father[x] = y;

            update(x);
            update(y);
        }

        void splay(int x) {
            if (x == 0)
                return;

            clear(x);

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

        int kth(int x, int k) {
            pushdown(x);

            while (x != 0) {
                pushdown(left[x]);
                int leftsize = left[x] ? size[left[x]] : 0;

                if (leftsize >= k)
                    x = left[x];
                else if (leftsize + 1 == k)
                    break;
                else {
                    k -= leftsize + 1;
                    pushdown(right[x]);
                    x = right[x];
                }
            }

            splay(x);
            return x;
        }

        void refresh(int x, int *arr) {
            if (!x)
                return;

            pushdown(x);
            refresh(left[x], arr);
            refresh(right[x], arr);
            value[x] = arr[x];
            update(x);
        }
    };

    void reset(int n) {
        sp.reset(n);
    }

    Splays sp;

    void access(int x) {
        sp.splay(x);
        sp.father[sp.right[x]] = -x;
        sp.right[x] = 0;
        sp.update(x);

        while (sp.father[x] != 0) {
            assert(sp.father[x] < 0);
            int top = -sp.father[x];
            sp.splay(top);

            assert(!sp.reversed[top]);
            sp.father[sp.right[top]] = -top;
            sp.father[x] = top;
            sp.right[top] = x;
            sp.update(top);

            x = top;
        }
    }

    void make_root(int x) {
        access(x);
        sp.splay(x);

        assert(sp.father[x] == 0);
        sp.reversed[x] ^= true;
    }

    int father(int x) {
        sp.splay(x);

        if (sp.left[x])
            return sp.left[x];
        else
            return -sp.father[x];
    }

    int find_root(int x) {
        sp.splay(x);

        while (sp.father[x] != 0) {
            assert(sp.father[x] < 0);
            x = -sp.father[x];
            sp.splay(x);
        }

        while (sp.left[x]) {
            x = sp.left[x];
        }

        return x;
    }

    void cut(int x) {
        int f = father(x);

        if (f == 0)
            return;

        access(f);
        sp.splay(x);
        sp.father[x] = 0;
    }

    void link(int x, int y) {
        make_root(y);
        sp.father[y] = -x;
        access(y);
    }
};

static LCT lct;

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    lct.reset(n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", W + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        lct.link(u, v);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", opt + i, U + i, V + i);
    }
}

static void sort(int x) {
    int u = U[x];
    int v = V[x];
    lct.make_root(u);
    lct.access(v);
    lct.sp.splay(v);
    int lcnt = lct.sp.cnt[v].none;
    int rcnt = lct.sp.cnt[v].one;
    int lmask = -1;
    int rmask = 1;
    int all = lct.sp.size[v];

    if (opt[x] == 1) {
        swap(lcnt, rcnt);
        swap(lmask, rmask);
    }

    if (lcnt + rcnt < all) {
        int mid = lct.sp.kth(v, lcnt + 1);
        assert(mid);
        assert(lct.sp.father[mid] <= 0);
        assert(!lct.sp.reversed[mid]);

        lct.sp.value[mid] = 0;
        lct.sp.update(mid);
        lct.sp.mark[lct.sp.left[mid]] = lmask;
        lct.sp.mark[lct.sp.right[mid]] = rmask;
    } else {
        if (lcnt == all || rcnt == all)
            return;

        int mid = lct.sp.kth(v, lcnt + 1);
        assert(mid);
        assert(lct.sp.father[mid] <= 0);
        assert(!lct.sp.reversed[mid]);

        lct.sp.value[mid] = rmask;
        lct.sp.update(mid);
        lct.sp.mark[lct.sp.left[mid]] = lmask;
        lct.sp.mark[lct.sp.right[mid]] = rmask;
    }
}

static void perform() {
    for (int i = 1; i <= m; i++) {
        sort(i);
    }
}

static int seq[NMAX + 10];

static int evaluate(int x) {
    for (int i = 1; i <= n; i++) {
        if (W[i] < x)
            seq[i] = -1;
        else if (W[i] > x)
            seq[i] = 1;
        else
            seq[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (lct.sp.father[i] <= 0)
            lct.sp.refresh(i, seq);
    }

    perform();

    lct.sp.splay(q);
    return lct.sp.value[q];
}

int main() {
    initialize();

    int left = 1, right = n;
    while (left < right) {
        int mid = (left + right) / 2;
        int result = evaluate(mid);
        if (result < 0)
            right = mid - 1;
        else if (result > 0)
            left = mid + 1;
        else {
            left = mid;
            break;
        }
    }

    printf("%d\n", left);

    return 0;
}
