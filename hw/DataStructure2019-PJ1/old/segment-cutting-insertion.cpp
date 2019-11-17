//#define NDEBUG
//if (argc > 1)
#define NOSTDERR

#include <cassert>
#include <cstdio>
#include <cstring>

//#include <map>

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

static int bcnt;
struct Block {
    Block() {}
    Block(int len) : p(new int[len]), q(p + len) {}

    int *p, *q;

    int len() const {
        return q - p;
    }

    int *locate(int i) {
        //if (cmp(*(q - 1), i) == LT) return q;

        /*
        int l = 0, r = q - p;
        while (l < r) {
            int m = (l + r) >> 1;
            if (cmp(p[m], i) == LT) l = m + 1;
            else r = m;
        }
        return p + l;
        */

        int s = 1;
        for ( ; q - s >= p && cmp(i, *(q - s)) == LT; s <<= 1) ;
        if (s == 1) return q;
        s >>= 1;
        int j = s;
        for ( ; s; s >>= 1)
        if (q - j - s >= p && cmp(i, *(q - j - s)) == LT)
            j += s;
        return q - j;
    }

    int &operator[](int i) {
        assert(p + i < q);
        return p[i];
    }

    bool operator<(const Block &z) const {
        bcnt++;
        return cmp(*p, *z.p) == LT;
    }
};

template <typename T>
void _swap(T &x, T &y) {
    T z = y;
    y = x;
    x = z;
}

template <typename T>
struct Heap {
    Heap(int _n) : n(_n) {}

    int n;
    T h[NMAX + 1];

    void move(int s, int t) {
        T x = h[s];
        if (t < s) {
            for (int i = s; i > t; i--)
                h[i] = h[i - 1];
        } else {
            for (int i = s; i < t; i++)
                h[i] = h[i + 1];
        }
        h[t] = x;
    }

    int locate(int l, int r, T x) {
        while (l < r) {
            int m = (l + r) / 2 + 1;
            if (h[m] < x) l = m;
            else r = m - 1;
        }
        return l;
    }

    void drop(T key) {
        h[1] = key;
        move(1, locate(2, n, key));
    }

    void pop() {
        for (int i = 1; i < n; i++)
            h[i] = h[i + 1];
        n--;
    }

    void initialize() {
        for (int i = n - 1; i >= 1; i--)
            move(i, locate(i + 1, n, h[i]));
    }

    T first() const {
        return h[1];
    }

    T second() const {
        return h[2];
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
        if (s != LT) {
            assert(t);
            add_block(tmp, t, LT);
            ls = NIL;
            tmp[0] = i;
            t = 1;
        } else {
            tmp[t++] = i;
            ls = s;
        }
    }
    if (t)
        add_block(tmp, t, LT);
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

//typedef std::pair<int, int> pii;
//static std::map<pii, int> pcnt;
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
        //int fcnt = 0;
        //for (auto &e : pcnt) if (e.second > 1) {
        //    //fprintf(stderr, "%d-%d: %d\n", e.first.first, e.first.second, e.second);
        //    fcnt++;
        //}
        //fprintf(stderr, "fcnt = %d\n", fcnt);
    }
    return 0;
}

int cmp(int i, int j) {
    assert(i != j);

    //int x = i < j ? i : j;
    //int y = i < j ? j : i;
    //pcnt[std::make_pair(x, y)]++;

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
