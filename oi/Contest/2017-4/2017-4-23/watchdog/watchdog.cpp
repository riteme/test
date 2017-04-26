#pragma GCC optimize(3)

#define NDEBUG

#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }
    return buffer[_pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c = _getchar();

    while (!isdigit(c)) {
        c = _getchar();
    }  // while

    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }  // while
}

#define NMAX 1000000
#define MOD 998244353

// #define chkmax(dest, src) \
//     if (dest < src)       \
//         dest = src;

typedef long long i64;

inline void chkmax(i64 &dest, i64 src) {
    if (dest < src)
        dest = src;
}

static int cnt;
static int weight[NMAX + 10];
static int key[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static i64 val[NMAX + 10];
static i64 maxv[NMAX + 10];

inline void update(int x) {
    maxv[x] = max(val[x], max(maxv[left[x]], maxv[right[x]]));
}

inline int left_rotate(int x) {
    int y = left[x];
    left[x] = right[y];
    right[y] = x;
    maxv[y] = maxv[x];
    update(x);
    return y;
}

int insert(int x, int _key, i64 _val) {
    if (!x) {
        cnt++;
        key[cnt] = _key;
        maxv[cnt] = val[cnt] = _val;
        return cnt;
    }

    left[x] = insert(left[x], _key, _val);

    if (weight[left[x]] < weight[x])
        return left_rotate(x);

    update(x);
    return x;
}

i64 query(int x, int l, int r) {
    if (!x)
        return -1;

    if (r < key[x])
        return query(left[x], l, r);
    if (l > key[x])
        return query(right[x], l, r);

    i64 ret = val[x];

    if (l <= key[x] && r == INT_MAX) {
        chkmax(ret, maxv[right[x]]);
        return max(query(left[x], l, INT_MAX), ret);
    }

    if (key[x] <= r && l == INT_MIN) {
        chkmax(ret, maxv[left[x]]);
        return max(query(right[x], INT_MIN, r), ret);
    }

    return max(ret,
               max(query(left[x], l, INT_MAX), query(right[x], INT_MIN, r)));
}

struct Treap {
    Treap() : root(0), size(0) {}

    int root;
    int size;
    int offest;

    void insert(int key, i64 val) {
        root = ::insert(root, offest + key, val);
        size++;
        offest--;
    }

    i64 query(int l, int r) {
        l += offest;
        r += offest;
        return ::query(root, l, r);
    }
};

static int n;
static int L[NMAX + 10];
static int R[NMAX + 10];
static vector<int> G[NMAX + 10];
static Treap tree[NMAX + 10];
static i64 w[NMAX + 10];
static i64 dist[NMAX + 10];
static i64 ans[NMAX + 10];

void scan_tree(int u) {
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        dist[v] = dist[u] + w[v];
        scan_tree(v);
    }  // for
}

static int tail;
static i64 tmp[NMAX + 10];

void scan(int x) {
    if (!x)
        return;

    scan(left[x]);

    tmp[++tail] = val[x];

    scan(right[x]);
}

void update(int x, int &pos) {
    if (!x || pos >= tail)
        return;

    update(left[x], pos);

    if (pos < tail) {
        pos++;
        chkmax(val[x], tmp[pos]);
    }

    update(right[x], pos);
    update(x);
}

i64 process(Treap &a, Treap &b, int l, int r) {
    if (a.size < b.size)
        swap(a, b);

    tail = 0;
    scan(b.root);

    i64 ret = -1;
    for (int i = 1; i <= tail; i++) {
        i64 d = a.query(l - i, r - i);

        if (d >= 0)
            chkmax(ret, tmp[i] + d);
    }  // for

    int pos = 0;
    update(a.root, pos);

    return ret;
}

void dfs(int u) {
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        dfs(v);
        chkmax(ans[u], process(tree[u], tree[v], L[u], R[u]) - (dist[u] << 1));
    }

    chkmax(ans[u], tree[u].query(L[u], R[u]) - dist[u]);
    tree[u].insert(0, dist[u]);
}

void initialize() {
    srand(MOD);
    for (int i = 1; i <= NMAX; i++) {
        weight[i] = rand();
    }

    // scanf("%d", &n);
    read<int>(n);

    for (int i = 1; i <= n; i++) {
        // scanf("%d%d", L + i, R + i);
        read<int>(L[i]);
        read<int>(R[i]);
        tree[i].offest = n;
        ans[i] = -1;
    }  // for

    for (int v = 2; v <= n; v++) {
        int u;
        // scanf("%d%lld", &u, w + v);
        read<int>(u);
        read<i64>(w[v]);
        G[u].push_back(v);
    }  // for

    scan_tree(1);
}

int main() {
#ifdef NDEBUG
    freopen("watchdog.in", "r", stdin);
    freopen("watchdog.out", "w", stdout);
#endif
    initialize();
    dfs(1);

    // for (int i = 1; i <= n; i++) {
    //     printf("%lld\n", ans[i]);
    // }  // for

    i64 tpow = 1;
    i64 answer = 0;
    for (int i = n; i >= 1; i--) {
        ans[i] %= MOD;
        answer = (answer + tpow * ans[i]) % MOD;
        tpow = tpow * 23333 % MOD;
    }  // for

    if (answer < 0)
        answer += MOD;

    printf("%lld\n", answer);

    return 0;
}
