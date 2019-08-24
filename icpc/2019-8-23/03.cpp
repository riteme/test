#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define MEMSIZE 200000000
static unsigned char mem[MEMSIZE];
static size_t _pos;

inline void clear() {
  _pos = 0;
}

void *operator new(size_t cnt) {
  void *ptr = mem + _pos;
  _pos += cnt;
  return ptr;
}

#define NMAX 100000
#define LOGN 20

#define SIGMA 27
#define EOFC (SIGMA - 1)
struct State {
  struct Trans {
    Trans(int _l, int _r, State *_nxt)
      : l(_l), r(_r), nxt(_nxt) {}
    int l, r; State *nxt;
    int len() const { return r - l + 1; }
  };
  State() : fail(NULL) { memset(ch, 0, sizeof(ch)); }
  State *fail; Trans *ch[SIGMA];
  int in, out, dep;
  State *jmp[LOGN];
};
typedef State::Trans Trans;

static State *rt;
static char str[NMAX + 10];
static int n;

namespace _append {
static char dir;
static int len, cnt, cur;
static State *ap;
void reset() {
  dir = -1; ap = rt;
  len = cnt = cur = 0;
}}
inline void append(char c) {
  using namespace _append;
  cnt++; cur++;
  State *x, *y = NULL;
  while (cnt) {
    if (cnt <= len + 1) {
      len = cnt - 1;
      dir = len ? str[cur - len] : -1;
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
      Trans *t = ap->ch[dir];
      x = new State;
      x->ch[c] = new Trans(cur, n, new State);
      x->ch[str[t->l + len]] = new Trans(t->l + len, t->r, t->nxt);
      t->r = t->l + len - 1;
      t->nxt = x;
    }
    if (y) y->fail = x;
    if (ap != rt) ap = ap->fail;
    y = x; cnt--;
}}

static int tm;
static State *suf[NMAX + 10], *pos[NMAX + 10];
void dfs(State *x) {
    x->in = INT_MAX;
    x->out = INT_MIN;
    for (int i = 1; i < LOGN; i++)
        x->jmp[i] = x->jmp[i - 1]->jmp[i - 1];
    bool has_child = false;
    for (char c = 0; c < SIGMA; c++) {
        if (x->ch[c]) {
            has_child = true;
            State *v = x->ch[c]->nxt;
            v->jmp[0] = x;
            v->dep = x->dep + x->ch[c]->len();
            dfs(v);
            x->in = min(x->in, v->in);
            x->out = max(x->out, v->out);
        }
    }
    if (!has_child) {
        x->in = x->out = ++tm;
        pos[x->in] = suf[n - x->dep + 1] = x;
    }
}

inline State *jump(State *x, int k) {  // k remaining distance [r + 1, n]
    for (int i = LOGN - 1; i >= 0; i--) {
        int d = x->dep - x->jmp[i]->dep;
        if (k >= d) {
            x = x->jmp[i];
            k -= d;
        }
    }
    if (x->dep - x->jmp[0]->dep <= k) x = x->jmp[0];
    return x;
}

struct Node {
    Node() : cnt(0), lch(NULL), rch(NULL) {}
    int cnt;
    Node *lch, *rch;
};

Node *modify(Node *x, int p, int xl, int xr) {
    Node *x_ = x;
    x = new Node;
    if (x_) memcpy(x, x_, sizeof(Node));
    if (xl < xr) {
        int m = (xl + xr) >> 1;
        if (p <= m) x->lch = modify(x->lch, p, xl, m);
        else x->rch = modify(x->rch, p, m + 1, xr);
    }
    x->cnt++;
    return x;
}

inline int kth(Node *x, Node *y, int k, int xl, int xr) {
    if (xl == xr) {
        int c = (y ? y->cnt : 0) - (x ? x->cnt : 0);
        return k <= c ? xl : -1;
    }
    int m = (xl + xr) >> 1;
    int c = (y && y->lch ? y->lch->cnt : 0) - (x && x->lch ? x->lch->cnt : 0);
    if (k <= c) return kth(x ? x->lch : NULL, y ? y->lch : NULL, k, xl, m);
    return kth(x ? x->rch : NULL, y ? y->rch : NULL, k - c, m + 1, xr);
}

static Node *tr[NMAX + 10];

int main() {
    int T, q;
    scanf("%d", &T);
    while (T--) {
        clear();
        rt = new State;
        _append::reset();

        scanf("%d%d%s", &n, &q, str + 1);
        n++;
        for (int i = 1; i < n; i++) {
            str[i] -= 'a';
            append(str[i]);
        }
        str[n] = EOFC;
        append(EOFC);

        tm = 0;
        rt->dep = 0;
        rt->jmp[0] = rt;
        dfs(rt);

        for (int i = 1; i <= tm; i++)
            tr[i] = modify(tr[i - 1], n - pos[i]->dep + 1, 1, n);

        while (q--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            State *x = jump(suf[l], n - r);
            //fprintf(stderr, "[%d, %d] %d\n", l, r, x->dep);
            int ans = kth(tr[x->in - 1], tr[x->out], k, 1, n);
            printf("%d\n", ans);
        }
    }
    return 0;
}
