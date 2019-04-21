/**
 * van Emde Boas trees
 * O(n log log n) - O(log log n)
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 2000

typedef long long i64;

struct PairHash {
    template <typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

static int cnt;
inline i64 add(i64 x, i64 y) {
    static unordered_map<pair<i64, i64>, i64, PairHash> mem;

    if (x > y) swap(x, y);
    if (x == -1) return y;
    i64 r;
    auto p = make_pair(x, y);
    if (mem.count(p)) r = mem[p];
    else {
        cnt++;
        printf("? %lld %lld\n", x, y);
        fflush(stdout);
        scanf("%lld", &r);
        //r = x + y;
        mem[p] = r;
    }

#ifndef NDEBUG
    fprintf(stderr, "[%d] query: %lld ∘ %lld = %lld\n", cnt, x, y, r);
#endif

    return r;
}

inline void answer(i64 x) {
    printf("! %lld\n", x);
    fflush(stdout);
}

static int n, q, K, sqrt[NMAX + 10];
static i64 seq[NMAX + 10];
static int pt[NMAX + 10];

inline void nxt_query() {
    puts("next");
    fflush(stdout);
    for (int i = 1; i <= K; i++) scanf("%d", pt + i);
    sort(pt + 1, pt + K + 1);
}

struct Node {
    Node(int _l, int _r) : l(_l), r(_r), len(sqrt[r - l + 1]) {
        if (l < r) {
            for (int i = l; i <= r; i += len) {
                int j = min(r, i + len - 1);
                ch.push_back(new Node(i, j));
            }
            sum.resize(size());
            for (int i = 0; i < size(); i++) {
                sum[i].resize(size());
                sum[i][i] = ch[i]->val;
                for (int j = i + 1; j < size(); j++)
                    sum[i][j] = add(sum[i][j - 1], ch[j]->val);
            }
            val = sum[0][size() - 1];
        } else val = seq[l];
    }

    i64 query(int lp, int rp) {
        if (lp < l && r < rp) return val;
        if (l == r) return -1;
        int li = -1, ri = size();
        for (int p = l, i = 0; p <= r; p += len, i++) {
            int q = min(p + len - 1, r);
            if (p <= lp && lp <= q) li = i;
            if (p <= rp && rp <= q) ri = i;
        }

        if (li == ri) return ch[li]->query(lp, rp);
        i64 ret = -1;
        if (li > -1) ret = ch[li]->query(lp, rp);
        if (ri < size()) ret = add(ret, ch[ri]->query(lp, rp));
        if (li + 1 == ri) return ret;
        return add(ret, sum[li + 1][ri - 1]);
    }

    int size() const {
        return ch.size();
    }

    int l, r, len;
    i64 val;
    vector<Node*> ch;
    vector<vector<i64>> sum;
};

int main() {
    scanf("%d%d%d", &n, &q, &K);
    for (int i = 1; i <= n; i++) scanf("%lld", seq + i);
    for (int i = 1, j = 1; i <= n; i++) {
        while ((j + 1) * (j + 1) <= i) j++;
        sqrt[i] = j;
    }

    pt[K + 1] = n + 1;
    Node *tr = new Node(1, n);
    for (int t = 1; t <= q; t++) {
        nxt_query();
        i64 ans = -1;
        for (int i = 1; i <= K + 1; i++) {
            if (pt[i - 1] + 1 == pt[i]) continue;
            ans = add(ans, tr->query(pt[i - 1], pt[i]));
        }
        answer(ans);
    }

#ifndef NDEBUG
    int maxcnt = 4 * (n + q * (K + 1));
    fprintf(stderr, "4(n + q(K + 1)) = %d\n", maxcnt);
#endif
    assert(maxcnt >= cnt);

    return 0;
}
