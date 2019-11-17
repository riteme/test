/**
 * This is source is inherited from segment-cutting-hinging.cpp.
 * Based on assumptions that test data are randomized.
 * Added size-filter & merging.
 */

//#define SUBMIT_VERSION  // Uncomment this when submit to eLearning

//#define NDEBUG
#define NOSTDERR  // Debug information dumped by interactive protocols
//#define DUPLICATE_CHECKER  // Duplicate `cmp` checker
#define ENABLE_CACHE
#define SHOW_SEQUENCE  // Show real values when print_segments

#define RANDOM_DATA  // Weird hacks

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <random>

#ifdef DUPLICATE_CHECKER
#incl ude <map>
#endif

#define KMAX 100
#define NMAX 10000

#define LT 1
#define GT 0
#define NIL -1


//***************************//
// SEGMENT-CUTTING ALGORITHM //
//***************************//


int cmp(int i, int j);
void start_record();
void stop_record();

template <typename T, unsigned N>
struct Stack {
    Stack() : size(0) {}

    int size;
    T stk[N];

    void push(const T &x) {
        assert(size < N);
        stk[size++] = x;
    }

    auto pop() -> T {
        assert(size > 0);
        return stk[--size];
    }

    bool empty() const {
        return !size;
    }

    auto operator[](const size_t i) -> T& {
        assert(i < size);
        return stk[size - i - 1];
    }
};

constexpr int THRESHOLD = 5000;
static int CUT_THRESHOLD = 2;  // Default to 2 when n < 5000. Otherwise 1
static int LARGE_THRESHOLD = 500;  // Default to 500 when n < 5000. Otherwise 3
constexpr int LEN_THRESHOLD = 256;
constexpr int LOGK0 = 8;
//constexpr int LOGK1 = 4;
constexpr int MAGIC_NUMBER = 3;

static int lcnt, gcnt;
struct Segment {
    Segment()
        : left(nullptr), right(nullptr), lcut(0), rcut(0) {}
    Segment(int _left, int _right)
        : left(new int[_right - _left]), right(left + _right - _left), lcut(0), rcut(0) {
        for (int i = _left; i < _right; i++)
            left[i - _left] = i;
    }
    Segment(int *_left, int *_right)
        : left(_left), right(_right), lcut(0), rcut(0) {}
    Segment(int *_left, int *_right, int _lcut, int _rcut)
        : left(_left), right(_right), lcut(_lcut), rcut(_rcut) {}

    int *left, *right;
    int lcut, rcut;

    int size() const {
        return right - left;
    }

    bool empty() const {
        return left == right;
    }

    bool lstrp() const {
        return lcut >= CUT_THRESHOLD;
    }

    bool rstrp() const {
        return rcut >= CUT_THRESHOLD;
    }

    bool may_cut() const {
#ifdef RANDOM_DATA  // Possibly cut once at each end of segment
        return size() > 1 &&
            (lcut < CUT_THRESHOLD || rcut < CUT_THRESHOLD);
#else
        return size() > 1;
#endif
    }

    auto locate(int key) -> int* {
#ifdef RANDOM_DATA  // Small tail optimization
        return _sequential_search(key);
#else
        if (size() < LEN_THRESHOLD) return _binary_search(key);
        else return _heuristic_locate(key);
#endif
    }

    auto _sequential_search(int key) -> int* {
        for (int i = 1; ; i++) {
            if (cmp(key, left[i]) == LT) return left + i;
            if (cmp(right[-(i + 1)], key) == LT) return right - i;
        }
    }

    auto _binary_search(int key) -> int* {
        int l = 0, r = size();
        while (l < r) {
            int m = (l + r) / 2;
            if (cmp(left[m], key) == LT) l = m + 1;
            else r = m;
        }
        return left + l;
    }

    auto _exponential_search_from_left(int key) -> int* {
        int i = 0;
        for (int step = 1 << (LOGK0 - 1); step; step >>= 1)
        if (i + step < size() && cmp(left[i + step], key) == LT)
            i += step;
        return left + i + 1;
    }

    auto _exponential_search_from_right(int key) -> int* {
        int i = size();
        for (int step = 1 << (LOGK0 - 1); step; step >>= 1)
        if (i - step >= 0 && cmp(key, left[i - step]) == LT)
            i -= step;
        return left + i;
    }

    auto _heuristic_locate(int key) -> int* {
        assert(size() >= THRESHOLD);
        return cmp(right[-(1 << LOGK0)], key) == LT ?
            _exponential_search_from_right(key) :
            _exponential_search_from_left(key);
    }

    bool operator<(const Segment &s) const {
        lcnt++;
        return cmp(left[0], s.left[0]) == LT;
    }

    bool operator>(const Segment &s) const {
        gcnt++;
        return cmp(s.left[0], right[-1]) == LT;
    }
};

struct CutResult {
    Segment front, rear;
};

auto cut(Segment s, int key) -> CutResult {
    int *p = s.locate(key);
    return {
        {s.left, p,
         s.lcut, static_cast<int>(s.right - p)},
        {p, s.right,
         static_cast<int>(p - s.left), s.rcut}
    };
}

auto concat(Segment u, Segment v) -> Segment {
    int len = u.size() + v.size();
    auto mem = new int[len];
    memcpy(mem, u.left, sizeof(int) * u.size());
    memcpy(mem + u.size(), v.left, sizeof(int) * v.size());
    return {mem, mem + len, u.lcut, v.rcut};
}

