#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define MMAX 200000
#define QMAX 200000

static int n, m, q;
static int U[MMAX + 10], V[MMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", U + i, V + i);
    }
}

static int cnt;
static int set[NMAX + 10];

inline void make_set() {
    cnt = n;

    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }
}

inline int find_set(const int &x) {
    return set[x] == x ? x : set[x] = find_set(set[x]);
}

inline void union_set(const int &x, const int &y) {
    int dx = find_set(x);
    int dy = find_set(y);

    if (dx != dy) {
        cnt--;
        set[dx] = dy;
    }
}

static int query(int left, int right) {
    make_set();

    for (int i = left; i <= right; i++) {
        union_set(U[i], V[i]);
    }

    return cnt;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        while (q--) {
            int left, right;
            scanf("%d%d", &left, &right);

            printf("%d\n", query(left, right));
        }
    }

    return 0;
}
