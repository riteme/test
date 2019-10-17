#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MEMSIZE 130000000
#define EPS 1e-11

static size_t memp;
void *operator new(size_t s) {
    static char mem[MEMSIZE];
    auto p = mem + memp;
    memp += s;
    return p;
}

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
    int w = 0;
    double dp = 0;
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
inline void initialize() {
    rt = new State;
    _append::reset();
    n = strlen(str + 1) + 1;
    for (int i = 1; i < n; i++) {
        str[i] -= 'a';
        append(str[i]);
    }
    str[n] = EOFC;
    append(EOFC);
}

static int t;
static double pre[100], suf[100];

void dp(State *x) {
    bool has = false;
    for (int c = 0; c < SIGMA; c++) if (x->ch[c]) {
        State *y = x->ch[c]->nxt;
        y->w = x->ch[c]->len() - (x->ch[c]->r >= n);
        dp(y);
        has = true;
    }
    if (has) {
        t = 0;
        pre[0] = suf[0] = 1;
        for (int c = 0; c < SIGMA; c++) if (x->ch[c]) {
            if (x == rt && c + 1 == SIGMA) continue;
            t++;
            pre[t] = pre[t - 1] * x->ch[c]->nxt->dp;
        }
        t = 0;
        for (int c = SIGMA - 1; c >= 0; c--) if (x->ch[c]) {
            if (x == rt && c + 1 == SIGMA) continue;
            t++;
            suf[t] = suf[t - 1] * x->ch[c]->nxt->dp;
        }
        double S = 0;
        for (int i = t; i >= 1; i--) {
            pre[i] = pre[i - 1] * suf[t - i];
            S += pre[i];
        }
        //printf("S = %.12lf\n", S);
        for (int c = 0; c < SIGMA; c++) if (x->ch[c]) {
            if (x == rt && c + 1 == SIGMA) continue;
            State *y = x->ch[c]->nxt;
            x->dp = pre[1] * y->dp / S;
            break;
        }
    }
    x->dp += x->w;
    //printf("%d %.12lf\n", x->w, x->dp);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str + 1);
        memp = 0;
        initialize();
        dp(rt);
        printf("%.12lf\n", rt->dp);
    }
}
