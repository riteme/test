#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 3000
#define MOD 1000000007

typedef long long i64;

struct Point {
    Point() : cnt(0), x(0), y(0) {}
    Point(i64 _x, i64 _y) : cnt(0), x(_x), y(_y) {}

    int cnt;
    i64 x, y;

    int id() const {
        if (x >= 0 && y >= 0)
            return 0;
        if (x >= 0 && y <= 0)
            return 1;
        if (x <= 0 && y <= 0)
            return 2;
        return 3;
    }

    i64 length() const {
        return x * x + y * y;
    }

    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    i64 operator%(const Point &b) const {
        return x * b.y - y * b.x;
    }

    bool operator<(const Point &b) const {
        return x < b.x || (x == b.x && y < b.y);
    }

    bool operator==(const Point &b) const {
        return x == b.x && y == b.y;
    }
};

bool polar_cmp(const Point &a, const Point &b) {
    if (a.id() != b.id())
        return a.id() < b.id();

    i64 p = a % b;
    return p < 0 || (p == 0 && a.length() < b.length());
}

static int n;
static i64 tpow[NMAX + 10];
static Point P[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    tpow[0] = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &P[i].x, &P[i].y);
        tpow[i] = tpow[i - 1] * 2 % MOD;
    }

    sort(P + 1, P + n + 1);
    int j = 1;
    for (int i = 1; i <= n; i++) {
        if (P[i] == P[j])
            P[j].cnt++;
        else {
            P[++j] = P[i];
            P[j].cnt = 1;
        }
    }

    n = j;
}

static Point tmp[NMAX * 2 + 10];

int main() {
    freopen("random.in", "r", stdin);
    freopen("random.out", "w", stdout);
    initialize();

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        int t = 0;
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                tmp[++t] = P[j] - P[i];
                tmp[t].cnt = P[j].cnt;
            }
        }

        sort(tmp + 1, tmp + n, polar_cmp);
        memcpy(tmp + t + 1, tmp + 1, sizeof(Point) * t);
        int l = 2, r = 2, rcnt = tmp[2].cnt, mcnt = 0;
        for (int j = 1; j <= t; j++) {
            if (j == l) {
                rcnt -= tmp[l].cnt;
                l++;
                mcnt = 0;
            }

            while (l <= 2 * t &&
                   tmp[l].id() == tmp[j].id() && tmp[l] % tmp[j] == 0) {
                if (l <= r)
                    rcnt -= tmp[l].cnt;
                l++;
            }

            if (l > r) {
                r = l;
                rcnt = tmp[r].cnt;
            }

            if (tmp[l] % tmp[j] > 0) {
                while (r + 1 <= 2 * t && tmp[r + 1] % tmp[j] > 0) {
                    r++;
                    rcnt += tmp[r].cnt;
                }
            }

            i64 contr = (tpow[P[i].cnt] - 1) * (tpow[tmp[j].cnt] - 1) % MOD *
                        tpow[(r <= t * 2 && tmp[r] % tmp[j] > 0) ? rcnt : 0] % MOD *
                        tpow[mcnt] % MOD;
            ans = (ans + contr) % MOD;
            // printf("(%lld, %lld) -> (%lld, %lld): +%lld\n",
            //         P[i].x, P[i].y, P[i].x + tmp[j].x, P[i].y + tmp[j].y, contr);
            // printf("rcnt = %d, mcnt = %d\n", rcnt, mcnt);
            mcnt += tmp[j].cnt;
        }
    }

    for (int i = 1; i <= n; i++) {
        ans = (ans + tpow[P[i].cnt] - 1) % MOD;
    }

    if (ans < 0)
        ans += MOD;

    printf("%lld\n", ans);

    return 0;
}
