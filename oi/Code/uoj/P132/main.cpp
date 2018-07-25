// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <deque>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

#define NMAX 50000
#define INFTY 0x3f3f3f3f

#define SORT_REF(cmp)          \
    sort(ptr + 1, ptr + n + 1, \
         [](const Point *a, const Point *b) { return cmp; });

#define TUPLE_CMP(x, y, op1, op2) \
    a->x op1 b->x || (a->x == b->x && a->y op2 b->y)

#define INDEX(ptr) (ptr - point)

#define chkmax(a, b) \
    if (b > a)       \
        a = b;

struct Point {
    Point() {
        memset(this, 0, sizeof(Point));
    }

    int x, y, id, cnt;
    int dist, lans, rans;
    Point *l, *lt, *t, *rt, *r;
    Point *lmax, *rmax;
    bool entrance, exit;

    int negcut() const {
        return y + x;
    }

    int plucut() const {
        return y - x;
    }

    int maxdist() {
        return max(dist, max(lans, rans));
    }

    void update() {
        dist = 0;

        if (lt)
            chkmax(dist, lt->maxdist());
        if (t)
            chkmax(dist, t->maxdist());
        if (rt)
            chkmax(dist, rt->maxdist());

        dist++;
    }
};

class NetworkFlow {
 public:
    NetworkFlow(int _s, int _t) : s(_s), t(_t), ss(t + 1), tt(t + 2) {
        memset(M, 0, sizeof(M));
    }

    struct Edge {
        Edge(int _v, int _capacity) : v(_v), capacity(_capacity) {}

        int v, capacity;
        Edge *reverse_edge;
    };  // struct Edge

    Edge *link(int u, int v, int l, int r) {
        // if (u != s && v != t)
        // fprintf(stderr, "%d -> %d [%d, %d]\n", u, v, l, r);

        Edge *e = new Edge(v, r - l);
        Edge *re = new Edge(u, 0);
        e->reverse_edge = re;
        re->reverse_edge = e;
        G[u].push_back(e);
        G[v].push_back(re);
        M[v] += l;
        M[u] -= l;

        return e;
    }

    int solve() {
        for (int i = 1; i <= t; i++) {
            if (M[i] > 0)
                link(ss, i, 0, M[i]);
            if (M[i] < 0)
                link(i, tt, 0, -M[i]);
        }  // for

        dinic();

        auto p = link(t, s, 0, INFTY);

        dinic();

        return p->reverse_edge->capacity;
    }

 private:
    int s, t, ss, tt;
    vector<Edge *> G[NMAX + 10];
    int M[NMAX + 10];
    int dist[NMAX + 10];
    size_t pos[NMAX + 10];

    void bfs() {
        memset(dist, 0, sizeof(dist));

        queue<int> q;
        q.push(ss);
        dist[ss] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto e : G[u]) {
                int v = e->v;

                if (dist[v] || e->capacity == 0)
                    continue;

                dist[v] = dist[u] + 1;
                q.push(v);
            }  // foreach in G[u]
        }      // while
    }

    int dfs(int u, int maxflow) {
        if (u == tt)
            return maxflow;

        int current = 0;
        for (size_t &i = pos[u]; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (dist[u] + 1 != dist[v] || e->capacity == 0)
                continue;

            int flow = min(maxflow - current, e->capacity);
            flow = dfs(v, flow);
            current += flow;
            e->capacity -= flow;
            e->reverse_edge->capacity += flow;

            if (current == maxflow)
                break;
        }  // for

        return current;
    }

    void dinic() {
        while (true) {
            bfs();

            if (!dist[tt])
                break;

            memset(pos, 0, sizeof(pos));
            dfs(ss, INFTY);
        }  // while
    }
};  // class NetworkFlow

static int n;
static Point *root;
static Point point[NMAX + 10];
static Point *ptr[NMAX + 10];

void link_graph() {
    SORT_REF(TUPLE_CMP(y, x, <, <));
    for (int i = 1; i <= n; i++) {
        int dy = ptr[i]->y;
        ptr[i]->id = 1;
        for (; i < n && ptr[i + 1]->y == dy; i++) {
            ptr[i]->r = ptr[i + 1];
            ptr[i + 1]->l = ptr[i];
            ptr[i + 1]->id = ptr[i]->id + 1;
        }  // for
    }      // for

    SORT_REF(TUPLE_CMP(x, y, <, >));
    for (int i = 1; i <= n; i++) {
        int dx = ptr[i]->x;
        for (; i < n && ptr[i + 1]->x == dx; i++) {
            ptr[i + 1]->t = ptr[i];
        }  // for
    }      // for

    SORT_REF(TUPLE_CMP(negcut(), x, <, <));
    for (int i = 1; i <= n; i++) {
        int dc = ptr[i]->negcut();
        for (; i < n && ptr[i + 1]->negcut() == dc; i++) {
            ptr[i + 1]->lt = ptr[i];
        }  // for
    }      // for

    SORT_REF(TUPLE_CMP(plucut(), x, <, >));
    for (int i = 1; i <= n; i++) {
        int dc = ptr[i]->plucut();
        for (; i < n && ptr[i + 1]->plucut() == dc; i++) {
            ptr[i + 1]->rt = ptr[i];
        }  // for
    }      // for
}

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &point[i].x, &point[i].y);
        ptr[i] = point + i;
    }  // for

    root = &point[++n];
    ptr[n] = root;
    root->x = root->y = 0;

    link_graph();
}

