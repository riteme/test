/**
 * 整体二分
 * 二分答案后只用判定断点是否经过了所有的长路经
 * 动态路径交使用线段树分治的思想
 */

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define NMAX 200000

enum CommandType : int {
    ADD = 0,
    END = 1,
    QUERY = 2,
};  // enum CommandType

struct AddCommand {
    int id;
    int u, v, w;
};  // struct AddCommand

struct EndCommand {
    int id;
    int t;
    AddCommand *ref;
};  // struct EndCommand

struct QueryCommand {
    int x;
    int t;
    int answer;
};  // struct QueryCommand

struct Command {
    int type;

    union {
        AddCommand *add;
        EndCommand *end;
        QueryCommand *query;
    } instance;
};  // struct Command

static int n, m;
static int _timestamp;
static vector<int> G[NMAX + 10];
static vector<int> children[NMAX + 10];
static int father[NMAX + 10];
static int size[NMAX + 10];
static int depth[NMAX + 10];
static int top[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];

static int vcnt;
static int values[NMAX + 10];

static Command commands[NMAX + 10];

static bool marked[NMAX + 10];

static void build(int x) {
    in[x] = ++_timestamp;
    marked[x] = true;

    size[x] = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            children[x].push_back(v);
            father[v] = x;
            depth[v] = depth[x] + 1;

            build(v);

            size[x] += size[v];
        }
    }  // for

    out[x] = _timestamp;
}

static void decompose(int x) {
    int next = 0;
    for (size_t i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (size[v] > size[next])
            next = v;
    }  // for

    if (!next)
        return;

    top[next] = top[x];
    decompose(next);

    for (size_t i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        if (v != next) {
            top[v] = v;
            decompose(v);
        }
    }  // for
}

inline int evaluate_lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = father[top[u]];
        else
            v = father[top[v]];
    }  // while

    if (depth[u] < depth[v])
        return u;
    else
        return v;
}

// O(1)
inline bool is_father(int x, int p) {
    return in[p] <= in[x] && in[x] <= out[p];
}

// O(log n) (LCA)
inline bool is_on_path(int x, int u, int v) {
    if (u == -1 && v == -1)
        return true;
    if (u == 0 && v == 0)
        return false;

    int lca = evaluate_lca(u, v);

    return is_father(x, lca) && (is_father(u, x) || is_father(v, x));
}

// O(1)
inline void two_sort(int x, int &first, int &second) {
    if (depth[first] < depth[x]) {
        second = first;
        first = x;
    } else if (depth[second] < depth[x])
        second = x;
}

// (4) O(log n) (LCA)
inline void path_intersect(int u1, int v1, int u2, int v2, int &ou, int &ov) {
    // assert that two paths has intersection.

    int nu = 0, nv = 0;
    if (is_on_path(evaluate_lca(u1, v1), u2, v2) ||
        is_on_path(evaluate_lca(u2, v2), u1, v1)) {
        two_sort(evaluate_lca(u1, u2), nu, nv);
        two_sort(evaluate_lca(u1, v2), nu, nv);
        two_sort(evaluate_lca(v1, u2), nu, nv);
        two_sort(evaluate_lca(v1, v2), nu, nv);
    }

    ou = nu;
    ov = nv;
}

struct Node {
    Node(int _left, int _right)
            : left(_left)
            , right(_right)
            , u(-1)
            , v(-1)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left, right;
    int u, v;
    Node *leftchild, *rightchild;
};  // struct Node

static Node *create(int left, int right) {
    Node *x = new Node(left, right);

    if (left == right)
        return x;

    int mid = (left + right) / 2;
    x->leftchild = create(left, mid);
    x->rightchild = create(mid + 1, right);
    return x;
}

static void gc(Node *x) {
    if (!x)
        return;

    gc(x->leftchild);
    gc(x->rightchild);
    delete x;
}

static void insert(Node *x, int u, int v, int s, int t) {
    if (!x)
        return;

    if (s <= x->left && x->right <= t) {
        if (x->u == -1) {
            x->u = u;
            x->v = v;
        } else
            path_intersect(x->u, x->v, u, v, x->u, x->v);
    } else {
        int mid = (x->left + x->right) / 2;

        if (t <= mid)
            insert(x->leftchild, u, v, s, t);
        else if (s > mid)
            insert(x->rightchild, u, v, s, t);
        else {
            insert(x->leftchild, u, v, s, t);
            insert(x->rightchild, u, v, s, t);
        }
    }
}

