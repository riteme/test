#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <ctime>
#define eps 1e-6
#define LL long long
#define pii (pair<int, int>)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;

// zoj 2104 动态主席树修改+静态主席树
const int maxn = 60000 + 1000;
const int M = 2400000;
int n, q, m, tot;
int a[maxn], t[maxn];
int T[maxn], lson[M], rson[M], c[M];
int S[maxn];
struct Query {
    int kind;
    int l, r, k;
} query[10010];

void Init_hash(int k) {
    sort(t, t + k);
    m = unique(t, t + k) - t;
}

int Hash(int x) {
    return lower_bound(t, t + m, x) - t;
}

int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if (l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}

int Insert(int root, int pos, int val) {
    int newroot = tot++, tmp = newroot;
    int l = 0, r = m - 1;
    c[newroot] = c[root] + val;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int lowbit(int x) {
    return x & (-x);
}
int use[maxn];
void add(int x, int pos, int d) {
    while (x <= n) {
        S[x] = Insert(S[x], pos, d);
        x += lowbit(x);
    }
}
int Sum(int x) {
    int ret = 0;
    while (x > 0) {
        ret += c[lson[use[x]]];
        x -= lowbit(x);
    }
    return ret;
}
int Query(int left, int right, int k) {
    int left_root = T[left - 1], right_root = T[right];
    int l = 0, r = m - 1;
    memset(use, 0, sizeof(use));
    for (int i = left - 1; i; i -= lowbit(i))
        use[i] = S[i];
    for (int i = right; i; i -= lowbit(i)) {
        if (use[i] != 0) {
            exit(-1);
        }
        use[i] = S[i];
    }
    while (l < r) {
        int mid = (l + r) >> 1;
        int tmp = Sum(right) - Sum(left - 1) + c[lson[right_root]] -
                  c[lson[left_root]];
        if (tmp >= k) {
            r = mid;
            for (int i = left - 1; i; i -= lowbit(i))
                use[i] = lson[use[i]];
            for (int i = right; i; i -= lowbit(i))
                use[i] = lson[use[i]];
            left_root = lson[left_root];
            right_root = lson[right_root];
        } else {
            l = mid + 1;
            k -= tmp;
            for (int i = left - 1; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            for (int i = right; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            left_root = rson[left_root];
            right_root = rson[right_root];
        }
    }
    return l;
}

int main() {
    freopen("dynrank.in", "r", stdin);
    freopen("dynrank.out", "w", stdout);
    int Tcase;
    cin >> Tcase;
    while (Tcase--) {
        scanf("%d%d", &n, &q);
        tot = 0;
        m = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            t[m++] = a[i];
        }
        char op[10];
        for (int i = 0; i < q; i++) {
            scanf("%s", op);
            if (op[0] == 'Q') {
                query[i].kind = 0;
                scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].k);
            } else {
                query[i].kind = 1;
                scanf("%d%d", &query[i].l, &query[i].r);
                t[m++] = query[i].r;
            }
        }
        Init_hash(m);
        T[0] = build(0, m - 1);
        for (int i = 1; i <= n; i++)
            T[i] = Insert(T[i - 1], Hash(a[i]), 1);
        for (int i = 1; i <= n; i++)
            S[i] = T[0];
        for (int i = 0; i < q; i++) {
            if (query[i].kind == 0)
                printf("%d\n", t[Query(query[i].l, query[i].r, query[i].k)]);
            else {
                add(query[i].l, Hash(a[query[i].l]), -1);
                add(query[i].l, Hash(query[i].r), 1);
                a[query[i].l] = query[i].r;
            }
        }
    }
    fcloseall();
    return 0;
}
