#include <cstdio>
#include <cstring>

#include <tuple>
#include <random>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef unsigned int u32;
typedef long long i64;

u32 randu() {
    static random_device rd;
    static mt19937 gen(rd());
    return gen();
}

struct Node {
    Node(int _val) {
        wt = randu();
        cnt = 1;
        val = _val;
        sum = val;
        lch = NULL;
        rch = NULL;
    }

    u32 wt;
    int cnt, val;
    i64 sum;
    Node *lch, *rch;

    void update() {
        cnt = 1;
        sum = val;
        if (lch) {
            cnt += lch->cnt;
            sum += lch->sum;
        }
        if (rch) {
            cnt += rch->cnt;
            sum += rch->sum;
        }
    }
};

typedef std::tuple<Node*, Node*> NodeTuple;

auto split(Node *x, int pos) -> NodeTuple {
    if (!x)
        return make_tuple((Node*)NULL, (Node*)NULL);

    int lcnt = x->lch ? x->lch->cnt : 0;
    Node *a, *b;
    if (lcnt + 1 >= pos) {
        tie(a, b) = split(x->lch, pos);
        x->lch = b;
        b = x;
    } else {
        tie(a, b) = split(x->rch, pos - lcnt - 1);
        x->rch = a;
        a = x;
    }

    x->update();
    return make_tuple(a, b);
}

Node *meld(Node *x, Node *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->wt < y->wt) {
        x->rch = meld(x->rch, y);
        x->update();
        return x;
    } else {
        y->lch = meld(x, y->lch);
        y->update();
        return y;
    }
}

int n, q;
Node *tr[6];

struct slice_t {
    Node *a, *b, *c;
};

void slice(int l, int r, slice_t *s) {
    for (int i = 0; i < 6; i++) {
        int pl = l / 6 + 1;
        int pr = r / 6 + 1;
        if (i < l % 6)
            pl++;
        if (i > r % 6)
            pr--;
        tie(s[i].a, s[i].b) = split(tr[i], pl);
        tie(s[i].b, s[i].c) = split(s[i].b, pr - pl + 2);
    }
}

void restore(slice_t *s) {
    for (int i = 0; i < 6; i++) {
        tr[i] = meld(s[i].a, meld(s[i].b, s[i].c));
    }
}

int main() {
    scanf("%d%d", &n, &q);
    tr[0] = new Node(0);
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        int p = i % 6;
        tr[p] = meld(tr[p], new Node(v));
    }

    while (q--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);

        slice_t s[6];
        slice(l, r, s);

        if (op == 2) {
            i64 ans = 0;
            for (int i = 0; i < 6; i++) {
                ans += s[i].b ? s[i].b->sum : 0;
            }
            printf("%lld\n", ans);
        } else {
            int K;
            scanf("%d", &K);

            int r = l % 6;
            if (K == 2) {
                swap(s[r].b, s[(r + 1) % 6].b);
                swap(s[(r + 2) % 6].b, s[(r + 3) % 6].b);
                swap(s[(r + 4) % 6].b, s[(r + 5) % 6].b);
            } else {  // K = 3
                swap(s[r].b, s[(r + 1) % 6].b);
                swap(s[(r + 1) % 6].b, s[(r + 2) % 6].b);
                swap(s[(r + 3) % 6].b, s[(r + 4) % 6].b);
                swap(s[(r + 4) % 6].b, s[(r + 5) % 6].b);
            }
        }

        restore(s);
    }

    return 0;
}
