#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 18
#define SMAX (1 << NMAX)

struct Edge {
    Edge(int _v, bool _mark) : v(_v), mark(_mark), mark0(_mark) {}

    int v;
    bool mark, mark0;
    Edge *rev;
};

static int n, t;
static vector<Edge*> G[2 * NMAX + 10];
static int mask[SMAX];
static int bit[SMAX];
static char A[NMAX + 10][NMAX + 10];
static int w[NMAX + 10];

void link(int u, int v) {
    Edge *e = new Edge(v, false);
    Edge *re = new Edge(u, false);
    e->rev = re; re->rev = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d", &n);
    t = 2 * n + 1;
    for (int i = 1; i <= t; i++)
        G[i].clear();

    for (int i = 1; i <= n; i++) {
        scanf("%s", A[i] + 1);
        link(n + i, t);
        mask[1 << i] = 0;
        for (int j = 1; j <= n; j++)
        if (A[i][j] == '1') {
            link(i, n + j);
            mask[1 << (i - 1)] |= 1 << (j - 1);
        }
    }

    for (int S = 2; S < (1 << n); S++) {
        for (int i = 0; i < n; i++) if ((S >> i) & 1) {
            int nS = S ^ (1 << i);
            if (nS)
                mask[S] = mask[nS] | mask[1 << i];
        }
    }

    for (int i = 1; i <= n; i++)
        scanf("%s", A[i] + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);
}

#define TEST(S, i) ((S >> (i - 1)) & 1)

bool check(int S) {
    if (bit[S] != bit[mask[S]]) return false;
    for (int i = 1; i <= n; i++) if (TEST(S, i))
    for (int j = i + 1; j <= n; j++) if (TEST(S, j) && A[i][j] == '1')
        return false;
    return true;
}

bool mark[2 * NMAX + 10];

bool dfs(int x) {
    if (mark[x]) return false;
    if (x == t) return true;
    mark[x] = true;
    for (auto e : G[x])
    if (!e->mark && !mark[e->v] && dfs(e->v)) {
        e->mark = true;
        e->rev->mark = false;
        return true;
    }
    return false;
}

static int cnt[NMAX + 10];

int pw(int a, int k) {
    switch (k) {
        case 0: return 1; break;
        case 1: return a; break;
        case 2: return a * a; break;
        case 3: return a * a * a; break;
    }
    return 0;
}

int eval(int S) {
    memset(cnt, 0, sizeof(cnt));
    int c[NMAX + 10], seq[NMAX + 10];
    memcpy(c, w, sizeof(c));
    for (int i = 1; i <= n; i++)
        seq[i] = i;
    for (int i = 1; i <= t; i++)
    for (auto e : G[i])
        e->mark = e->mark0;

    int ret = 0, sum = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        memset(mark, 0, sizeof(mark));
        for (int i = 1; i <= n; i++)
            mark[i] = !TEST(S, i);

        for (int i = 1; i <= n; i++) {
            int u = seq[i];
            if (dfs(u)) {
                flag = true;
                sum++;
                cnt[u]++;
                ret += c[u];
                c[u] = pw(w[u], cnt[u] + 1) - pw(w[u], cnt[u]);
                while (i < n && c[u] > c[seq[i + 1]]) {
                    swap(seq[i], seq[i + 1]);
                    i++;
                }
                break;
            }
        }
    }

    return sum == n ? ret : INT_MAX;
}

int main() {
    bit[1] = 1;
    for (int S = 2; S < SMAX; S++)
        bit[S] = bit[S >> 1] + (S & 1);
    int T;
    scanf("%d", &T);
    while (T--) {
        initialize();
        int ans = INT_MAX;
        for (int S = 1; S < (1 << n); S++) if (check(S))
            ans = min(ans, eval(S));
        printf("%d\n", ans == INT_MAX ? -1 : ans);
    }
    return 0;
}
