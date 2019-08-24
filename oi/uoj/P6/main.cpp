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

static i64 x0, a, b, c, d;
static Random *randint;
static int n, m, q;
static int P[NMAX * NMAX + 10];
static int pos[NMAX * NMAX + 10];
static int upper[NMAX + 10];
static int lower[NMAX + 10];

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

    for (int i = 0; i < n; i++) {
        upper[i] = m - 1;
    }

    for (int i = 1; i <= n * m; i++) {
        int x = pos[i] / m;
        int y = pos[i] - x * m;

        if (y < lower[x] ||
            y > upper[x])
            continue;

        printf("%d ", i);

        int j = x - 1;
        while (j >= 0 && upper[j] > y) {
            upper[j] = y;
            j--;
        }

        j = x + 1;
        while (j < n && lower[j] < y) {
            lower[j] = y;
            j++;
        }
    }

    printf("\n");

    return 0;
}
