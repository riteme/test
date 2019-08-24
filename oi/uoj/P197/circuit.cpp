#define NDEBUG

#include <cstdio>
#include <cstring>

#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 100000

#ifndef NDEBUG
#define DEBUG(str, ...) fprintf(stderr, str, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

typedef long long i64;

enum NodeType {
    EDGE, SERIES, PARALLEL
};

struct Edge;
struct Node {
    Node(NodeType t, Edge *e = NULL)
        : type(t), head(NULL), tail(NULL), nxt(NULL), edge(e) {}

    NodeType type;
    Node *head, *tail, *nxt;
    Edge *edge;
};

struct Edge {
    Edge(int _u, int _v, bool init = false) : u(_u), v(_v), node(NULL) {
        if (init) node = new Node(EDGE, this);
    }

    int u, v;
    Node *node;

    int ep(int x) {
        return u == x ? v : u;
    }
};

static int n, m, top;
static int dfn[NMAX + 10], low[NMAX + 10], now;
static int seq[NMAX + 10], cnt;
static bool mark[NMAX + 10];
static i64 dp[NMAX + 10], ans, acc;
static vector<Edge *> G[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) dp[i] = 1;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        Edge *e = new Edge(u, v, true);
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

void eval(Node *x) {
    auto adde = [] (Edge *e) {
        ans += dp[e->u] * dp[e->v];
        if (e->u == top) acc += dp[e->v];
        else if (e->v == top) acc += dp[e->u];
    };
    if (x->type == EDGE) {
        adde(x->edge);
        return;
    }

    int ch = 0;
    for (Node *y = x->head; y; y = y->nxt, ch++) {
        if (x->type == PARALLEL && y->type == EDGE) adde(y->edge);
        else if (y->type != EDGE) eval(y);
    }

    if (x->type == PARALLEL) {
        ans -= dp[x->edge->u] * dp[x->edge->v] * (ch - 1);
        if (x->edge->u == top) acc -= dp[x->edge->v] * (ch - 1);
        else if (x->edge->v == top) acc -= dp[x->edge->u] * (ch - 1);
    } else {
        i64 sum = 0;
        auto add = [&sum] (int u) {
            if (!mark[u]) {
                mark[u] = true;
                ans += dp[u] * sum;
                sum += dp[u];
            }
        };
        for (Node *y = x->head; y; y = y->nxt) {
            auto e = y->edge;
            add(e->u);
            add(e->v);
            if (y->type == PARALLEL) {
                ans -= dp[e->u] * dp[e->v];
                if (e->u == top) acc -= dp[e->v];
                else if (e->v == top) acc -= dp[e->u];
            }
        }
        if (mark[top]) acc += sum - dp[top];
        for (Node *y = x->head; y; y = y->nxt)
            mark[y->edge->u] = mark[y->edge->v] = false;
    }
}

Node *parse() {
    static unordered_map<int, Edge*> C[NMAX + 10];
    static bool used[NMAX + 10];
    for (int i = 0; i < cnt; i++) {
        C[seq[i]].clear();
        used[seq[i]] = false;
    }

    queue<int> q;
    for (int i = 0; i < cnt; i++) {
        int u = seq[i];
        for (auto e : G[u])
            if (mark[e->ep(u)]) C[u].insert({e->ep(u), e});
        if (C[u].size() == 2) {
            q.push(u);
            used[u] = true;
        }
    }

    int total = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (C[u].size() < 2) {
            used[u] = false;
            continue;
        }
        total++;
        Edge *e1 = C[u].begin()->second;
        Edge *e2 = next(C[u].begin())->second;
        int a = e1->ep(u), b = e2->ep(u);
        C[a].erase(u);
        C[b].erase(u);

        Edge *e = new Edge(a, b);
        Node *x = e->node = new Node(SERIES, e);
        if (e1->node->type == SERIES) {
            x->head = e1->node->head;
            x->tail = e1->node->tail;
        } else x->head = x->tail = e1->node;
        if (e2->node->type == SERIES) {
            x->tail->nxt = e2->node->head;
            x->tail = e2->node->tail;
        } else x->tail = x->tail->nxt = e2->node;
        if (C[a].count(b)) {
            Node *y = C[a][b]->node, *z = e->node = new Node(PARALLEL, e);
            z->head = y->type == PARALLEL ? y->head : y;
            if (y->type == PARALLEL) y->tail->nxt = x;
            else y->nxt = x;
            z->tail = x;
        }

        C[a][b] = C[b][a] = e;
        if (!used[a] && C[a].size() == 2) {
            q.push(a);
            used[a] = true;
        }
        if (!used[b] && C[b].size() == 2) {
            q.push(b);
            used[b] = true;
        }
    }

    if (total == cnt - 2)
        for (int i = 0; i < cnt; i++) if (!used[seq[i]])
            return C[seq[i]].begin()->second->node;
    return NULL;
}

