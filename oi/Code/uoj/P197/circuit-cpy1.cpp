//#define NO_PRINT_TREE

#include <cassert>
#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 1000

#define SERIES 1
#define PARALLEL 2
#define EDGE 3

struct Node {
    Node(char _type, struct Edge *e = NULL)
        : type(_type), head(NULL), tail(NULL), nxt(NULL), edge(e) {}

    char type;
    Node *head, *tail, *nxt;
    struct Edge *edge;
};

struct Edge {
    Edge(int _u, int _v, bool leaf = false) : u(_u), v(_v), node(NULL) {
        if (leaf) node = new Node(EDGE, this);
    }

    int u, v;
    Node *node;

    int rev(int x) const {
        return u == x ? v : u;
    }
};

static int n, m;
static unordered_map<int, Edge*> G[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        Edge *e = new Edge(u, v, true);
        G[u].insert({v, e});
        G[v].insert({u, e});
    }
}

Node *parse() {
    static bool mark[NMAX + 10];
    queue<int> q;
    for (int u = 1; u <= n; u++) if (G[u].size() == 2) {
        q.push(u);
        mark[u] = true;
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (G[u].size() < 2) {
            mark[u] = false;
            continue;
        }
        cnt++;
        Edge *e1 = G[u].begin()->second;
        Edge *e2 = next(G[u].begin())->second;
        int a = e1->rev(u), b = e2->rev(u);
        G[a].erase(u);
        G[b].erase(u);

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
        if (G[a].count(b)) {
            Node *y = G[a][b]->node, *z = e->node = new Node(PARALLEL, e);
            z->head = y->type == PARALLEL ? y->head : y;
            if (y->type == PARALLEL) y->tail->nxt = x;
            else y->nxt = x;
            z->tail = x;
        }
        G[a][b] = G[b][a] = e;

        if (!mark[a] && G[a].size() == 2) {
            q.push(a);
            mark[a] = true;
        }
        if (!mark[b] && G[b].size() == 2) {
            q.push(b);
            mark[b] = true;
        }
    }

    //printf("cnt = %d\n", cnt);
    if (cnt == n - 2)
        for (int i = 1; i <= n; i++) if (!mark[i])
            return G[i].begin()->second->node;
    return NULL;
}

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
    printf("%s$%s: %d-%d\n", stk, typestr(x->type), x->edge->u, x->edge->v);
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

static bool ans[NMAX + 10][NMAX + 10];

void eval(Node *x) {
    static int seq[NMAX * 3 + 10];
    if (x->type == EDGE) ans[x->edge->u][x->edge->v] = true;
    else if (x->type == SERIES) {
        int cnt = 0;
        for (Node *y = x->head; y; y = y->nxt) {
            seq[cnt++] = y->edge->u;
            seq[cnt++] = y->edge->v;
        }
        sort(seq, seq + cnt);
        cnt = unique(seq, seq + cnt) - seq;
        for (int i = 0; i < cnt; i++) for (int j = 0; j < cnt; j++)
            ans[seq[i]][seq[j]] = true;
    }
    for (Node *y = x->head; y; y = y->nxt) eval(y);
}

int main() {
    initialize();
    Node *tr = parse();
    assert(tr != NULL);
    if (tr->head && tr->head->nxt == tr->tail)  // Cycle graph
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) ans[i][j] = true;
    else eval(tr);
    int ret = 0;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        if (ans[i][j] || ans[j][i]) {
            ret++;
            printf("%d -- %d\n", i,  j);
        }
    }
#ifndef NO_PRINT_TREE
    print(tr);
#endif
    printf("%d\n", ret);
    return 0;
}
