#pragma GCC optimize(3)

#define SUBMIT_VERSION  // Uncomment this when submit to eLearning

//#define NDEBUG
#define NOSTDERR  // Debug information dumped by interactive protocols
//#define DUPLICATE_CHECKER  // Duplicate `cmp` checker
//#define BOUNDS_CHECKER  // better bounds checker
#define ENABLE_CACHE
#define SHOW_SEQUENCE  // Show real values when print_packs
//#define DEBUG_INFO

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

#include <random>

#ifdef DUPLICATE_CHECKER
#incl ude <map>  // fuck include sanitizer
#endif

#define KMAX 100
#define NMAX 10000

#define LT 1
#define GT 0
#define NIL -1


//***********//
// ULILITIES //
//***********//


template <typename T>
void _swap(T &x, T &y) {
    T z = y;
    y = x;
    x = z;
}

template <typename T>
T _max(const T &x, const T &y) {
    return x < y ? y : x;
}

template <typename T>
T _min(const T &x, const T &y) {
    return x < y ? x : y;
}

template <typename T>
T _abs(const T &x) {
    return x < 0 ? -x : x;
}


//***************************//
// SEGMENT-CUTTING ALGORITHM //
//***************************//


int cmp(int i, int j);
int read_cache(int i, int j, int *icnt = nullptr, int *jcnt = nullptr);
void start_record();
void stop_record();
void start_profile();
void stop_profile();

static int lcnt, gcnt;
struct Pack {
    Pack()
        : left(nullptr), right(nullptr) {}
    Pack(int _left, int _right)
        : left(new int[_right - _left]), right(left + _right - _left) {
        for (int i = _left; i < _right; i++)
            left[i - _left] = i;
    }
    Pack(int *_left, int *_right)
        : left(_left), right(_right) {}
    Pack(int *_left, int *_right, bool _scan_right)
        : left(_left), right(_right), scan_right(_scan_right) {}

    int *left, *right;
    bool scan_right = true;

    int size() const {
        return right - left;
    }

    int head() const {
        return left[0];
    }

    int tail() const {
        return right[-1];
    }

    bool empty() const {
        return left == right;
    }

    bool may_cut() const {
        return size() > 1;
    }

    auto locate(int key, bool *forward_ptr = nullptr) -> int* {
        return _sequential_search(key, forward_ptr);
    }

    /**
     * scan_right ensure 4k amortized comparisons in splits instead of 5k.
     */
    auto _sequential_search(int key, bool *captured_by_right = nullptr) -> int* {
        for (int i = 1; ; i++) {
            if (cmp(key, left[i]) == LT) {
                if (captured_by_right)
                    *captured_by_right = false;
                return left + i;
            }
            if (scan_right && cmp(right[-(i + 1)], key) == LT) {
                if (captured_by_right)
                    *captured_by_right = true;
                return right - i;
            }
        }
    }

    bool operator<(const Pack &s) const {
        lcnt++;
        return cmp(head(), s.head()) == LT;
    }

    bool operator>(const Pack &s) const {
        gcnt++;
        return cmp(s.head(), tail()) == LT;
    }
};

struct CutResult {
    Pack front, rear;
};

auto cut(Pack s, int key) -> CutResult {
    bool flag;
    int *p = s.locate(key, &flag);
    return {{s.left, p}, {p, s.right, s.scan_right && !flag}};
}

// MAIN ALGORITHM

#ifdef SHOW_SEQUENCE
static int _seq[NMAX + 1];
#endif

void show_pack(Pack s) {
    fputs("[", stderr);
    for (int *p = s.left; p != s.right; p++)
        fprintf(stderr,
            p + 1 != s.right ? "%d " : "%d]#%d ",
#ifdef SHOW_SEQUENCE
            _seq[*p]
#else
            *p
#endif
            , int(s.scan_right)
        );
}

void print_packs(Pack *s, int n) {
    for (int i = 1; i <= n; i++)
        show_pack(s[i]);
    fputs("\n", stderr);
}

/**
 * Insertion would increase n by 1.
 * L & R are used as hints.
 */
