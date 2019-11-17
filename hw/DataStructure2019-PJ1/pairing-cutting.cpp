//#define SUBMIT_VERSION  // Uncomment this when submit to eLearning

//#define NDEBUG
#define NOSTDERR  // Debug information dumped by interactive protocols
//#define DUPLICATE_CHECKER  // Duplicate `cmp` checker
#define ENABLE_CACHE

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
// PAIRING-CUTTING ALGORITHM //
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

static int lcnt, gcnt;
struct Segment {
    Segment()
        : head(nullptr), tail(nullptr) {}
    Segment(int *_head, int *_tail)
        : head(_head), tail(_tail) {}
    Segment(int left, int right)
        : head(new int[right - left]), tail(head + right - left) {
        for (int i = left; i < right; i++)
            head[i - left] = i;
    }

    int *head, *tail;

    int length() const {
        return tail - head;
    }

    bool empty() const {
        return head == tail;
    }

    bool may_cut() const {
        return length() > 1;
    }

    auto locate(int key) -> int* {
        return _binary_search(key);
    }

    auto _sequential_search(int key) -> int* {
        for (int i = 1; ; i++) {
            if (cmp(key, head[i]) == LT) return head + i;
            if (cmp(tail[-i - 1], key) == LT) return tail - i;
        }
    }

    auto _binary_search(int key) -> int* {
        int l = 0, r = length();
        while (l < r) {
            int m = (l + r) / 2;
            if (cmp(head[m], key) == LT) l = m + 1;
            else r = m;
        }
        return head + l;
    }

    bool operator<(const Segment &s) const {
        lcnt++;
        return cmp(head[0], s.head[0]) == LT;
    }

    bool operator>(const Segment &s) const {
        gcnt++;
        return cmp(s.head[0], tail[-1]) == LT;
    }
};

struct CutResult {
    Segment front, rear;
};

auto cut(Segment s, int key) -> CutResult {
    int *p = s.locate(key);
    return {
        {s.head, p}, {p, s.tail}
    };
}

auto concat(Segment u, Segment v) -> Segment {
    int len = u.length() + v.length();
    auto mem = new int[len];
    memcpy(mem, u.head, sizeof(int) * u.length());
    memcpy(mem + u.length(), v.head, sizeof(int) * v.length());
    return {mem, mem + len};
}

static int n, m;
static int seq[NMAX + 1];
static int sgn[NMAX + 1];

static Segment s[5 * KMAX];

void print_segments() {
    for (int i = 1; i <= m; i++) {
        fprintf(stderr, "[");
        for (int *p = s[i].head; p != s[i].tail; p++)
            fprintf(stderr, p +  1 == s[i].tail ? "%d] " : "%d ", *p);
    }
    fputs("\n", stderr);
}

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

void pairing(int i) {
    assert(i < m);
    s[i] = concat(s[i], s[i + 1]);
    if (i + 1 < m)
        memmove(s + i + 1, s + i + 2, sizeof(Segment) * (m - i - 1));
    m--;
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

    //print_segments();
    while (!stk.empty()) {
        auto u = stk.pop();
        //fprintf(stderr, "[%d] Process [%d, %d)\n", m, u.segment.left, u.segment.right);

        int l = u.start, r = m + 1;
        while (l < r) {
            int mi = (l + r) / 2;
            if (s[mi] < u.segment) l = mi + 1;
            else r = mi;
        }
        if (l <= m)
            memmove(s + l + 1, s + l, sizeof(Segment) * (m - l + 1));
        s[l] = u.segment;
        m++;
        //fprintf(stderr, "Insert at %d\n", l);

        auto split = [](Segment &x, int i) {
            int key = s[i].head[0];
            auto ret = cut(x, key);
            assert(!ret.front.empty());
            assert(!ret.rear.empty());
            x = ret.front;
            //fprintf(stderr, "NEW [%d, %d), start = %d\n", ret.rear.left, ret.rear.right, i + 1);
            stk.push({ret.rear, i + 1});
        };

        //print_segments();
        bool flag = true;
        if (l < m && s[l].may_cut() && s[l] > s[l + 1]) {
            flag = false;
            split(s[l], l + 1);
        }

        if (l > 1 && s[l - 1].may_cut() && s[l - 1] > s[l])
            split(s[l - 1], l);
#ifdef ENABLE_PAIRING
        else if (flag && l > 1) {
            pairing(l - 1);
            //fprintf(stderr, "Pairing: @%d ", l - 1);
            //print_segments();
        }
#endif
    }
}

void concat_segments() {
    for (int i = 1, k = 1; i <= m; i++)
    for (int *p = s[i].head; p != s[i].tail; p++)
        seq[*p] = k++;
}

void solve() {
    scan_segments();
    sort_segments();
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
static int _seq[NMAX + 1];

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
