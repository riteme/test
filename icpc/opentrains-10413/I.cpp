#pragma GCC optimize(3)

#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int BUFFERSIZE = 65536;
int _pos = BUFFERSIZE;
char _buf[BUFFERSIZE];

char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getchar(); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getchar();
    } while (isdigit(c));
}

void reads(char *s) {
    char c;
    while (isalpha(c = _getchar())) {
        *(s++) = c;
    }
}

constexpr int SMAX = 26;
constexpr int NMAX = 800000;
constexpr int QMAX = 400000;

struct SAM {
    int mcnt;
    struct Node {
        int maxlen, fail;
        int ch[SMAX];
    } m[NMAX + 10];
    SAM() { reset(); }
    void reset() {
        memset(this, 0, sizeof(SAM));
        mcnt = 1;
        m[0].maxlen = -1;
        fill(m[0].ch, m[0].ch + SMAX, 1);
    }
    int append(int x, int c) {
        int y = ++mcnt;
        m[y].maxlen = m[x].maxlen + 1;
        while (!m[x].ch[c]) {
            m[x].ch[c] = y;
            x = m[x].fail;
        }
        int p = m[x].ch[c];
        if (m[x].maxlen + 1 != m[p].maxlen) {
            int q = ++mcnt;
            m[q] = m[p];
            m[q].maxlen = m[x].maxlen + 1;
            m[p].fail = m[y].fail = q;
            while (m[x].ch[c] == p) {
                m[x].ch[c] = q;
                x = m[x].fail;
            }
        } else
            m[y].fail = p;
        return y;
    }
    Node &operator[](int i) {
        return m[i];
    }
} *_sam;

int n, m, q;
char s[NMAX + 10];
int p[NMAX + 10];

vector<int> T[NMAX + 10];
int len[NMAX + 10];
int dfn[NMAX + 10], cur;
int top[NMAX + 10], pa[NMAX + 10], dep[NMAX + 10];
int stk[NMAX + 10], tail;

void dfs(int x) {
    dfn[x] = ++cur;
    top[x] = 1;
    for (int v : T[x]) {
        pa[v] = x;
        dep[v] = dep[x] + 1;
        dfs(v);
        top[x] += top[v];
    }
}

void decompose(int x) {
    int u = 0;
    for (int v : T[x]) {
        if (top[v] > top[u])
            u = v;
    }

    if (u) {
        top[u] = top[x];
        decompose(u);
    }

    for (int v : T[x]) if (v != u) {
        top[v] = v;
        decompose(v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = pa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct Query {
    i64 mod;
    vector<int> nodes;
};

i64 f[NMAX + 10], cnt[NMAX + 10];
[[nodiscard]] i64 solve(Query &op) {
    tail = 1;
    stk[0] = 1;
    f[1] = 1;

    sort(op.nodes.begin(), op.nodes.end(), [](int u, int v) {
        return dfn[u] < dfn[v];
    });

    for (int x : op.nodes) {
        cnt[x]++;
    }

    i64 mod = op.mod;
    for (int v : op.nodes) {
        if (v == stk[tail - 1])
            continue;

        assert(tail > 0);
        int u, p = lca(stk[tail - 1], v);
        i64 ans = 1;
        while (dep[u = stk[tail - 1]] > dep[p]) {
            // assert(tail > 0);
            ans = (ans * f[u] + cnt[u]) % mod;
            tail--;
        }

        assert(tail > 0);
        // u = stk[tail - 1];
        if (u == p)
            f[u] = f[u] * ans % mod;
        else {
            stk[tail++] = p;
            f[p] = ans;
        }

        f[v] = 1;
        stk[tail++] = v;
    }

    i64 ans = 1;
    for (int i = tail - 1; i >= 1; i--) {
        int u = stk[i];
        ans = (ans * f[u] + cnt[u]) % mod;
    }

    ans = (ans * f[1] + cnt[1]) % mod;

    for (int x : op.nodes) {
        cnt[x] = 0;
    }

    return ans;
}

struct Locate {
    int len;
    int *dest;
};

vector<Locate> loc[NMAX + 10];
Query op[QMAX + 10];

void locate(int x) {
    stk[tail++] = x;

    for (auto &u : loc[x]) {
        len[0] = u.len;
        auto v = *lower_bound(stk, stk + tail, 0, [](int i, int j) {
            return len[i] < len[j];
        });
        *u.dest = v;
    }

    for (int v : T[x]) {
        locate(v);
    }

    tail--;
}

int main() {
    // scanf("%d%d%s", &n, &q, s + 1);
    read(n); read(q); reads(s + 1);

    // build SAM
    _sam = new SAM;
    SAM &sam = *_sam;
    p[n + 1] = 1;
    for (int i = n; i >= 1; i--) {
        p[i] = sam.append(p[i + 1], s[i] - 'a');
        assert(sam[p[i]].maxlen == n - i + 1);
    }

    // scan fail tree
    m = sam.mcnt;
    for (int i = 1; i <= m; i++) {
        len[i] = sam[i].maxlen;
    }
    for (int i = 2; i <= m; i++) {
        cnt[sam[i].fail]++;
    }
    for (int i = 1; i <= m; i++) {
        T[i].reserve(cnt[i]);
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 2; i <= m; i++) {
        T[sam[i].fail].push_back(i);
    }

    delete _sam;

    // LCA
    dfs(1);
    top[1] = 1;
    decompose(1);

    // read queries
    for (int i = 1; i <= q; i++) {
        int c;
        // scanf("%d%lld", &c, &op[i].mod);
        read(c); read(op[i].mod);
        op[i].nodes.resize(c);

        for (int j = 0; j < c; j++) {
            int l, r;
            // scanf("%d%d", &l, &r);
            read(l); read(r);
            loc[p[l]].push_back({r - l + 1, &op[i].nodes[j]});
        }
    }

    // solve them!
    locate(1);
    for (int i = 1; i <= q; i++) {
        printf("%lld\n", solve(op[i]));
    }

    return 0;
}