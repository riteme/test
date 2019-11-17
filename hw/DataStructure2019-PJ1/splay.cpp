//#define NDEBUG
//#define NOSTDERR

#include <cassert>
#include <cstdio>
#include <cstring>

#define KMAX 100
#define NMAX 10000

#define LT 1
#define GT 0

//***********//
// ALGORITHM //
//***********//

int cmp(int i, int j);

static struct Node {
    int key;
    int fa, lch, rch;
} m[NMAX + 1];

#define ROT(name, l, r) \
void name(int x) { \
    int y = m[x].l; \
    assert(y); \
    m[m[y].r].fa = x; \
    m[x].l = m[y].r; \
    m[y].r = x; \
    if (m[x].fa > 0) { \
        int p = m[x].fa; \
        if (m[p].l == x) m[p].l = y; \
        else m[p].r = y; \
    } \
    m[y].fa = m[x].fa; \
    m[x].fa = y; \
}

ROT(lrot, lch, rch);
ROT(rrot, rch, lch);


int splay_s(int x, int t) {
    while (m[x].fa > 0 && m[x].fa != t) {
        int p = m[x].fa, p2 = m[p].fa;
        if (p2 > 0 && p2 != t) {
            if (m[p].lch == x && m[p2].lch == p) lrot(p2);
            else if (m[p].rch == x && m[p2].rch == p) rrot(p2);
        }
        if (m[p].lch == x) lrot(p);
        else rrot(p);
    }
    return x;
}

int splay(int x, int t) {
    while (m[x].fa > 0 && m[x].fa != t) {
        int p = m[x].fa, p2 = m[p].fa;
        if (p2 > 0 && p2 != t) {
            if (m[p].lch == x) {
                if (m[p2].lch == p) {
                    lrot(p2);
                    lrot(p);
                } else {
                    lrot(p);
                    rrot(p2);
                }
            } else if (m[p].rch == x) {
                if (m[p2].lch == p) {
                    rrot(p);
                    lrot(p2);
                } else {
                    rrot(p2);
                    rrot(p);
                }
            }
        } else {
            if (m[p].lch == x) lrot(p);
            else rrot(p);
        }
    }
    return x;
}

static int n;
static int perm[NMAX + 1];

struct Result {
    int p = 0, cmp = LT;
};

Result search(int x, int i) {
    Result ret;
    while (x) {
        ret.cmp = cmp(m[x].key, i);
        ret.p = x;
        //fprintf(stderr, "hit %d [key = %d]\n", x, m[x].key);
        if (ret.cmp == LT) x = m[x].rch;
        else x = m[x].lch;
    }
    return ret;
}

void scan(int x) {
    static int cnt;
    if (!x) return;
    scan(m[x].lch);
    perm[m[x].key] = ++cnt;
    //fprintf(stderr, "%d [%d, %d][cnt = %d]\n", x, m[x].lch, m[x].rch, cnt);
    scan(m[x].rch);
}

void sort() {
    int tr = 0, t = 0;
    for (int i = 1; i <= n; i++) {
        auto ret = search(tr, i);
        t++;
        m[t].key = i;
        m[t].fa = ret.p;
        if (!ret.p) tr = t;
        else {
            if (ret.cmp == LT) m[ret.p].rch = t;
            else m[ret.p].lch = t;
        }
        tr = splay_s(t, 0);
    }
    scan(tr);
}

//******//
// MAIN //
//******//

void terminate();
void swap(int i, int j);
void relabel();
bool is_sorted();

int main() {
    scanf("%d", &n);
    sort();
    relabel();
    assert(is_sorted());
    terminate();
    return 0;
}

namespace interactive {
    static int swap_cnt;
    static int pos[NMAX + 1];
    static struct {
        int i, j;
    } swap[KMAX];
}

int cmp(int i, int j) {
    assert(i != j);

    printf("%d %d\n", i, j);
    fflush(stdout);
    int ret;
    scanf("%d", &ret);
    return ret;
}

void terminate() {
    using interactive::swap_cnt;

    puts("0 0");
    printf("%d\n", swap_cnt);
    for (int i = 0; i < swap_cnt; i++)
        printf("%d %d\n", interactive::swap[i].i, interactive::swap[i].j);
    fflush(stdout);
    int _;
    scanf("%d", &_);
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
    int t = perm[i];
    perm[i] = perm[j];
    perm[j] = t;
    pos[perm[i]] = i;
    pos[perm[j]] = j;
}

void relabel() {
    using interactive::pos;

    for (int i = 1; i <= n; i++)
        pos[perm[i]] = i;

#ifndef NOSTDERR
    for (int i = 1; i <= n; i++)
        fprintf(stderr, "perm[%d] = %d\n", i, perm[i]);
    for (int i = 1; i <= n; i++)
        fprintf(stderr, "pos[%d] = %d\n", i, pos[i]);
#endif

    for (int i = 1; i <= n; i++)
        if (perm[i] != i)
            swap(i, pos[i]);
}

bool is_sorted() {
    using interactive::pos;

    for (int i = 1; i <= n; i++)
        if (pos[i] != i) return false;
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