#ifndef NDEBUG
static size_t pos;
static char stk[1024];

inline void push(char c) {
    stk[pos++] = c;
}

inline void pop() {
    stk[--pos] = 0;
}

inline auto typestr(char type) -> const char * {
    if (type == SERIES) return "SERIES";
    else if (type == EDGE) return "EDGE";
    return "PARALLEL";
}

void print(Node *x, bool last = false) {
    fprintf(stderr, "%s$%s: %d-%d\n", stk, typestr(x->type), x->edge->u, x->edge->v);
    if (last) {
        pop();
        pop();
        push(' ');
        push(' ');
    } else {
        pop();
        pop();
        push('|');
        push(' ');
    }
    for (Node *y = x->head; y; y = y->nxt) {
        push('+');
        push('-');
        print(y, y == x->tail);
        pop();
        pop();
    }
}
#else
inline void print(...) {}
#endif

void bcc(int x, int fa = 0) {
    static stack<int> stk;
    dfn[x] = low[x] = ++now;

    bool ch = false;
    for (auto e : G[x]) {
        int v = e->ep(x);
        if (v == fa) continue;
        if (dfn[v]) {
            low[x] = min(low[x], dfn[v]);
            continue;
        }
        ch = true;
        stk.push(x);
        bcc(v, x);
        low[x] = min(low[x], low[v]);
        if (low[v] < dfn[x]) continue;
        ch = false;
        if (low[v] > dfn[x]) {
            DEBUG("cut edge: %d -- %d\n", x, v);
            ans += dp[x] * dp[v];
            dp[x] += dp[v];
            stk.pop();
            stk.pop();
            DEBUG("dp[%d] = %lld\n", x, dp[x]);
            DEBUG("ans = %lld\n", ans);
            continue;
        }
        DEBUG("cut vertex: %d\n", x);
        int u;
        cnt = 0;
        do {
            u = stk.top();
            stk.pop();
            if (!mark[u]) seq[cnt++] = u;
            mark[u] = true;
            DEBUG("%d, ", u);
        } while (u != x);
        DEBUG("\ncnt = %d\n", cnt);
        Node *tr = parse();
        for (int i = 0; i < cnt; i++) mark[seq[i]] = false;
        acc = 0;
        top = x;
        if (tr) {
            print(tr);
            if (tr->head && tr->head->nxt == tr->tail) {  // Cycle graph
                i64 sum = 0;
                for (int i = 0; i < cnt; i++) {
                    int u = seq[i];
                    ans += sum * dp[u];
                    sum += dp[u];
                }
                acc = sum - dp[x];
            } else eval(tr);
        }
        dp[x] += acc;
        DEBUG("dp[%d] = %lld\n", x, dp[x]);
        DEBUG("ans = %lld\n", ans);
    }
    if (!ch) stk.push(x);
}

int main() {
    initialize();
    for (int u = 1; u <= n; u++) {
        if (!dfn[u]) {
            DEBUG("%s", "--- NEW ---\n");
            bcc(u);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
