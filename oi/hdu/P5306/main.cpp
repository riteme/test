#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long i64;

int n, q;
int a[NMAX + 10];

struct Node {
    Node(int L, int R)
    : l(L), r(R), vmx0(-1), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
            fetch();
        } else {
            mx0 = a[l];
            c0 = 1;
            mx1 = -1;
            sum = a[l];
        }
    }

    ~Node() {
        if (lch) {
            delete lch;
            delete rch;
        }
    }

    void _update_mx0(int v) {
        if (v >= mx0)
            return;
        sum -= (i64) c0 * (mx0 - v);
        vmx0 = mx0 = v;
    }

    void update_mx0(int v) {
        if (v >= mx0)
            return;
        if (v > mx1) {
            sum -= (i64) c0 * (mx0 - v);
            vmx0 = mx0 = v;
        } else {
            commit();
            lch->update_mx0(v);
            rch->update_mx0(v);
            fetch();
        }
    }

    void commit() {
        if (vmx0 >= 0) {
            lch->_update_mx0(vmx0);
            rch->_update_mx0(vmx0);
            vmx0 = -1;
        }
    }

    void fetch() {
        mx0 = lch->mx0;
        c0 = lch->c0;
        mx1 = lch->mx1;

        if (rch->mx0 > mx0) {
            mx1 = mx0;
            mx0 = rch->mx0;
            c0 = rch->c0;
        } else if (rch->mx0 == mx0) {
            c0 += rch->c0;
        } else if (rch->mx0 > mx1) {
            mx1 = rch->mx0;
        }

        if (rch->mx1 > mx1) {
            mx1 = rch->mx1;
        }

        sum = lch->sum + rch->sum;
    }

    i64 query_sum(int L, int R) {
        if (L <= l && r <= R)
            return sum;

        commit();
        int m = (l + r) / 2;
        i64 rax = 0;
        if (L <= m)
            rax += lch->query_sum(L, R);
        if (R > m)
            rax += rch->query_sum(L, R);

        return rax;
    }

    int query_max(int L, int R) {
        if (L <= l && r <= R)
            return mx0;

        commit();
        int m = (l + r) / 2;
        int rax = 0;
        if (L <= m)
            rax = max(rax, lch->query_max(L, R));
        if (R > m)
            rax = max(rax, rch->query_max(L, R));

        return rax;
    }

    void cut_min(int L, int R, int v) {
        if (L <= l && r <= R) {
            update_mx0(v);
        } else {
            commit();
            int m = (l + r) / 2;
            if (L <= m)
                lch->cut_min(L, R, v);
            if (R > m)
                rch->cut_min(L, R, v);
            fetch();
        }
    }

    int l, r;
    int mx0, vmx0, c0, mx1;
    i64 sum;
    Node *lch, *rch;
};

void _main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    Node *tr = new Node(1, n);
    while (q--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);

        if (op == 0) {
            int v;
            scanf("%d", &v);
            tr->cut_min(l, r, v);
        } else if (op == 1) {
            printf("%d\n", tr->query_max(l, r));
        } else {
            printf("%lld\n", tr->query_sum(l, r));
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