void dp() {
    SORT_REF(TUPLE_CMP(y, x, >, <));

    for (int head = 1; head <= n; head++) {
        int tail = head;
        ptr[head]->update();
        for (; tail < n && ptr[tail + 1]->y == ptr[head]->y; tail++) {
            ptr[tail + 1]->update();
        }

        deque<Point *> q;
        q.push_back(ptr[head]);
        for (int i = head + 1; i <= tail; i++) {
            if (!q.empty()) {
                ptr[i]->lmax = q.front();
                ptr[i]->lans =
                    ptr[i]->lmax->dist + tail - head + 1 - ptr[i]->lmax->id;
            }

            while (!q.empty() &&
                   q.back()->dist - q.back()->id <= ptr[i]->dist - ptr[i]->id) {
                q.pop_back();
            }  // while

            q.push_back(ptr[i]);
        }  // for

        q.clear();
        q.push_back(ptr[tail]);
        for (int i = tail - 1; i >= head; i--) {
            if (!q.empty()) {
                ptr[i]->rmax = q.front();
                ptr[i]->rans = ptr[i]->rmax->dist + ptr[i]->rmax->id - 1;
            }

            while (!q.empty() &&
                   q.back()->dist + q.back()->id <= ptr[i]->dist + ptr[i]->id) {
                q.pop_back();
            }  // while

            q.push_back(ptr[i]);
        }  // for

        head = tail;
    }  // for
}

void walk(Point *u, int d) {
    if (u != root)
        printf("%ld ", INDEX(u));
    Point *v;

    if (d == 1)
        return;
    else if (u->lt && u->lt->maxdist() + 1 == d)
        walk(u->lt, d - 1);
    else if (u->t && u->t->maxdist() + 1 == d)
        walk(u->t, d - 1);
    else if (u->rt && u->rt->maxdist() + 1 == d)
        walk(u->rt, d - 1);
    else if (u->lans < u->rans) {
        for (v = u->l; v; v = v->l, d--) {
            printf("%ld ", INDEX(v));
        }

        for (v = u->r; v != u->rmax; v = v->r, d--) {
            printf("%ld ", INDEX(v));
        }

        walk(v, d - 1);
    } else {
        for (v = u->r; v; v = v->r, d--) {
            printf("%ld ", INDEX(v));
        }

        for (v = u->l; v != u->lmax; v = v->l, d--) {
            printf("%ld ", INDEX(v));
        }

        walk(v, d - 1);
    }
}

static NetworkFlow *net;

void construct() {
    net = new NetworkFlow(n + 1, n + 2);

    for (int i = 1; i <= n; i++) {
        net->link(n + 1, i, 0, INFTY);
        net->link(i, n + 2, 0, INFTY);
    }  // for

    SORT_REF(TUPLE_CMP(y, x, <, <));

    for (int head = 1; head <= n; head++) {
        int tail = head;
        while (tail < n && ptr[tail + 1]->y == ptr[head]->y) {
            tail++;
        }  // while

        unordered_set<int> q;
        for (int i = head; i <= tail; i++) {
            Point *cur = ptr[i];

            if ((cur->entrance && cur->maxdist() == cur->dist) ||
                q.count(cur->dist + cur->id - 1))
                cur->exit = true;
            if (cur->entrance && cur->rans == cur->maxdist())
                q.insert(cur->rans);
        }  // for

        q.clear();
        for (int i = tail; i >= head; i--) {
            Point *cur = ptr[i];

            if ((cur->entrance && cur->maxdist() == cur->dist) ||
                q.count(cur->dist + tail - head + 1 - cur->id))
                cur->exit = true;
            if (cur->entrance && cur->lans == cur->maxdist())
                q.insert(cur->lans);
        }  // for

        for (int i = head; i <= tail; i++) {
            Point *cur = ptr[i];

            if (cur->exit) {
                Point *nxt[] = {cur->lt, cur->t, cur->rt};

                for (auto v : nxt) {
                    if (v && v->maxdist() + 1 == cur->dist) {
                        v->entrance = true;
                        net->link(INDEX(cur), INDEX(v), 1, INFTY);
                    }
                }  // foreach in nxt
            }
        }  // for

        head = tail;
    }  // for
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    dp();

    printf("%d\n", root->dist - 1);

    walk(root, root->dist);

    root->entrance = true;
    construct();

    printf("\n%d\n", net->solve());

    // for (int i = 1; i <= n; i++) {
    //     fprintf(stderr,
    //             "%d: (%3d, %3d) / %d: l = %ld, lt = %ld, t = %ld, rt = %ld, r
    //             "
    //             "= %ld, "
    //             "lmax = %ld, rmax = %ld, dist = %d\n",
    //             i, point[i].x, point[i].y, point[i].id,
    //             max(0L, point[i].l - point), max(0L, point[i].lt - point),
    //             max(0L, point[i].t - point), max(0L, point[i].rt - point),
    //             max(0L, point[i].r - point), max(0L, point[i].lmax - point),
    //             max(0L, point[i].rmax - point), point[i].dist);
    // }  // for

    return 0;
}
