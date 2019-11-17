//#define NDEBUG
//if (argc > 1)
#define NOSTDERR

#include <cassert>
#include <cstdio>
#include <cstring>

#include <map>

#define KMAX 100
#define NMAX 10000

#define LT 1
#define GT 0
#define NIL -1

//***********//
// ALGORITHM //
//***********//

int cmp(int i, int j);

static struct Node {
    int key;
    int fa, lch, rch;
} e[NMAX + 1];

#define ROT(name, l, r) \
void name(int x) { \
    int y = e[x].l; \
    assert(y); \
    e[e[y].r].fa = x; \
    e[x].l = e[y].r; \
    e[y].r = x; \
    if (e[x].fa > 0) { \
        int p = e[x].fa; \
        if (e[p].l == x) e[p].l = y; \
        else e[p].r = y; \
    } \
    e[y].fa = e[x].fa; \
    e[x].fa = y; \
}

ROT(lrot, lch, rch);
ROT(rrot, rch, lch);

int splay_s(int x, int t) {
    while (e[x].fa > 0 && e[x].fa != t) {
        int p = e[x].fa, p2 = e[p].fa;
        if (p2 > 0 && p2 != t) {
            if (e[p].lch == x && e[p2].lch == p) lrot(p2);
            else if (e[p].rch == x && e[p2].rch == p) rrot(p2);
        }
        if (e[p].lch == x) lrot(p);
        else rrot(p);
    }
    return x;
}

int splay_o(int x, int t) {
    while (e[x].fa > 0 && e[x].fa != t) {
        int p = e[x].fa, p2 = e[p].fa;
        if (p2 > 0 && p2 != t) {
            if (e[p].lch == x) {
                if (e[p2].lch == p) {
                    lrot(p2);
                    lrot(p);
                } else {
                    lrot(p);
                    rrot(p2);
                }
            } else if (e[p].rch == x) {
                if (e[p2].lch == p) {
                    rrot(p);
                    lrot(p2);
                } else {
                    rrot(p2);
                    rrot(p);
                }
            }
        } else {
            if (e[p].lch == x) lrot(p);
            else rrot(p);
        }
    }
    return x;
}

#define splay splay_s

typedef std::pair<int, int> pii;
static int bcnt;
static std::map<pii, int> pcnt;
struct Block {
    Block() {}
    Block(int len) : p(new int[len]), q(p + len) {}

    int *p, *q;

    int len() const {
        return q - p;
    }

    int *locate(int i) {
        int l = 0, r = q - p;
        while (l < r) {
            int m = (l + r) >> 1;
            if (cmp(p[m], i) == LT) l = m + 1;
            else r = m;
        }
        return p + l;
        /*
        int s = 1;
        for ( ; p + s < q && cmp(p[s], i) == LT; s <<= 1) ;
        s >>= 1;
        int j = s;
        for ( ; s; s >>= 1)
        if (p + j + s < q && cmp(p[j + s], i) == LT)
            j += s;
        return p + j + 1;
        */
    }

    int &operator[](int i) {
        assert(p + i < q);
        return p[i];
    }

    bool operator<(const Block &z) const {
        bcnt++;
        int _x = *p, _y = *z.p;
        int x = _x < _y ? _x : _y;
        int y = _x < _y ? _y : _x;
        pcnt[std::make_pair(x, y)]++;
        return cmp(*p, *z.p) == LT;
    }
};

template <typename T>
void _swap(T &x, T &y) {
    T z = y;
    y = x;
    x = z;
}

#define L(x) (x << 1)
#define R(x) (L(x) | 1)

template <typename T>
struct Heap {
    Heap(int _n) : n(_n) {}

    int n;
    T h[NMAX + 1];
    int mi[NMAX + 1];

    void eval_mi(int i) {
        int l = L(i), r = R(i);
        if (l <= n && r <= n)
            mi[i] = h[l] < h[r] ? l : r;
        else if (l <= n) mi[i] = l;
        else mi[i] = 0;
    }

    void sink(int i) {
        static int stk[NMAX + 1], t;
        t = 0;
        for (int j = i; mi[j] && h[mi[j]] < h[j]; j = mi[j]) {
            _swap(h[j], h[mi[j]]);
            stk[t++] = j;
        }
        for (int i = 0; i < t; i++)
            eval_mi(stk[i]);
    }

    void drop(T key) {
        h[1] = key;
        sink(1);
    }

    void pop() {
        _swap(h[1], h[n]);
        n--;
        eval_mi((n + 1) / 2);
        sink(1);
    }

    void initialize() {
        for (int i = n; i >= 1; i--) {
            eval_mi(i);
            sink(i);
        }
    }

    T first() const {
        return h[1];
    }

    T second() const {
        assert(mi[1]);
        return h[mi[1]];
    }

    T &operator[](int i) {
        return h[i];
    }
};

static int n, m;
static Block b[NMAX + 1];
static int seq[NMAX + 1];

template <typename T>
void reverse(T *beg, T *ed) {
    for ( ; beg < ed; beg++, ed--)
        _swap(*beg, *ed);
}

