#include <cstdio>
#include <cstring>
#include <climits>

#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

#define NMAX 5000

typedef long long i64;

class Random {
 public:
    Random(i64 _x0, i64 _a, i64 _b, i64 _c, i64 _d)
        : x0(_x0), a(_a), b(_b), c(_c), d(_d) {}

    int next() {
        return x0 = ((a * x0 + b) * x0 + c) % d;
    }

 private:
    i64 x0, a, b, c, d;
};

struct Segment {
    Segment()
        : left(0), right(0) {}
    Segment(int l, int r)
        : left(l), right(r) {}

    int left, right;
};

static i64 x0, a, b, c, d;
static Random *randint;
static int n, m, q;
static int P[NMAX * NMAX + 10];
static int pos[NMAX * NMAX + 10];
static map<int, Segment> s;

void initialize() {
    scanf("%lld%lld%lld%lld%lld", &x0, &a, &b, &c, &d);
    randint = new Random(x0, a, b, c, d);

    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n * m; i++) {
        P[i] = i;
        int p = randint->next() % i + 1;
        pos[P[p]] = i - 1;
        pos[i] = p - 1;
        P[i] = P[p];
        P[p] = i;
    }

    int u, v;
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &u, &v);
        pos[P[u]] = v - 1;
        pos[P[v]] = u - 1;
        swap(P[u], P[v]);
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("random_2014.in", "r", stdin);
    freopen("random_2014.out", "w", stdout);
#endif
    initialize();

    s[0] = Segment(0, 0);
    s[n - 1] = Segment(m - 1, m - 1);
    for (int i = 1; i <= n * m; i++) {
        int x = pos[i] / m;
        int y = pos[i] - x * m;

        if (s.count(x)) {
            auto iter = s.find(x);
            Segment &seg = iter->second;

            if (y < seg.left) {
                if (y >= prev(iter)->second.right) {
                    printf("%d ", i);
                    seg.left = y;
                }
            } else if (y > seg.right) {
                if (y <= next(iter)->second.left) {
                    printf("%d ", i);
                    seg.right = y;
                }
            } else
                printf("%d ", i);
        } else {
            auto iter = s.lower_bound(x);

            if (prev(iter)->second.right <= y &&
                y <= iter->second.left) {
                printf("%d ", i);
                s[x] = Segment(y, y);
            }
        }
    }

    printf("\n");

    return 0;
}
