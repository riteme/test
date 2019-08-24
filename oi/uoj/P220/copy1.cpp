// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 100000

typedef unsigned long long u64;

inline u64 code(u64 x, u64 y) {
    return (x << 32) + y;
}

inline int x(u64 c) {
    return c >> 32;
}

inline int y(u64 c) {
    return c & ((1ULL << 32) - 1);
}

static int n, m, c, cnt;
static unordered_map<u64, int> block;
static unordered_map<u64, int> ground;
static int sx[NMAX + 10];
static int sy[NMAX + 10];
static int father[NMAX * 24 + 10];
static vector<int> G[NMAX * 24 + 10];

inline int find(int x) {
    return father[x] ? father[x] = find(father[x]) : x;
}

inline void link(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y)
        father[x] = y;
}

inline bool has(int x, int y) {
    return x < 1 || x > n || y < 1 || y > m || block.count(code(x, y));
}

void initialize() {
    scanf("%d%d%d", &n, &m, &c);

    cnt = 0;
    block.clear();
    ground.clear();
    memset(father, 0, sizeof(int) * (24 * c + 10));
    for (int i = 1; i <= 24 * c; i++) {
        G[i].clear();
    }  // for

    for (int i = 1; i <= c; i++) {
        scanf("%d%d", sx + i, sy + i);
        block[code(sx[i], sy[i])] = i;
    }  // for

    for (int i = 1; i <= c; i++) {
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if (dx == 0 && dy == 0)
                    continue;

                int tx = sx[i] + dx;
                int ty = sy[i] + dy;
                u64 p = code(tx, ty);
                if (!has(tx, ty) && !ground.count(p)) {
                    ground[p] = ++cnt;
                    // printf("(%d, %d) : %d\n", tx, ty, cnt);
                }
            }  // for
        }      // for
    }          // for

    for (auto tup : ground) {
        u64 p = tup.first;
        int u = ground[p];
        int px = x(p), py = y(p);

        auto test = [u](const int px, const int py) {
            u64 cv = code(px, py);

            if (ground.count(cv)) {
                int v = ground[cv];
                // printf("%d %d\n", u, v);
                G[u].push_back(v);
                G[v].push_back(u);
                link(u, v);
            }
        };

        test(px + 1, py);
        test(px, py + 1);
    }  // foreach in ground
}

bool invalid() {
    u64 all = static_cast<u64>(n) * m;
    if (all - c <= 1)
        return true;
    else if (all - c == 2) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                u64 p = code(i, j);

                if (block.count(p))
                    continue;

                const int dx[] = {-1, 1, 0, 0};
                const int dy[] = {0, 0, -1, 1};

                for (int pos = 0; pos < 4; pos++) {
                    int tx = i + dx[pos];
                    int ty = j + dy[pos];

                    if (1 <= tx && tx <= n && 1 <= ty && ty <= m &&
                        !block.count(code(tx, ty)))
                        return true;
                }  // for

                return false;
            }  // for
        }      // for
    }

    return false;
}

static int f;
static bool cancut[NMAX * 24 + 10];
static bool marked[NMAX + 10];

bool search(int u) {
    marked[u] = true;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;

            u64 p = code(sx[u] + dx, sy[u] + dy);
            if (ground.count(p)) {
                int v = ground[p];
                int id = find(v);
                cancut[v] = true;

                if (!f)
                    f = id;
                else if (f != id)
                    return true;
            }
        }  // for
    }      // for

    auto test = [](const int tx, const int ty) {
        u64 p = code(tx, ty);

        if (block.count(p)) {
            int v = block[p];

            if (!marked[v] && search(v))
                return true;
        }

        return false;
    };

    if (test(sx[u] + 1, sy[u]))
        return true;
    if (test(sx[u] - 1, sy[u]))
        return true;
    if (test(sx[u], sy[u] + 1))
        return true;
    if (test(sx[u], sy[u] - 1))
        return true;

    return false;
}

bool ok0() {
    memset(cancut, 0, cnt + 10);
    memset(marked, 0, c + 10);

    for (int i = 1; i <= c; i++) {
        f = 0;
        if (!marked[i] && search(i))
            return true;
    }  // for

    return false;
}

static int timestamp;
static int dfn[NMAX * 24 + 10];
static int low[NMAX * 24 + 10];

bool dfs(int u, int f) {
    dfn[u] = low[u] = ++timestamp;
    // printf("%d\n", u);

    int c = 0;
    for (int v : G[u]) {
        if (v == f)
            continue;

        if (!dfn[v]) {
            c++;
            if (dfs(v, u))
                return true;
            if (f && low[v] >= dfn[u] && cancut[u])
                return true;

            low[u] = min(low[u], low[v]);
        } else
            low[u] = min(low[u], dfn[v]);
    }  // foreach in G[u]

    if (f == 0)
        return c > 1 && cancut[u];
    return false;
}

bool ok1() {
    if (n == 1 || m == 1)
        return true;

    timestamp = 0;
    memset(dfn, 0, sizeof(int) * (cnt + 10));

    for (int i = 1; i <= cnt; i++) {
        if (!dfn[i] && dfs(i, 0))
            return true;
    }  // for

    return false;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        if (invalid())
            puts("-1");
        else if (ok0())
            puts("0");
        else if (ok1())
            puts("1");
        else
            puts("2");
    }  // while

    return 0;
}  // function main
