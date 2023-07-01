#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

constexpr int NMAX = 300000;
constexpr int DMAX = 30;

struct Ran {
    int l, r, x;
};

int m, T, Q;
map<int, vector<int>> ts;
Ran R[NMAX + 10];

struct Trie {
    int cnt = 0;
    Trie *ch[2] = {nullptr, nullptr};

    void modify(int d, int x, int v) {
        cnt += v;
        if (d < 0)
            return;

        int b = (x >> d) & 1;
        if (!ch[b])
            ch[b] = new Trie;
        ch[b]->modify(d - 1, x, v);
    }

    int query(int d, int x) {
        if (d < 0)
            return 0;
        int b = (x >> d) & 1;
        if (ch[b] && ch[b]->cnt > 0)
            return ch[b]->query(d - 1, x);
        else if (ch[b ^ 1] && ch[b ^ 1]->cnt > 0)
            return ch[b ^ 1]->query(d - 1, x) | (1 << d);
        else
            return INT_MAX;
    }
};

int ans[NMAX + 10];

struct Node {
    int l, r;
    vector<int> xs;
    Node *lch, *rch;
    int qmin = INT_MAX;

    Node(int L, int R) {
        l = L;
        r = R;
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    void cover(int L, int R, int x) {
        if (L <= l && r <= R)
            xs.push_back(x);
        else {
            int m = (l + r) / 2;
            if (L <= m)
                lch->cover(L, R, x);
            if (R > m)
                rch->cover(L, R, x);
        }
    }

    void solve(Trie *tr) {
        for (int x : xs) {
            qmin = min(qmin, tr->query(DMAX, x));
            tr->modify(DMAX, x, +1);
        }

        if (l < r) {
            lch->qmin = qmin;
            lch->solve(tr);
            rch->qmin = qmin;
            rch->solve(tr);
        } else {
            ans[l] = qmin;
        }

        for (int x : xs) {
            tr->modify(DMAX, x, -1);
        }
    }
};

int main() {
    scanf("%d", &Q);
    while (Q--) {
        int op, x;
        scanf("%d", &op);
        if (op != 3)
            scanf("%d", &x);

        if (op == 1) {
            ts[x].push_back(T);
        } else if (op == 2) {
            auto t0 = ts[x].back();
            ts[x].pop_back();
            if (t0 + 1 <= T)
                R[m++] = {t0 + 1, T, x};
        } else {
            T++;
        }
    }
    for (auto &e : ts) {
        int x = e.first;
        for (int t0 : e.second) {
            if (t0 < T)
                R[m++] = {t0 + 1, T, x};
        }
    }

    Node *tr = new Node(1, T);
    for (int i = 0; i < m; i++) {
        tr->cover(R[i].l, R[i].r, R[i].x);
    }

    tr->solve(new Trie);

    for (int i = 1; i <= T; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