static bool query(Node *x, int t, int p) {
    if (!x)
        return true;

    int mid = (x->left + x->right) / 2;
    if (t <= mid)
        return is_on_path(p, x->u, x->v) && query(x->leftchild, t, p);
    else
        return is_on_path(p, x->u, x->v) && query(x->rightchild, t, p);
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    for (int i = 1; i <= m; i++) {
        int type;
        scanf("%d", &type);

        commands[i].type = type;
        switch (type) {
            case ADD: {
                int a, b, v;
                scanf("%d%d%d", &a, &b, &v);

                commands[i].instance.add = new AddCommand;
                commands[i].instance.add->u = a;
                commands[i].instance.add->v = b;
                commands[i].instance.add->w = v;
                commands[i].instance.add->id = i;

                values[++vcnt] = v;
            } break;

            case END: {
                int t;
                scanf("%d", &t);

                commands[i].instance.end = new EndCommand;
                commands[i].instance.end->t = t;
                commands[i].instance.end->id = commands[t].instance.add->id;
                commands[i].instance.end->ref = commands[t].instance.add;
            } break;

            case QUERY: {
                int x;
                scanf("%d", &x);

                commands[i].instance.query = new QueryCommand;
                commands[i].instance.query->x = x;
            } break;
        }  // switch to type
    }      // for

    depth[1] = 1;
    build(1);

    top[1] = 1;
    decompose(1);

    sort(values + 1, values + vcnt + 1);
    vcnt = unique(values + 1, values + vcnt + 1) - values - 1;
}

static int timestamp;
static int intime[NMAX + 10];
static int outtime[NMAX + 10];
static Command *queue[NMAX + 10];
static Command *lqueue[NMAX + 10];
static Command *rqueue[NMAX + 10];

static void solve(int left, int right, int head, int tail) {
    if (tail < head)
        return;

    if (left == right) {
        for (int i = head; i <= tail; i++)
            if (queue[i]->type == QUERY)
                queue[i]->instance.query->answer = values[left];

        return;
    }

    int mid = (left + right) / 2;
    int midv = values[mid];
    timestamp = 0;
    for (int i = head; i <= tail; i++) {
        Command *q = queue[i];

        switch (q->type) {
            case ADD: {
                intime[q->instance.add->id] = timestamp;
                outtime[q->instance.add->id] = -1;
            } break;

            case END: {
                outtime[q->instance.end->id] = timestamp;
            } break;

            case QUERY: {
                timestamp++;
                q->instance.query->t = timestamp;
            } break;
        }  // switch to q->type
    }      // for

    for (int i = head; i <= tail; i++) {
        Command *q = queue[i];

        if (q->type == ADD && outtime[q->instance.add->id] < 0)
            outtime[q->instance.add->id] = timestamp;
    }

    Node *tree = create(0, timestamp);
    int lpos = 0;
    int rpos = 0;
    for (int i = head; i <= tail; i++) {
        Command *q = queue[i];

        switch (q->type) {
            case ADD: {
                if (q->instance.add->w > midv) {
                    insert(tree, q->instance.add->u, q->instance.add->v,
                           intime[q->instance.add->id],
                           outtime[q->instance.add->id]);
                    rqueue[++rpos] = q;
                } else
                    lqueue[++lpos] = q;
            } break;

            case END: {
                if (q->instance.end->ref->w > midv)
                    rqueue[++rpos] = q;
                else
                    lqueue[++lpos] = q;
            } break;

            case QUERY: {
                if (query(tree, q->instance.query->t, q->instance.query->x))
                    lqueue[++lpos] = q;
                else
                    rqueue[++rpos] = q;
            } break;
        }  // switch to q->type
    }      // for

    gc(tree);

    int pos = head;
    for (int i = 1; i <= lpos; i++)
        queue[pos++] = lqueue[i];
    for (int i = 1; i <= rpos; i++)
        queue[pos++] = rqueue[i];

    solve(left, mid, head, head + lpos - 1);
    solve(mid + 1, right, head + lpos, head + lpos + rpos - 1);
}

int main() {
    // freopen("network.in", "r", stdin);
    // freopen("network.out", "w", stdout);
    freopen("network_tenderRun.in", "r", stdin);
    freopen("network_tenderRun.out", "w", stdout);
    initialize();

    for (int i = 1; i <= m; i++)
        queue[i] = commands + i;

    values[0] = -1;
    solve(0, vcnt, 1, m);

    for (int i = 1; i <= m; i++) {
        Command &q = commands[i];

        if (q.type == QUERY)
            printf("%d\n", q.instance.query->answer);
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
