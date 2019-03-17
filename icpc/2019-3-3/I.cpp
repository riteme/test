#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define MMAX 8
#define WIDTH 4
#define SIZE 3079
#define SMAX 4096

#define MASK(L) ((1ULL << (L)) - 1)

typedef unsigned long long u64;
typedef long long i64;

static int n, m;

struct State {
    State() = default;
    State(u64 r) : dat(r) {}

    u64 dat = 0;

    bool has(int i) const {
        return get(MMAX + m * WIDTH + i);
    }

    void has(int i, bool v) {
        set(MMAX + m * WIDTH + i, v);
    }

    bool col(int i) const {
        return get(i);
    }

    void col(int i, bool v) {
        set(i, v);
    }

    int pure() const {
        int c = dat & MASK(MMAX);
        if (!c) return 0;
        if (c == (1 << m) - 1) return 1;
        return -1;
    }

    int id(int i) const {
        return get(i * WIDTH + MMAX, WIDTH);
    }

    void id(int i, int v) {
        set(i * WIDTH + MMAX, v, WIDTH);
    }

    void idto(int x, int y) {
        x = id(x);
        for (int i = 0; i < m; i++)
            if (id(i) == x) id(i, y);
    }

    bool nxtid(int i) const {
        int x = id(i), c = col(i);
        int mask = MASK(WIDTH);
        u64 d = dat >> MMAX;
        for (int j = 0; j < m; j++, d >>= WIDTH)
            if (i != j && (d & mask) == x) return true;
        d = dat;
        for (int j = 0; j < m; j++, d >>= 1)
            if (i != j && (d & 1) == c) return false;
        return true;
    }

    int maxid() const {
        int r = 0;
        for (int i = 0; i < m; i++) {
            int x = id(i);
            if (x > r) r = x;
        }
        return r;
    }

    void update() {
        int mp[16] = {0};
        for (int i = 0; i <= MMAX; i++) mp[i] = -1;
        int mask = MASK(WIDTH);
        u64 d = dat >> MMAX, o = 0;
        for (int i = 0, t = 0; i < m; i++, d >>= WIDTH) {
            int x = d & mask;
            if (mp[x] < 0) mp[x] = t++;
            o |= mp[x] << (i * WIDTH);
        }
        set(MMAX, o, m * WIDTH);
        int c = dat & MASK(MMAX);
        if (!has(0) && c < (1 << m) - 1) has(0, 1);
        if (!has(1) && c) has(1, 1);
    }

    int get(int i) const {
        return (dat >> i) & 1;
    }

    int get(int i, int c) const {
        return (dat >> i) & ((1 << c) - 1);
    }

    void set(int i, bool v) {
        if (v) dat |= 1ULL << i;
        else dat &= ~(1ULL << i);
    }

    void set(int i, u64 v, int c) {
        dat = (dat & (~(MASK(c) << i))) | (v << i);
    }
};

struct HashTable {
    i64 val[SMAX];
    u64 key[SMAX];
    int nxt[SMAX], cnt, head[SIZE];

    i64 &operator[](const u64 i) {
        int p = i % SIZE;
        for (int x = head[p]; x; x = nxt[x])
            if (key[x] == i) return val[x];
        key[++cnt] = i;
        val[cnt] = 0;
        nxt[cnt] = head[p];
        head[p] = cnt;
        return val[cnt];
    }

    void reset() {
        memset(head, 0, sizeof(head));
        cnt = 0;
    }

    void copy(const HashTable &b) {
        memcpy(head, b.head, sizeof(head));
        cnt = b.cnt;
        memcpy(nxt + 1, b.nxt + 1, sizeof(int) * cnt);
        memcpy(key + 1, b.key + 1, sizeof(u64) * cnt);
        memcpy(val + 1, b.val + 1, sizeof(i64) * cnt);
    }
};

static i64 MOD;
static HashTable f, g;

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

char *bin(State &s) {
    static int p = 0;
    static char buf[100000];
    char *pos = buf + p;
    p += sprintf(buf + p, "[");
    for (int i = 0; i < m; i++)
        p += sprintf(buf + p, "%s%d%s", s.col(i) ? "+" : "-", s.id(i), i == m - 1 ? "" : " ");
    p += sprintf(buf + p, "]");
    buf[p++] = 0;
    return pos;
}

int main() {
    scanf("%d%d%lld", &n, &m, &MOD);

    for (int c = 0; c < (1 << m); c++) {
        State s(c);
        s.id(0, 0);
        for (int i = 1, j = 0; i < m; i++) {
            if (s.col(i) != s.col(i - 1)) j++;
            s.id(i, j);
        }
        if (c < (1 << m) - 1) s.has(0, 1);
        if (c) s.has(1, 1);
        f[s.dat]++;
    }

    for (int i = 2; i <= n; i++) for (int j = 0; j < m; j++) {
        //printf("i = %d, j = %d\n", i, j + 1);
        g.copy(f);
        f.reset();
        for (int p = 1; p <= g.cnt; p++) {
            State s(g.key[p]), ns;
            int c = s.maxid();
            i64 cnt = g.val[p];
            if (!j) {
                for (int b = 0; b < 2; b++) {
                    const int k = b^1;
                    if (s.pure() == k && s.has(b)) continue;
                    ns = s;
                    if (s.col(0) == k && s.nxtid(0)) {
                        ns.col(0, b), ns.id(0, c + 1);
                        ns.update();
                        add(f[ns.dat], cnt);
                        //printf("%s → %s [%lld, %s%s]\n", bin(s), bin(ns), cnt, s.has(0) ? "+" : ".", s.has(1) ? "+" : ".");
                    } else if (s.col(0) == b) add(f[s.dat], cnt);
                }
            } else {
                for (int b = 0; b != 2; b++) {
                    const int k = b^1;
                    int t = c + 1;
                    if (s.pure() == k && s.has(b)) continue;
                    ns = s;
                    if (s.col(j - 1) == b) t = s.id(j - 1);
                    if (s.col(j) == b) {
                        if (s.id(j) != t) ns.idto(j, t);
                        ns.update();
                        add(f[ns.dat], cnt);
                        //printf("%s → %s [%lld, %s%s]\n", bin(s), bin(ns), cnt, s.has(0) ? "+" : ".", s.has(1) ? "+" : ".");
                    } else if (s.nxtid(j)) {
                        ns.col(j, b), ns.id(j, t);
                        ns.update();
                        add(f[ns.dat], cnt);
                        //printf("%s → %s [%lld, %s%s]\n", bin(s), bin(ns), cnt, s.has(0) ? "+" : ".", s.has(1) ? "+" : ".");
                    }
                }
            }
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= f.cnt; i++)
        if (State(f.key[i]).maxid() < 2) add(ans, f.val[i]);
    printf("%lld\n", ans);

    return 0;
}