void add_block(int *t, int len, int sgn) {
    b[++m] = Block(len);
    memcpy(b[m].p, t, sizeof(int) * len);
    if (sgn == GT)
        reverse(b[m].p, b[m].q - 1);
}

void split_blocks() {
    int tmp[NMAX + 10], t = 1, ls = NIL;
    tmp[0] = 1;
    for (int i = 2; i <= n; i++) {
        int s = cmp(i - 1, i);
        if (ls != NIL && s != ls) {
            assert(t);
            add_block(tmp, t, ls);
            ls = NIL;
            tmp[0] = i;
            t = 1;
        } else {
            tmp[t++] = i;
            ls = s;
        }
    }
    if (t)
        add_block(tmp, t, ls);
}

void emit(int *p, int *q) {
    static int cur;
    //fputs("emit: ", stderr);
    for ( ; p != q; p++) {
        seq[*p] = ++cur;
        //fprintf(stderr, "%d[%d] ", *p, cur);
    }
    //fputs("\n", stderr);
}

void sort() {
    split_blocks();
    auto Q = new Heap<Block>(m);
    for (int i = 1; i <= m; i++)
        Q->h[i] = b[i];
    Q->initialize();
    //fprintf(stderr, "bcnt = %d\n", bcnt);
    while (Q->n > 1) {
        auto s = Q->first();
        auto t = Q->second();
        int *ed = s.locate(*t.p);
        emit(s.p, ed);
        if (s.q == ed) Q->pop();
        else {
            s.p = ed;
            Q->drop(s);
        }
    }
    emit(Q->first().p, Q->first().q);
}


//******//
// MAIN //
//******//


void terminate();
void swap(int i, int j);
void relabel();
bool is_sorted();

static bool _mimic;
static int _K, _cnt;
static int _seq[NMAX + 1];

namespace interactive {
    static int swap_cnt;
    static int pos[NMAX + 1];
    static struct {
        int i, j;
    } swap[KMAX];
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        _mimic = true;
        auto fp = fopen(argv[1], "r");
        fscanf(fp, "%d%d", &n, &_K);
        for (int i = 1; i <= n; i++)
            fscanf(fp, "%d", _seq + i);
        //fprintf(stderr, "[%d] ", _K);
        //for (int i = 1; i <= n; i++)
        //    fprintf(stderr, "%d ", _seq[i]);
        //fputs("\n", stderr);
        fclose(fp);
    } else {
        scanf("%d", &n);
    }

    sort();
    if (_mimic) assert(is_sorted());
    relabel();
    terminate();

    if (_mimic) {
        fprintf(stderr, "_cnt = %d\n", _cnt);
        fprintf(stderr, "bcnt = %d\n", bcnt);
        int fcnt = 0;
        for (auto &e : pcnt) if (e.second > 1) {
            //fprintf(stderr, "%d-%d: %d\n", e.first.first, e.first.second, e.second);
            fcnt++;
        }
        fprintf(stderr, "fcnt = %d\n", fcnt);
    }
    return 0;
}

int cmp(int i, int j) {
    assert(i != j);

    if (_mimic) {
        //fprintf(stderr, "QUERY: %d - %d\n", i, j);
        _cnt++;
        return _seq[i] < _seq[j];
    } else {
        printf("%d %d\n", i, j);
        fflush(stdout);
        int ret;
        scanf("%d", &ret);
        return ret;
    }
}

void terminate() {
    using interactive::swap_cnt;

    if (!_mimic) {
        puts("0 0");
        printf("%d\n", swap_cnt);
        for (int i = 0; i < swap_cnt; i++)
            printf("%d %d\n", interactive::swap[i].i, interactive::swap[i].j);
        fflush(stdout);
        int _;
        scanf("%d", &_);
    }
}

void swap(int i, int j) {
    using interactive::pos;
    using interactive::swap_cnt;

#ifndef NOSTDERR
    fprintf(stderr, "swap %d, %d\n", i, j);
#endif

    assert(swap_cnt < KMAX);
    assert(1 <= i && i <= n);
    assert(1 <= j && j <= n);
    assert(i != j);

    interactive::swap[swap_cnt++] = {i, j};
    int t = seq[i];
    seq[i] = seq[j];
    seq[j] = t;
    pos[seq[i]] = i;
    pos[seq[j]] = j;
}

void relabel() {
    using interactive::pos;

    for (int i = 1; i <= n; i++)
        pos[seq[i]] = i;

#ifndef NOSTDERR
    for (int i = 1; i <= n; i++)
        fprintf(stderr, "seq[%d] = %d\n", i, seq[i]);
    for (int i = 1; i <= n; i++)
        fprintf(stderr, "pos[%d] = %d\n", i, pos[i]);
#endif

    for (int i = 1; i <= n; i++)
        if (seq[i] != i)
            swap(i, pos[i]);
}

bool is_sorted() {
    for (int i = 1; i <= n; i++)
        if (seq[i] != _seq[i]) return false;
    return true;
}

namespace RESPECT {
//**********************//
// TOO YOUNG TOO SIMPLE //
// SOMETIMES N A Ï V E! //
//**********************//

/**
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 */
}
