#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define NUM 25

static int primes[] = {
     2,  3,  5,  7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97
};

struct Integer {
    Integer() {
        memset(cnt, 0, sizeof(cnt));
    }

    Integer(int x) {
        memset(cnt, 0, sizeof(cnt));

        for (int i = 0; i < NUM; i++) {
            while (x % primes[i] == 0) {
                cnt[i]++;
                x /= primes[i];
            }
        }
    }

    int cnt[NUM];

    Integer operator*(const Integer &b) const {
        Integer c;
        memcpy(c.cnt, cnt, sizeof(cnt));

        for (int i = 0; i < NUM; i++) {
            c.cnt[i] += b.cnt[i];
        }

        return c;
    }

    Integer operator/(const Integer &b) const {
        Integer c;
        memcpy(c.cnt, cnt, sizeof(cnt));

        for (int i = 0; i < NUM; i++) {
            c.cnt[i] -= b.cnt[i];
        }

        return c;
    }

    bool operator==(const Integer &b) const {
        return memcmp(cnt, b.cnt, sizeof(cnt)) == 0;
    }

    bool operator!=(const Integer &b) const {
        return memcmp(cnt, b.cnt, sizeof(cnt)) != 0;
    }
};

struct Ratio {
    Ratio() : x(1), y(1) {}

    Ratio(int _x, int _y) : x(_x), y(_y) {
        simplify();
    }

    Ratio(const Integer &_x, const Integer &_y)
        : x(_x), y(_y) {
        simplify();
    }

    Integer x, y;

    void simplify() {
        for (int i = 0; i < NUM; i++) {
            int minv = min(x.cnt[i], y.cnt[i]);
            x.cnt[i] -= minv;
            y.cnt[i] -= minv;
        }
    }

    Ratio operator*(const Ratio &b) const {
        return Ratio(x * b.x, y * b.y);
    }

    Ratio operator/(const Ratio &b) const {
        return Ratio(x * b.y, y * b.x);
    }

    bool operator==(const Ratio &b) const {
        return x == b.x && y == b.y;
    }

    bool operator!=(const Ratio &b) const {
        return x != b.x || y != b.y;
    }
};

struct Edge {
    Edge(int _u, int _v, bool _c, int _x, int _y)
        : u(_u), v(_v), c(_c ? 1 : 0), r(_x, _y) {}

    int u, v, c;
    Ratio r;

    int either(int x) {
        return u == x ? v : u;
    }
};

static int n, m;
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];
static int col[NMAX + 10];
static Ratio num[NMAX + 10];

bool dfs(int u) {
    marked[u] = true;

    for (size_t i = 0; i < G[u].size(); i++) {
        Edge *e = G[u][i];
        int v = e->either(u);

        if (marked[v]) {
            Ratio r = num[e->u];
            r = r / num[e->v];

            if (r != e->r || e->c != (col[e->u] ^ col[e->v]))
                return false;
        } else {
            col[v] = col[u] ^ e->c;

            if (u == e->u)
                num[v] = num[u] / e->r;
            else
                num[v] = num[u] * e->r;

            if (!dfs(v))
                return false;
        }
    }

    return true;
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int u = 1; u <= n; u++) {
        G[u].clear();
    }

    for (int i = 0; i < m; i++) {
        int u, v, x, y;
        scanf("%d%d%d%d", &u, &v, &x, &y);
        
        Edge *e = new Edge(u, v, y < 0, x, abs(y));
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        initialize();

        bool answer = true;
        memset(marked, 0, sizeof(marked));
        memset(col, 0, sizeof(col));
        for (int u = 1; answer && u <= n; u++) {
            if (!marked[u]) {
                num[u] = Ratio();
                answer &= dfs(u);
            }
        }

        printf("Case #%d: %s\n", i, answer ? "Yes" : "No");
    }

    return 0;
}
