#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int INF = 1000000000;
constexpr int NMAX = 40000;
constexpr int MMAX = 10;
constexpr int QMAX = 40000;
constexpr int CMAX = 1000000;
constexpr int SMAX = 1 << MMAX;

struct vec {
    vec() : x(0), y(0) {}
    vec(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    i64 len2() const {
        return i64(x) * x + i64(y) * y;
    }

    bool up() const {
        return y > 0 || (y == 0 && x > 0);
    }

    vec operator-() const {
        return {-x, -y};
    }
    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }
    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
    i64 operator*(const vec &z) const {
        return i64(x) * z.x + i64(y) * z.y;
    }
    i64 operator%(const vec &z) const {
        return i64(x) * z.y - i64(y) * z.x;
    }
};

constexpr int BEFORE0 = 0;
constexpr int BEFORE1 = 1;
constexpr int ADD = 11;
constexpr int SUB = 12;
constexpr int AFTER0 = 100;
constexpr int AFTER1 = 101;

struct Event {
    vec v;
    int *t, y, rk;

    bool operator<(const Event &z) const {
        i64 c = v % z.v;
        return c > 0 ||
            (c == 0 && rk < z.rk) ||
            (c == 0 && rk == z.rk && v.len2() < z.v.len2());
    }
};

int sgn[SMAX];
int n, m, q, ans[QMAX + 10];
int cnt, ys[NMAX + MMAX + 10], idx[CMAX + 10];
vec P[NMAX + 10], Q[MMAX + 10];
vector<Event> ev[MMAX + 1];
int bit[NMAX + MMAX + 10];

void clean() {
    memset(bit + 1, 0, sizeof(int) * cnt);
}

void modify(int x, int v) {
    for ( ; x <= cnt; x += x & -x) {
        bit[x] += v;
    }
}

int query(int x) {
    int r = 0;
    for ( ; x; x -= x & -x) {
        r += bit[x];
    }
    return r;
}

void submit(int *t, vec u) {
    *t = n;
    for (int S = 1; S < (1 << m); S++) {
        int maxy = 0;
        int lk = 0, rk = 2 * m + 1;
        for (int i = 1; i <= m; i++)
        if ((S >> (i - 1)) & 1) {
            maxy = max(maxy, idx[Q[i].y]);

            i64 lc = (Q[i] - u) % (Q[lk] - u);
            i64 rc = (Q[rk] - u) % (Q[m + i] - u);

            if (lc > 0 || (lc == 0 && Q[i].y < Q[lk].y))
                lk = i;
            if (rc > 0 || (rc == 0 && Q[m + i].y < Q[rk].y))
                rk = m + i;
        }

        vec lp = Q[lk] - u;
        vec rp = Q[rk] - u;
        if (lp % rp > 0)
            continue;

        int s = sgn[S];
        ev[lk].push_back({lp, t, cnt, AFTER0 ^ s});
        ev[lk].push_back({lp, t, maxy - 1, AFTER1 ^ s});
        ev[rk].push_back({rp, t, cnt, BEFORE1 ^ s});
        ev[rk].push_back({rp, t, maxy - 1, BEFORE0 ^ s});
    }
}

void evaluate() {
    for (int i = 1; i <= 2 * m; i++) {
        sort(ev[i].begin(), ev[i].end());

        clean();
        for (auto &e : ev[i]) {
            if (e.rk == SUB)
                modify(e.y, +1);
        }

        for (auto &e : ev[i]) {
            if (e.rk == ADD)
                modify(e.y, +1);
            else if (e.rk == SUB)
                modify(e.y, -1);
            else {
                int s = e.rk & 1 ? -1 : 1;
                *e.t += s * query(e.y);
            }
        }
    }
}

int main() {
    for (int S = 1; S < SMAX; S++) {
        sgn[S] = sgn[S >> 1] ^ (S & 1);
    }

    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].x, &P[i].y);
        ys[cnt++] = P[i].y;
    }

    Q[0] = {-INF, 0};
    Q[2 * m + 1] = {INF, 0};
    for (int i = 1; i <= m; i++) {
        int l, r, y;
        scanf("%d%d%d", &l, &r, &y);
        Q[i] = {l, y};
        Q[m + i] = {r, y};
        ys[cnt++] = y;
    }

    sort(ys, ys + cnt);
    cnt = unique(ys, ys + cnt) - ys;
    for (int i = 0; i < cnt; i++) {
        idx[ys[i]] = i + 1;
    }

    for (int i = 1; i <= 2 * m; i++) {
        ev[i].reserve(2 * n);
        for (int j = 1; j <= n; j++) {
            vec v = P[j] - Q[i];
            if (v.up())
                ev[i].push_back({v, NULL, idx[P[j].y], ADD});
            else
                ev[i].push_back({-v, NULL, idx[P[j].y], SUB});
        }
    }

    for (int i = 1; i <= q; i++) {
        vec u;
        scanf("%d%d", &u.x, &u.y);
        submit(ans + i, u);
    }

    evaluate();

    for (int i = 1; i <= q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