#ifdef SHOW_SEQUENCE
static int _seq[NMAX + 1];
#endif

void print_segments(Segment *s, int m) {
    for (int i = 1; i <= m; i++) {
        fputs("[", stderr);
        for (int *p = s[i].left; p != s[i].right; p++)
#ifdef SHOW_SEQUENCE
            fprintf(stderr,
                p + 1 != s[i].right ? "%d " : "%d] ", _seq[*p]);
#else
            fprintf(stderr,
                p + 1 != s[i].right ? "%d " : "%d] ", *p);
#endif
    }
    fputs("\n", stderr);
}

/**
 * Insertion would increase n by 1.
 */
int insertion(Segment *s, int &n, Segment u, int start = 1) {
    int l = start, r = n + 1;
    while (l < r) {
        int mi = (l + r) / 2;
        if (s[mi] < u) l = mi + 1;
        else r = mi;
    }
    if (l <= n)
        memmove(s + l + 1, s + l, sizeof(Segment) * (n - l + 1));
    s[l] = u;
    n++;
    return l;
}

static int n, m, K;
static int seq[NMAX + 1];
static int sgn[NMAX + 1];

static Segment s[5 * KMAX], ns[5 * KMAX], ts[5 * KMAX];

void scan_segments() {
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

void sort_segments() {
    struct Item {
        Segment segment;
        int start;
    };

    static Stack<Item, 5 * KMAX> stk;

    for (int i = m; i >= 2; i--)
        stk.push({s[i], 1});
    m = 1;

    //print_segments(s, m);
    while (!stk.empty()) {
        auto u = stk.pop();
        int l = insertion(s, m, u.segment, u.start);

        auto split = [](int i) -> bool {
            int key = s[i].left[0];
            auto &x = s[i - 1];
            auto ret = cut(x, key);
            assert(!ret.front.empty());
            assert(!ret.rear.empty());

            int d = 0;
            x = ret.front;
            if (x.size() == 1) {
                d = 1;
                ns[++K] = x;
                memmove(s + i - 1, s + i, sizeof(Segment) * (m - i + 1));
                m--;
            }
            if (ret.rear.size() == 1)
                ns[++K] = ret.rear;
            else
                stk.push({ret.rear, i + 1 - d});
            return d;
        };

        bool dropped = false;
        if (l < m && s[l].may_cut() && s[l] > s[l + 1])
            dropped = split(l + 1);
        if (!dropped && l > 1 && s[l - 1].may_cut() && s[l - 1] > s[l])
            split(l);

        //print_segments(s, m);
    }

    int k0 = 1;
    for (int i = 2; i <= K; i++)
        insertion(ns, k0, ns[i]);

    //print_segments(s, m);
    //print_segments(ns, K);

    for (int i = 1, j = 1, p = 0; i <= m || j <= K; ) {
        Segment u;
        if (i > m)
            u = ns[j++];
        else if (j > K)
            u = s[i++];
        else if (s[i].size() > MAGIC_NUMBER &&  // FIXME
            p && j <= K && ts[p].size() >= LARGE_THRESHOLD)
            u = ns[j++];
        else if (s[i] < ns[j]) {
            // FIXME: Magic fix
            if (s[i].size() <= MAGIC_NUMBER && s[i] > ns[j]) {
                auto ret = cut(s[i], ns[j].left[0]);
                u = ret.front;
                if (m - i < K - j)
                    insertion(s, m, ret.rear, i + 1);
                else
                    insertion(s, K, ret.rear, j + 1);
                i++;
            } else u = s[i++];
        } else
            u = ns[j++];
        ts[++p] = u;
    }
    m += K;
    memcpy(s + 1, ts + 1, sizeof(Segment) * m);

    //print_segments(s, m);
}

void concat_segments() {
    for (int i = 1, k = 1; i <= m; i++)
    for (int *p = s[i].left; p != s[i].right; p++)
        seq[*p] = k++;
}

void solve() {
    if (n >= THRESHOLD) {
        CUT_THRESHOLD = 1;
        LARGE_THRESHOLD = 3;
        scan_segments();
        sort_segments();
    }
    else {
        m = 1;
        s[1] = {1, 2};
        for (int i = 2; i <= n; i++)
            insertion(s, m, {i, i + 1});
    }
    concat_segments();
}


//*******//
// CACHE //
//*******//


int _cmp(int i, int j);

static bool _record = false;
static int G[NMAX + 1][NMAX + 1];

void start_record() {
    _record = true;
}

void stop_record() {
    _record = false;
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

static int cached;
int cached_cmp(int i, int j) {
    memset(visited, 0, sizeof(visited));
    if (dfs(i, j)) {
        cached++;
        return GT;
    }

    memset(visited, 0, sizeof(visited));
    if (dfs(j, i)) {
        cached++;
        return LT;
    }

    int ret = _cmp(i, j);
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
        fprintf(stderr, "%d cached\n", cached);

#ifdef DUPLICATE_CHECKER
        int fcnt = 0;
        for (auto &e : pcnt) if (e.second > 1) {
            //fprintf(stderr, "%d-%d: %d\n", e.first.first, e.first.second, e.second);
            fcnt++;
        }
        fprintf(stderr, "fcnt = %d\n", fcnt);
#endif
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
