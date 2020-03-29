#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

#define NMAX 100000

struct Node {
    Node() : w(rand() * rand()), key(0), size(1), lch(NULL), rch(NULL) {}

    int w, key, size;
    Node *lch, *rch;

    void update() {
        size = 1 + (lch ? lch->size : 0) + (rch ? rch->size : 0);
    }
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node *x, int key) {
    if (!x) return NodePair(NULL, NULL);
    NodePair ret;
    if (x->key < key) {  // key to right
        ret = split(x->rch, key);
        x->rch = ret.first;
        ret.first = x;
    } else {
        ret = split(x->lch, key);
        x->lch = ret.second;
        ret.second = x;
    }
    x->update();
    return ret;
}

Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    if (x->w < y->w) {
        x->rch = meld(x->rch, y);
        x->update();
        return x;
    } else {
        y->lch = meld(x, y->lch);
        y->update();
        return y;
    }
}

struct Segment {
    int l, r, c;

    bool operator<(const Segment &z) const {
        return l < z.l;
    }
};

int n, q;
Node mem[NMAX + 10];

void solve() {
    set<Segment> s;
    tr1::unordered_map<int, Node*> tr;
    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        mem[i].key = i;
        mem[i].size = 1;
        mem[i].lch = mem[i].rch = NULL;
        tr[c] = meld(tr[c], mem + i);
        s.insert({i, i, c});
    }

    // s.insert({n + 1, n + 1, 0});
    while (q--) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        l++; r++;
        if (op == 1) {
            typedef set<Segment>::iterator iter_t;
            iter_t li = s.upper_bound({l, l}), ri = s.upper_bound({r, r});
            iter_t ri2 = ri;
            li--; ri2--;
            int l1 = li->l, r1 = l - 1, c1 = li->c;
            int l2 = r + 1, r2 = ri2->r, c2 = ri2->c;

            Node *sum = NULL;
            for (iter_t it = li; it != ri; ) {
                NodePair x = split(tr[it->c], max(l, it->l));
                NodePair y = split(x.second, min(r, it->r) + 1);
                sum = meld(sum, y.first);
                tr[it->c] = meld(x.first, y.second);
                iter_t nxt = it;
                nxt++;
                s.erase(it);
                it = nxt;
            }

            if (l1 <= r1)
                s.insert({l1, r1, c1});
            if (l2 <= r2)
                s.insert({l2, r2, c2});

            s.insert({l, r, c});
            NodePair x = split(tr[c], l);
            tr[c] = meld(x.first, meld(sum, x.second));
        } else {
            NodePair x = split(tr[c], l);
            NodePair y = split(x.second, r + 1);
            int ans = y.first ? y.first->size : 0;
            tr[c] = meld(x.first, meld(y.first, y.second));
            printf("%d\n", ans);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        solve();
    }
    return 0;
}