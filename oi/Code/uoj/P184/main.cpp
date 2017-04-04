// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define QMAX 100000
#define NMAX 100000

constexpr int dx[] = {0, 0, 1, -1};
constexpr int dy[] = {-1, 1, 0, 0};

struct Point {
    int x, y;
};

struct Query {
    int x1, y1, u1;
    int x2, y2, u2;
    int answer;
};

static int n, m, q;

inline int id(int x, int y) {
    return x * (m + 2) + y;
}

static int w[NMAX + 10][4];
static int go[NMAX + 10][4];
static int dist[NMAX + 10];
static bool exist[NMAX + 10];
static Query que[QMAX + 10];
static Query *ptr[QMAX + 10];
static Query *q1[QMAX + 10];
static Query *q2[QMAX + 10];

struct State {
    int x, d;

    bool operator<(const State &b) const {
        return d > b.d;
    }
};

inline bool chkmin(int &dest, int src) {
    if (src < dest) {
        dest = src;
        return true;
    }

    return false;
}

void dijkstra(int l, int r, int t, int b, int x0, int y0) {
    for (int i = l; i <= r; i++) {
        for (int j = b; j <= t; j++) {
            int u = id(i, j);
            exist[u] = false;
            dist[u] = INT_MAX;
        }
    }
    dist[id(x0, y0)] = 0;

    priority_queue<State> q;
    q.push({id(x0, y0), 0});
    while (!q.empty()) {
        State u = q.top();
        q.pop();

        if (exist[u.x])
            continue;
        exist[u.x] = true;

        for (int p = 0; p < 4; p++) {
            int v = go[u.x][p];
            
            if (exist[v])
                continue;

            if (chkmin(dist[v], u.d + w[u.x][p])) {
                q.push({v, dist[v]});
            }
        }
    }
}

void solve(int l, int r, int t, int b, int head, int tail) {
    if (tail < head || r < l || t < b)
        return;
    if (l == r && t == b) {
        for (int i = head; i <= tail; i++) {
            ptr[i]->answer = 0;
        }

        return;
    }

    auto update = [&]() {
        for (int _i = head; _i <= tail; _i++) {
            chkmin(
                ptr[_i]->answer,
                dist[ptr[_i]->u1] + dist[ptr[_i]->u2]
            );
        }
    };

    if (r - l > t - b) {
        int mid = (r + l) / 2;
        for (int i = b; i <= t; i++) {
            dijkstra(l, r, t, b, mid, i);
            update();
        }

        for (int i = b; i <= t; i++) {
            exist[id(mid, i)] = true;
        }

        int s1 = 0, s2 = 0;
        for (int i = head; i <= tail; i++) {
            Query *comm = ptr[i];
            if (comm->x1 < mid && comm->x2 < mid)
                q1[++s1] = comm;
            else if (comm->x1 > mid && comm->x2 > mid)
                q2[++s2] = comm;
        }

        int pos = head;
        for (int i = 1; i <= s1; i++) {
            ptr[pos++] = q1[i];
        }
        for (int i = 1; i <= s2; i++) {
            ptr[pos++] = q2[i];
        }

        solve(l, mid - 1, t, b, head, head + s1 - 1);
        solve(mid + 1, r, t, b, head + s1, head + s1 + s2 - 1);
    } else {
        int mid = (t + b) / 2;
        for (int i = l; i <= r; i++) {
            dijkstra(l, r, t, b, i, mid);
            update();
        }

        for (int i = l; i <= r; i++) {
            exist[id(i, mid)] = true;
        }

        int s1 = 0, s2 = 0;
        for (int i = head; i <= tail; i++) {
            Query *comm = ptr[i];
            if (comm->y1 < mid && comm->y2 < mid)
                q1[++s1] = comm;
            else if (comm->y1 > mid && comm->y2 > mid)
                q2[++s2] = comm;
        }

        int pos = head;
        for (int i = 1; i <= s1; i++) {
            ptr[pos++] = q1[i];
        }
        for (int i = 1; i <= s2; i++) {
            ptr[pos++] = q2[i];
        }

        solve(l, r, mid - 1, b, head, head + s1 - 1);
        solve(l, r, t, mid + 1, head + s1, head + s1 + s2 - 1);
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int p = 0; p < 4; p++) {
                go[id(i, j)][p] = id(i + dx[p], j + dy[p]);
            }
        }
    }

    for (int i = 0; i <= n + 1; i++) {
        exist[id(i, 0)] = exist[id(i, m + 1)] = true;
    }

    for (int i = 0; i <= m + 1; i++) {
        exist[id(0, i)] = exist[id(n + 1, i)] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m - 1; j++) {
            int c;
            scanf("%d", &c);
            w[id(i, j + 1)][LEFT] = w[id(i, j)][RIGHT] = c;
        }
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m; j++) {
            int c;
            scanf("%d", &c);
            w[id(i, j)][UP] = w[id(i + 1, j)][DOWN] = c;
        }
    }

    scanf("%d", &q);

    for (int i = 1; i <= q; i++) {
        scanf("%d%d%d%d", &que[i].x1, &que[i].y1, &que[i].x2, &que[i].y2);
        que[i].u1 = id(que[i].x1, que[i].y1);
        que[i].u2 = id(que[i].x2, que[i].y2);
        que[i].answer = INT_MAX;
        ptr[i] = que + i;
    }
}

int main() {
    initialize();
    solve(1, n, m, 1, 1, q);
    for (int i = 1; i <= q; i++) {
        printf("%d\n", que[i].answer);
    }

    return 0;
}
