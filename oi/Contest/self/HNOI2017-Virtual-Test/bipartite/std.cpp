// #define USE_FILE_IO
// #define NDEBUG

#define NAME "bipartite"

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 150000
#define QMAX 750000

class UnionFind {
 public:
    UnionFind() {
        memset(set, 0, sizeof(set));
        for (int i = 1; i <= NMAX; i++) {
            size[i] = 1;
        }
    }

    int find(int u) {
        return set[u] ? find(set[u]) : u;
    }

    void link(int u, int v) {
        assert(!set[u]);
        assert(!set[v]);

        if (size[u] < size[v])
            swap(u, v);

        set[v] = u;
        size[u] += size[v];
    }

    void remove(int u, int v) {
        if (set[u] != v)
            swap(u, v);

        assert(set[u] == v);

        while (v) {
            size[v] -= size[u];
            v = set[v];
        }
        set[u] = 0;
    }

 private:
    int set[NMAX + 10];
    int size[NMAX + 10];
};

class Solver {
 public:
    Solver() : answer(true), cnt(0) {
        memset(match, 0, sizeof(match));
    }

    void add(int u, int v) {
        if (!answer) {
            cnt++;
            return;
        }

        int idu = uf.find(u);
        int idv = uf.find(v);

        if (idu == idv) {
            answer = false;
            cnt = 1;
            return;
        }

        op.push(NULL);

        if (match[idu] == idv)
            return;

        if (match[idv]) {
            uf.link(idu, match[idv]);
            op.push(new RemoveCommand(this, idu, match[idv]));
        }

        if (match[idu]) {
            uf.link(match[idu], idv);
            op.push(new RemoveCommand(this, match[idu], idv));
        }

        int nidu = uf.find(idu);
        int nidv = uf.find(idv);
        op.push(new ModifyCommand(this, nidu, match[nidu]));
        op.push(new ModifyCommand(this, nidv, match[nidv]));
        match[nidu] = nidv;
        match[nidv] = nidu;
    }

    void ret() {
        if (cnt > 1)
            cnt--;
        else if (cnt == 1) {
            answer = true;
            cnt = 0;
        } else {
            while (true) {
                Command *command = op.top();
                op.pop();

                if (command == NULL)
                    break;

                command->execute();
            }
        }
    }

    bool answer;

 private:
    struct Command {
        virtual void execute() = 0;
    };

    struct RemoveCommand : public Command {
        RemoveCommand(Solver *_target, int _u, int _v)
            : target(_target), u(_u), v(_v) {}

        Solver *target;
        int u, v;

        virtual void execute() {
            target->uf.remove(u, v);
        }
    };

    struct ModifyCommand : public Command {
        ModifyCommand(Solver *_target, int _u, int _v)
            : target(_target), u(_u), v(_v) {}

        Solver *target;
        int u, v;

        virtual void execute() {
            target->match[u] = v;
        }
    };

    stack<Command *> op;
    UnionFind uf;
    int match[NMAX + 10];
    int cnt;
};

struct Edge {
    Edge(int _u, int _v)
        : u(_u), v(_v), translated(false) {}

    int u, v;
    bool translated;
};

enum CommandType {
    ADD, DEL
};

static int n, q, s, xcnt, ycnt;
static CommandType type[QMAX + 10];
static int u[QMAX + 10];
static int v[QMAX + 10];
static int t[QMAX + 10];
static bool answer[QMAX + 10];

class SegmentTree {
 public:
    SegmentTree(int n) {
        root = _build(1, n);
    }

    void cover(int left, int right, Edge *e) {
        _cover(root, left, right, e);
    }

    void solve() {
        solver = new Solver;
        _solve(root);
    }

 private:
    struct Node {
        Node(int l, int r)
            : left(l), right(r), leftchild(NULL), rightchild(NULL) {}

        int left;
        int right;
        vector<Edge *> edges;
        Node *leftchild;
        Node *rightchild;
    };

    Node *root;
    Solver *solver;

    Node *_build(int left, int right) {
        Node *x = new Node(left, right);

        if (left < right) {
            int mid = (left + right) / 2;
            x->leftchild = _build(left, mid);
            x->rightchild = _build(mid + 1, right);
        }

        return x;
    }

    void _cover(Node *x, int left, int right, Edge *e) {
        if (left <= x->left && x->right <= right)
            x->edges.push_back(e);
        else {
            int mid = (x->left + x->right) / 2;

            if (left <= mid)
                _cover(x->leftchild, left, right, e);
            if (right > mid)
                _cover(x->rightchild, left, right, e);
        }
    }

    void _solve(Node *x) {
        for (size_t i = 0; i < x->edges.size(); i++) {
            Edge *e = x->edges[i];

            if (s && !e->translated) {
                e->u ^= xcnt | ycnt;
                e->v ^= xcnt | ycnt;
                e->translated = true;
            }

            solver->add(e->u, e->v);
        }

        if (x->left == x->right) {
            answer[x->left] = solver->answer;

            if (solver->answer)
                xcnt++;
            else
                ycnt++;
        } else {
            _solve(x->leftchild);
            _solve(x->rightchild);
        }

        for (size_t i = 0; i < x->edges.size(); i++) {
            solver->ret();
        }
    }
};

static SegmentTree *tree;

void initialize() {
    scanf("%d%d%d", &n, &q, &s);

    char command[4];
    for (int i = 1; i <= q; i++) {
        scanf("%s", command);

        switch (command[0]) {
            case 'A': {
                type[i] = ADD;
                scanf("%d%d", u + i, v + i);
            } break;

            case 'D': {
                type[i] = DEL;
                scanf("%d", u + i);
                t[u[i]] = i - 1;
            } break;
        }
    }

    tree = new SegmentTree(q);
    for (int i = 1; i <= q; i++) {
        if (type[i] == ADD) {
            if (!t[i])
                t[i] = q;

            tree->cover(i, t[i], new Edge(u[i], v[i]));
        }
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();
    tree->solve();

    for (int i = 1; i <= q; i++) {
        puts(answer[i] ? "YES" : "NO");
    }

    return 0;
}
