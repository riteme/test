#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define SIGMA 26
#define NMAX 1100000
#define MOD 998244353

typedef long long i64;

struct State {
    struct Trans {
        Trans(int _l, int _r, State *_nxt)
            : l(_l), r(_r), nxt(_nxt) {}
        int l, r; State *nxt;
        int len() const {
            return r - l + 1;
        }
    };
    State() : fail(NULL) {}
    State *fail;
    unordered_map<int, Trans*> ch;
};

typedef State::Trans Trans;
static State *rt;
static char buf[NMAX + 10];
static int str[NMAX + 10];
static int n;
namespace _append {
static int dir;
static int len, cnt, cur;
static State *ap;
void reset() {
    dir = -1; ap = rt;
    len = cnt = cur = 0;
}
}

inline void append(int c) {
    using namespace _append;
    cnt++; cur++;
    State *x, *y = NULL;
    while (cnt) {
        if (cnt <= len + 1) {
            len = cnt - 1;
            dir = len ? str[cur - len]: -1;
        }
        while (dir >= 0 && len >= ap->ch[dir]->len()) {
            len -= ap->ch[dir]->len();
            ap = ap->ch[dir]->nxt;
            dir = len ? str[cur - len] : -1;
        }
        if ((dir >= 0 && str[ap->ch[dir]->l + len] == c) ||
            (dir < 0 && ap->ch[c])) {
            if (dir < 0) dir = c;
            if (y) y->fail = ap;
            len++; return;
        }
        if (dir < 0) {
            ap->ch[c] = new Trans(cur, n, new State);
            x = ap;
        } else {
            auto t = ap->ch[dir];
            x = new State;
            x->ch[c] = new Trans(cur, n, new State);
            x->ch[str[t->l + len]] = new Trans(t->l + len, t->r, t->nxt);
            t->r = t->l + len - 1;
            t->nxt = x;
        }
        if (y) y->fail = x;
        if (ap != rt) ap = ap->fail;
        y = x; cnt--;
    }
}

inline void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int num, ncnt;
int ch[NMAX + 10][SIGMA];
int tlen[NMAX + 10][SIGMA];
int dep[NMAX + 10];
int val[NMAX + 10];
vector<int> col[NMAX + 10];
stack<int, vector<int>> stk[NMAX + 10];

i64 pw(i64 x) {
    return x * x;
}

int right[NMAX + 10];

int build(State *x, int dt = 0) {
    int u = ++ncnt;
    dep[u] = dt;
    for (auto &e : x->ch) {
        int c = e.first;
        auto t = x->ch[c];
        int r = right[t->l];
        if (r <= t->r) {
            int p = str[r] - SIGMA + 1;
            if (r == t->l)
                col[u].push_back(p);
            else {
                int v = ++ncnt;
                col[v].push_back(p);
                ch[u][c] = v;
                tlen[u][c] = r - t->l;
                dep[v] = dt + tlen[u][c];
            }
        }
    }

    for (auto &e : x->ch) {
        int c = e.first;
        auto t = x->ch[c];
        if (right[t->l] > t->r) {
            ch[u][c] = build(t->nxt, dt + t->len());
            tlen[u][c] = t->len();
        }
    }

    return u;
}

void dfs(int u) {
    for (int p : col[u]) {
        add(val[u], (pw(dep[u]) - (stk[p].empty() ? 0 : pw(dep[stk[p].top()]))) % MOD);
        stk[p].push(u);
    }

    for (int c = 0; c < SIGMA; c++)
        if (ch[u][c]) dfs(ch[u][c]);

    for (int p : col[u])
        stk[p].pop();
}

void initialize() {
    scanf("%d", &num);
    char *p = buf + 1;
    for (int i = 0; i < num; i++) {
        scanf("%s", p);
        int sz = strlen(p);
        for (int j = 0; j <= sz; j++)
            right[p - buf + j] = p - buf + sz;
        p += sz;
        *p = '#';
        p++;
    }

    rt = new State;
    _append::reset();
    n = strlen(buf + 1);
    for (int i = 1, j = 0; i <= n; i++) {
        if (buf[i] == '#') {
            str[i] = SIGMA + j;
            j++;
            append(str[i]);
        } else {
            str[i] = buf[i] - 'a';
            append(str[i]);
        }
    }

    build(rt);
    dfs(1);
}

int main() {
    initialize();

    int ans = 0;
    int x = 1;
    for (int i = 1; i <= n; )
    if (buf[i] == '#') {
        x = 1;
        i++;
    } else {
        int c = buf[i] - 'a';
        i += tlen[x][c];
        x = ch[x][c];
        add(ans, val[x]);
    }

    printf("%d\n", ans);
    return 0;
}