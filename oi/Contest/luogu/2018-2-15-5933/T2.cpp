#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000
#define QMAX 200000

static int n, m, p, q;
static int arr[NMAX + 10];

inline void modify(int x, int v) {
    for (; x <= n; x += x & (-x)) {
        arr[x] += v;
    }
}

inline int query(int x) {
    int r = 0;
    for (; x; x -= x & (-x)) {
        r += arr[x];
    }
    return r;
}

#define MODIFY 1
#define QUERY 2
#define DEC 3

struct Op {
    Op() {}
    Op(int _x, int _y, int _t, int _v)
        : x(_x), y(_y), type(_t), val(_v) {}

    int x, y, type, val;

};

static int cnt;
static Op *ops[QMAX * 4];
static Op *ref[QMAX + 10];

bool cmp(const Op *a, const Op *b) {
    return (a->y < b->y) ||
           (a->y == b->y && a->type < b->type);
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &p, &q);

    for (int i = 0; i < p; i++) {
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        ops[++cnt] = new Op(a, b, MODIFY, 1);
        ops[++cnt] = new Op(x + 1, b, MODIFY, -1);
        ops[++cnt] = new Op(a, y, DEC, -1);
        ops[++cnt] = new Op(x + 1, y, DEC, +1);
    }

    for (int i = 1; i <= q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        ops[++cnt] = new Op(x, y, QUERY, 0);
        ref[i] = ops[cnt];
    }

    sort(ops + 1, ops + cnt + 1, cmp);
}

int main() {
    initialize();

    for (int i = 1; i <= cnt; i++) {
        Op &op = *ops[i];
        if (op.type == MODIFY || op.type == DEC)
            modify(op.x, op.val);
        else
            op.val = query(op.x);
    }

    for (int i = 1; i <= q; i++) {
        printf("%d\n", ref[i]->val);
    }

    return 0;
}
