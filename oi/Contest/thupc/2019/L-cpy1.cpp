#include <cstdio>
#include <cstring>

#include <forward_list>
#include <queue>
#include <algorithm>

using namespace std;

#define MMAX 10000
#define NMAX 500

struct Item {
    int i, j, v;

    bool operator<(const Item &b) const {
        return v > b.v;
    }
};

static int m, n[MMAX + 10];
static int a[MMAX + 10][NMAX + 10];
static int last[MMAX + 10];
static forward_list<Item> _buc[2][NMAX + 10][2];
static auto buc = _buc[1];  // Support negative index
static int f[MMAX + 10];

inline void submit(int i1, int j1, const Item &t2) {
    int v = max(a[i1][j1], t2.v);
    f[i1] ^= v + i1 + t2.i;
    if (i1 != t2.i) f[t2.i] ^= v + i1 + t2.i;
}

int main() {
#ifdef USE_FILE_IO
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
#endif
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", n + i);
        for (int j = 1; j <= n[i]; j++)
            scanf("%d", a[i] + j);
        sort(a[i] + 1, a[i] + n[i] + 1);
    }

    priority_queue<Item> pq;
    for (int i = 1; i <= m; i++) pq.push({i, 0, 0});
    while (!pq.empty()) {
        auto u = pq.top();
        int i = u.i, j = u.j;
        pq.pop();
        last[i] = j;
        if (j < n[i]) pq.push({i, j + 1, a[i][j + 1]});

        int p[2] = { j - ((n[i] + 1) >> 1), j - (n[i] >> 1) };
        if (n[i] & 1) for (int b = 0; b < 2; b++) {
            auto &q = buc[p[b]][b];
            auto x = q.begin(), px = q.before_begin();
            while (x != q.end()) {
                if (last[x->i] > x->j) x = q.erase_after(px);
                else {
                    submit(i, j, *x);
                    px = x++;
                }
            }
        } else for (int b = 0; b < 2; b++) {
            auto &q = buc[p[1]][b];
            auto x = q.begin(), px = q.before_begin();
            while (x != q.end()) {
                if (last[x->i] > x->j) x = q.erase_after(px);
                else {
                    submit(i, j, *x);
                    px = x++;
                }
            }
        }
        buc[-p[!(n[i] & 1)]][n[i] & 1].push_front(u);
    }

    for (int i = 1; i <= m; i++) printf("%d\n", f[i] ^ (a[i][(n[i] + 1) >> 1] + 2 * i));

    return 0;
}
