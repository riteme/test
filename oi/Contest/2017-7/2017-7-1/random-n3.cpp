#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 3000
#define MOD 1000000007

typedef long long i64;

struct Point {
    Point() : x(0), y(0) {}
    Point(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

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

static int n;
static i64 tpow[NMAX + 10];
static int cnt[NMAX + 10];
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
            cnt[j]++;
        else {
            cnt[++j] = 1;
            P[j] = P[i];
        }
    }

    n = j;
}

int main() {
    initialize();

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;

            int lx = min(P[i].x, P[j].x), rx = max(P[i].x, P[j].x);
            int ly = min(P[i].y, P[j].y), ry = max(P[i].y, P[j].y);
            int contr = 0;
            i64 c = (tpow[cnt[i]] - 1) * (tpow[cnt[j]] - 1) % MOD;
            for (int k = 1; k <= n; k++) {
                if (i == k || j == k)
                    continue;

                i64 p = (P[k] - P[i]) % (P[j] - P[i]);
                if ((p == 0 &&
                     lx <= P[k].x && P[k].x <= rx &&
                     ly <= P[k].y && P[k].y <= ry) || p < 0)
                    contr += cnt[k];
            }

            ans = (ans + c * tpow[contr]) % MOD;
        }
    }

    for (int i = 1; i <= n; i++) {
        ans = (ans + tpow[cnt[i]] - 1) % MOD;
    }

    if (ans < 0)
        ans += MOD;

    printf("%lld\n", ans);

    return 0;
}
