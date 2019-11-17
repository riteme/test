#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, q;
static int a[NMAX + 10];

struct Result {
    Result() : mi(INT_MAX), mx(0) {}
    Result(int _mi, int _mx) : mi(_mi), mx(_mx) {}

    int mi, mx;

    Result operator+(const Result &z) const {
        return Result(min(mi, z.mi), max(mx, z.mx));
    }
};

struct Node {
    int l, r;
    int mi, mx;
    Node *lch, *rch;

    Node(int _l, int _r) : l(_l), r(_r), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
            mi = min(lch->mi, rch->mi);
            mx = max(lch->mx, rch->mx);
        } else
            mi = mx = a[l];
    }

    Result query(int L, int R) {
        if (L <= l && r <= R) return Result(mi, mx);
        int m = (l + r) / 2;
        Result ret;
        if (L <= m) ret = ret + lch->query(L, R);
        if (R > m) ret = ret + rch->query(L, R);
        return ret;
    }
};

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    Node *tr = new Node(1, n);
    while (q--) {
        int L, R;
        scanf("%d%d", &L, &R);
        Result ret = tr->query(L, R);
        printf("%d\n", ret.mx - ret.mi);
    }
    return 0;
}