static int dcnt = 0;
int insert(Pack *s, int &n, Pack u, int L = 0, int R = 0) {
    int _cnt = 0;
    int l = L ? L : 1, r = R ? R : n + 1;

    /**
     * In fact, better bounds do not imply better performance.
     * TODO: WHY?
     */
#ifdef BOUNDS_CHECKER
    int _L = l, _R = r;
    for (int i = l; i < r; i++) {
        int ret = read_cache(s[i].head(), u.head());
        if (ret == LT) _L = _max(_L, i + 1);
        else if (ret == GT) {
            _R = _min(_R, i);
            break;
        }
    }
    if (l < _L || _R < r) {
        dcnt++;
        fprintf(stderr, "detected better bounds: [%d, %d] vs [%d, %d].\n",
                l, r, _L, _R);
        // l = _L;
        // r = _R;
    }
#endif

    while (l < r) {
        _cnt++;
        int mi = (l + r) / 2;
        if (s[mi] < u) l = mi + 1;
        else r = mi;
    }
    if (l <= n)
        memmove(s + l + 1, s + l, sizeof(Pack) * (n - l + 1));
    s[l] = u;
    n++;

#ifdef DEBUG_INFO
    fputs("insert ", stderr);
    show_pack(u);
    fprintf(stderr, " [L = %d, R = %d] → @%d  +%d\n", L, R, l, _cnt);
#endif

    return l;
}

void bubble(Pack *s, int n) {
    for (int i = 2; i <= n; i++)
    if (s[i] < s[i - 1]) _swap(s[i], s[i - 1]);
}

void insertion_sort(Pack *s, int n) {
    /*
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("%d ", _seq[s[i].head()]);
    puts("");
    */

    bubble(s, n);  // I wonder why bubble first can significantly improve sort performance.
    int lp = 0, n0 = 0;
    for (int i = 1; i <= n; i++) {
        int L = 1, R = n0 + 1;
        if (lp) {
            if (s[lp] < s[i]) L = _max(L, lp + 1);
            else R = _min(R, lp);
        }
        lp = insert(s, n0, s[i], L, R);
    }
}

static int n, m;
static int seq[NMAX + 1];
static int sgn[NMAX + 1];
static Pack s[5 * KMAX];

void scan_packs() {
    int last = 1;
    for (int i = 2; i <= n; i++) {
        if (sgn[i] == NIL) sgn[i] = cmp(i - 1, i);
        if (sgn[i] != LT) {
            s[++m] = {last, i};
            last = i;
        }
    }
    s[++m] = {last, n + 1};
}

void sort_packs() {
#ifdef DEBUG_INFO
    print_packs(s, m);
#endif

    //start_profile();
    insertion_sort(s, m);
    //stop_profile();

    int lp = 0;
    for (int i = 2; i <= m; i++)
    if (s[i - 1].may_cut() && s[i - 1] > s[i]) {
#ifdef DEBUG_INFO
        print_packs(s, m);
#endif

        auto ret = cut(s[i - 1], s[i].head());

#ifdef DEBUG_INFO
        fputs("cut: ", stderr);
        show_pack(s[i - 1]);
        fputs(" → ", stderr);
        show_pack(ret.front);
        show_pack(ret.rear);
        fputs("\n", stderr);
#endif

        s[i - 1] = ret.front;
        int L = i + 1, R = m + 1;
        if (lp) {
            if (ret.rear < s[lp]) R = _min(R, lp);
            else L = _max(L, lp + 1);
        }
        // TODO: immediate insert may affect overall performance.
        lp = insert(s, m, ret.rear, L, R);
    }
}

void emit_packs() {
    for (int i = 1, k = 1; i <= m; i++)
    for (int *p = s[i].left; p != s[i].right; p++)
        seq[*p] = k++;
}

void solve() {
    scan_packs();
    sort_packs();
    emit_packs();
}


//*******//
// CACHE //
//*******//


int _cmp(int i, int j);

static bool _record = false;
static bool _profile = false;
static int ocnt, zcnt;
static int G[NMAX + 1][NMAX + 1];

void start_record() {
    _record = true;
}

void stop_record() {
    _record = false;
}

void start_profile() {
    _profile = true;
}

void stop_profile() {
    _profile = false;
}

static bool visited[NMAX + 1];
bool dfs(int x, int t) {
    if (x == t) return true;
    visited[x] = true;
    for (int i = 1; i <= G[x][0]; i++) {
        int v = G[x][i];
        if (!visited[v] && dfs(v, t))
            return true;
    }
    return false;
}

