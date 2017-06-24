/**
 * Haven't submit
 */
// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef unsigned long long u64;

static int n, m;
static bool mat[20][20];

void initialize() {
    scanf("%d%d", &n, &m);

    char buf[20];
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf + 1);
        for (int j = 1; j <= m; j++) {
            mat[i][j] = buf[j] == '*';
        }
    }
}

struct State {
    int x, y;
    u64 s;

    bool operator==(const State &b) const {
        return x == b.x && y == b.y && s == b.s;
    }
};

namespace std {

template <>
struct hash<State> {
    size_t operator()(const State &u) const {
        return (u.s << 8) + (u.x << 4) + u.y;
    }
};

}

static queue<State> q;
static unordered_map<State, u64> dp;

void send(State u, u64 v) {
    if (!dp.count(u))
        q.push(u);
    dp[u] += v;
}

u64 encode(int a[]) {
    u64 r = 0;
    for (int i = m + 1; i >= 1; i--) {
        r = (r << 3) + a[i];
    }

    return r;
}

void decode(u64 s, int a[]) {
    for (int i = 1; i <= m + 1; i++) {
        a[i] = s & 7;
        s >>= 3;
    }
}

int get(u64 s, int p) {
    return (s & (7UL << 3 * (p - 1))) >> 3 * (p - 1);
}

u64 set(u64 s, int p, int v) {
    return (s & (~(7UL << 3 * (p - 1)))) + (v << 3 * (p - 1));
}

u64 clear(u64 s, int p) {
    return s & (~(7UL << 3 * (p - 1)));
}

void show(u64 s) {
    for (int i = 1; i <= m + 1; i++) {
        printf("%llu ", s & 7);
        s >>= 3;
    }
    printf("\n");
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    State initial;
    if (mat[1][1])
        initial = {1, 1, 0};
    else
        initial = {1, 1, 011UL};

    dp[initial] = 1;
    q.push(initial);

    int lx = n, ly = m;
    while (mat[lx][ly]) {
        ly--;

        if (ly < 1) {
            lx--;
            ly = m;
        }
    }

    // printf("lx = %d, ly = %d\n", lx, ly);

    u64 ans = 0;
    while (!q.empty()) {
        State u = q.front();
        // printf("%d, %d: %llu\n", u.x, u.y, dp[u]);
        // show(u.s);
        q.pop();

        if (u.x == lx && u.y == ly) {
            if (u.s == 0)
                ans = dp[u];
        }

        if (u.x > lx)
            break;

        static int a[20];
        decode(u.s, a);
        u64 ns;
        u64 val = dp[u];
        if (u.y == m) {
            // 检查最后一个插头
            if (a[m + 1])
                continue;

            if (mat[u.x + 1][1] && !a[1]) {
                ns = u.s << 3;
                send({u.x + 1, 1, ns}, val);
            } else if (!mat[u.x + 1][1]) {
                if (!a[1]) {
                    ns = 0;
                    for (int i = 2; i <= m; i++) {
                        ns = set(ns, i + 1, a[i] == 1 ? 2 : a[i]);
                    }
                    ns = set(ns, 1, 1);
                    ns = set(ns, 2, 1);
                    send({u.x + 1, 1, ns}, val);
                }

                if (a[1]) {
                    ns = u.s << 3;
                    send({u.x + 1, 1, ns}, val);
                    ns = clear(ns, 2);
                    ns = set(ns, 1, 1);
                    send({u.x + 1, 1, ns}, val);
                }
            }
        } else {
            #define SEND send({u.x, u.y + 1, ns}, val);
            if (mat[u.x][u.y + 1] && !a[u.y + 1] && !a[u.y + 2]) {
                // 障碍
                ns = u.s;
                SEND
            } else if (!mat[u.x][u.y + 1]) {
                if (a[u.y + 1] == a[u.y + 2] && a[u.y + 1] &&
                    u.x == lx && u.y + 1 == ly) {
                    // 结束
                    ns = clear(u.s, u.y + 1);
                    ns = clear(ns, u.y + 2);
                    SEND
                }

                if (a[u.y + 1] && a[u.y + 2] &&
                    a[u.y + 1] != a[u.y + 2]) {
                    // 合并两个连通块
                    int x = a[u.y + 1], y = a[u.y + 2];
                    ns = clear(u.s, u.y + 1);
                    ns = clear(ns, u.y + 2);
                    for (int i = 1; i <= m + 1; i++) {
                        if (get(ns, i) == x || get(ns, i) == y)
                            ns = set(ns, i, min(x, y));
                    }
                    SEND
                }

                if (!a[u.y + 1] && !a[u.y + 2]) {
                    ns = set(u.s, u.y + 1, u.y + 1);
                    ns = set(ns, u.y + 2, u.y + 1);
                    SEND
                }

                if (a[u.y + 1] && !a[u.y + 2]) {
                    ns = u.s;
                    SEND
                    ns = set(u.s, u.y + 2, a[u.y + 1]);
                    ns = clear(ns, u.y + 1);
                    SEND
                }

                if (!a[u.y + 1] && a[u.y + 2]) {
                    ns = set(u.s, u.y + 1, a[u.y + 2]);
                    ns = clear(ns, u.y + 2);
                    SEND
                    ns = u.s;
                    SEND
                }
            }
        }
    }

    printf("%llu\n", ans);

    return 0;
}
