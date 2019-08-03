#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 100000

int n, q;
int key[NMAX + 10];
int fa[NMAX + 10], lch[NMAX + 10], rch[NMAX + 10], size[NMAX + 10];
int L[NMAX + 10], R[NMAX + 10];
map<int, int> seq;

inline void update(int x) {
    size[x] = 1 + size[lch[x]] + size[rch[x]];
}

inline void lrot(int x) {
    int y = lch[x];
    assert(y);
    lch[x] = rch[y];
    rch[y] = x;
    if (fa[x]) {
        if (lch[fa[x]] == x) lch[fa[x]] = y;
        else rch[fa[x]] = y;
    }
    fa[lch[x]] = x;
    fa[y] = fa[x];
    fa[x] = y;
    size[y] = size[x];
    L[y] = L[x];
    R[y] = R[x];
    update(x);
}

inline void rrot(int x) {
    int y = rch[x];
    assert(y);
    rch[x] = lch[y];
    lch[y] = x;
    if (fa[x]) {
        if (lch[fa[x]] == x) lch[fa[x]] = y;
        else rch[fa[x]] = y;
    }
    fa[rch[x]] = x;
    fa[y] = fa[x];
    fa[x] = y;
    size[y] = size[x];
    L[y] = L[x];
    R[y] = R[x];
    update(x);
}

inline void splay(int x) {
    while (fa[x]) {
        int p = fa[x], g = fa[p];
        if (g) {
            if (p == lch[g] && x == lch[p]) lrot(g);
            else if (p == rch[g] && x == rch[p]) rrot(g);
        }
        if (x == lch[p]) lrot(p);
        else rrot(p);
    }
}

inline auto kth(int x, int k) -> int {
    assert(x);
    assert(k);
    while (size[lch[x]] + 1 != k) {
        if (k <= size[lch[x]]) x = lch[x];
        else k -= size[lch[x]] + 1, x = rch[x];
    }
    splay(x);
    return x;
}

inline auto search(int x, int k) -> int {
    // caution: no splay
    int y = 0;
    while (x) {
        if (k < key[x]) x = lch[x];
        else if (k > key[x]) x = rch[y = x];
        else return x;
    }
    assert(y);
    return y;
}

inline auto query(int i) {
    auto it = prev(seq.upper_bound(i));
    it->second = kth(it->second, i - it->first + 1);
    return it;
}

inline void split(int i) {
    auto it = query(i);
    int r = it->second;
    if (!lch[r]) return;
    L[lch[r]] = L[r];
    R[lch[r]] = i - 1;
    L[r] = i;
    it = seq.erase(it);
    it = seq.insert(it, {i, r});
    seq.insert(it, {L[lch[r]], lch[r]});
    fa[lch[r]] = 0;
    lch[r] = 0;
    update(r);
}

inline auto extract(int i) -> int {
    auto it = query(i);
    int r = it->second;
    seq.erase(it);
    return r;
}

inline auto min(int x) -> int {
    while (lch[x]) x = lch[x];
    splay(x);
    return x;
}

inline auto max(int x) -> int {
    while (rch[x]) x = rch[x];
    splay(x);
    return x;
}

inline auto meld(int x, int y) -> int {
    x = max(x);
    R[x] = R[y];
    rch[x] = y;
    fa[y] = x;
    update(x);
    rrot(x);
    return y;
}

inline auto trsplit(int x, int p) -> int {
    splay(x);
    int t = rch[x];
    rch[x] = 0;
    fa[t] = 0;
    update(x);
    t = min(t);
    L[t] = L[x] + size[lch[x]] + 1;
    R[t] = R[x];
    L[x] = p;
    R[x] = p + size[lch[x]];
    return t;
}

void msort(int l, int r, int m) {
    static int Q[NMAX + 10], cnt;
    auto add = [](int x, int k) {
        if (cnt && key[Q[cnt]] <= k) Q[cnt] = meld(Q[cnt], x);
        else Q[++cnt] = x;
    };
    cnt = 0;
    split(l); split(m + 1); if (r < n) split(r + 1);
    int a = 0, b = 0, p = l;
    for (int i = l, j = m + 1, x, t; i <= m && j <= r; p = R[x] + 1) {
        if (!a) a = extract(i);
        if (!b) b = extract(j);
        assert(!lch[a]);
        assert(!lch[b]);
        if (key[a] < key[b]) {
            x = search(a, key[b] - 1), t = trsplit(x, p);
            add(x, key[a]);
            i = L[t];
            a = t;
        } else {
            x = search(b, key[a]), t = trsplit(x, p);
            add(x, key[b]);
            j = L[t];
            b = t;
        }
    }
    if (a) {
        int i = R[a] + 1;
        L[a] = p;
        R[a] = p + size[a] - 1;
        p += size[a];
        add(a, key[a]);
        for (; i <= m; p += size[a]) {
            a = extract(i);
            i = R[a] + 1;
            L[a] = p;
            R[a] = p + size[a] - 1;
            Q[++cnt] = a;
        }
    } else if (b) add(b, key[b]);
    for (int i = 1; i <= cnt; i++) seq.insert({L[Q[i]], Q[i]});
}

static void print(int x) {
    if (!x) return;
    print(lch[x]);
    fprintf(stderr, "%d ", key[x]);
    print(rch[x]);
}

static void print() {
    fprintf(stderr, "⇒ ");
    for (auto &e : seq) if (e.first <= n) {
        fprintf(stderr, "[%d] ", L[e.second]);
        print(e.second);
    }
    fprintf(stderr, "\n");
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", key + i);
        size[i] = 1;
        L[i] = R[i] = i;
        if (i > 1 && key[i] >= key[i - 1]) {
            lch[i] = i - 1;
            fa[i - 1] = i;
            size[i] += size[i - 1];
            L[i] = L[i - 1];
        }
    }
    for (int i = 1; i <= n; i++) if (!fa[i]) seq[L[i]] = i;
    seq[n + 1] = 0;
#ifndef NDEBUG
    print();
#endif
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, m;
            scanf("%d%d%d", &l, &m, &r);
#ifndef NDEBUG
            fprintf(stderr, "[%d, %d] × [%d, %d]\n", l, m, m + 1, r);
#endif
            msort(l, r, m);
#ifndef NDEBUG
            print();
#endif
        } else {
            int i;
            scanf("%d", &i);
            printf("%d\n", key[query(i)->second]);
        }
    }
    print();

    return 0;
}