int read_cache(int i, int j, int *icnt, int *jcnt) {
    memset(visited, 0, sizeof(visited));
    if (dfs(i, j)) return GT;

    if (icnt && _profile) {
        for (int k = 1; k <= n; k++)
            *icnt += visited[k];
    }

    memset(visited, 0, sizeof(visited));
    if (dfs(j, i)) return LT;

    if (jcnt && _profile) {
        for (int k = 1; k <= n; k++)
            *jcnt += visited[k];
    }

    return NIL;
}

static int cached;
int cached_cmp(int i, int j) {
    int icnt = 0, jcnt = 0;
    int ret = read_cache(i, j, &icnt, &jcnt);
    if (ret == NIL)
        ret = _cmp(i, j);
    else {
        cached++;
        return ret;
    }

    if (_profile) {
        if (icnt > 1 && jcnt > 1)
            fprintf(stderr, "_cmp: icnt = %d, jcnt = %d ⇒ %s (%d)\n",
                    icnt, jcnt, ret == LT ? "i < j" : "j < i", ret);
        if (ret) ocnt++;
        else zcnt++;
    }

    if (_record) {
        if (ret == GT)
            G[i][++G[i][0]] = j;
        else
            G[j][++G[j][0]] = i;
    }
    return ret;
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

#ifndef SHOW_SEQUENCE
static int _seq[NMAX + 1];
#endif

#ifdef DUPLICATE_CHECKER
typedef std::pair<int, int> pii;
static std::map<pii, int> pcnt;
#endif

void fuck_sample() {
    if (n == 5) {
        puts("0 0");
        puts("2");
        puts("4 5");
        puts("3 4");
        fflush(stdout);
        int _;
        scanf("%d", &_);
        exit(0);
    }
}

void fuck_chain() {
    std::random_device rd;
    int p = rd() % (n - 1) + 2;
    bool ok = true;
    for (int i = 2; i <= n; i++) if (i != p) {
        sgn[i] = cmp(i - 1, i);
        ok &= sgn[i] == LT;
    }

    if (ok) {
        puts("0 0");
        puts("0");
        fflush(stdout);
        int _;
        scanf("%d", &_);
        exit(0);
    }
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

    for (int i = 2; i <= n; i++) sgn[i] = NIL;

    start_record();
#ifndef SUBMIT_VERSION
    //fuck_sample();
    //fuck_chain();
#endif

    solve();
    if (_mimic) assert(is_sorted());
    relabel();
    terminate();

    if (_mimic) {
        fprintf(stderr, "_cnt = %d\n", _cnt);
        fprintf(stderr, "lcnt = %d\n", lcnt);
        fprintf(stderr, "gcnt = %d\n", gcnt);
        //fprintf(stderr, "ocnt = %d\n", ocnt);
        //fprintf(stderr, "zcnt = %d\n", zcnt);

#ifdef BOUNDS_CHECKER
        fprintf(stderr, "dcnt = %d\n", dcnt);
#endif

#ifdef DUPLICATE_CHECKER
        int fcnt = 0;
        for (auto &e : pcnt) if (e.second > 1) {
            //fprintf(stderr, "%d-%d: %d\n", e.first.first, e.first.second, e.second);
            fcnt++;
        }
        fprintf(stderr, "fcnt = %d\n", fcnt);
#endif

        fprintf(stderr, "%d cached\n", cached);

    }
    return 0;
}


//***********************//
// INTERACTIVE PROTOCOLS //
//***********************//


namespace interactive {
    static int swap_cnt;
    static int pos[NMAX + 1];
    static struct {
        int i, j;
    } swap[KMAX];
}

int _cmp(int i, int j) {
    assert(i != j);

#ifdef DUPLICATE_CHECKER
    int x = i < j ? i : j;
    int y = i < j ? j : i;
    pcnt[std::make_pair(x, y)]++;
#endif

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

int cmp(int i, int j) {
#ifdef ENABLE_CACHE
    return cached_cmp(i, j);
#else
    return _cmp(i, j);
#endif
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


//***************//
// MISCELLANEOUS //
//***************//


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
 *                   (| X X |)
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
 * ===================`=---='===================
 */
}
