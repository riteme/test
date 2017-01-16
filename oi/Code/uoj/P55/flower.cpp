#define NDEBUG
// #define ONLINE

#include <cassert>

#include <cstdio>
#include <cctype>
#include <climits>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 65536
static size_t ipos = INPUT_BUFFERSIZE;
static char ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (ipos == INPUT_BUFFERSIZE) {
        ipos = 0;
        fread(ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return ibuffer[ipos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c)) {
        c = _getchar();
    }

    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define OUTPUT_BUFFERSIZE 2000000
static size_t opos = 0;
static char obuffer[OUTPUT_BUFFERSIZE];

inline void put(long long x) {
    opos += sprintf(obuffer + opos, "%lld\n", x);
}

inline void flush() {
    setbuf(stdout, nullptr);
    fwrite(obuffer, 1, opos, stdout);
}

#define NMAX 100000
#define LOGN 16
#define ALPHAA 88
#define ALPHAB 100

typedef long long int64;

static int testid;
static int n;

static class MyRandom {
 public:
    int p = 1000000007;
    static constexpr int t = 1103515245;
    static constexpr int q = 23333;

    int operator()() {
        p = p * t + q;
        return p;
    }
} randint;

class Treap {
 public:
    friend class Solver;

    Treap() : _root(nullptr) {}
    ~Treap() {
        delete _root;
    }

    void insert(int key) {
        _root = _insert(_root, key);
    }

    int count(int key) {
        return _count(_root, key);
    }

 private:
    struct Node {
        static vector<Node *> bin;   

        void *operator new(size_t) {
            Node *node;

            if (!bin.empty()) {
                node = bin.back();
                bin.pop_back();
            } else {
                node = static_cast<Node *>(malloc(sizeof(Node)));
                node->weight = randint();
            }

            node->cnt = 1;
            node->size = 1;
            node->left = nullptr;
            node->right = nullptr;

            return node;
        }

        void operator delete(void *ptr) {
            bin.push_back(static_cast<Node *>(ptr));
        }
    
        Node() {}
        ~Node() {
            delete left;
            delete right;
        }

        int key;
        int cnt;
        int size;
        int weight;
        Node *left;
        Node *right;

        Node *left_rotate() {
            auto y = left;
            left = y->right;
            y->right = this;
            y->size = size;
            size -= y->cnt +
                    (y->left ? y->left->size : 0);

            return y;
        }

        Node *right_rotate() {
            auto y = right;
            right = y->left;
            y->left = this;
            y->size = size;
            size -= y->cnt +
                    (y->right ? y->right->size : 0);

            return y;
        }
    };

    Node *_root;

    Node *_insert(Node *x, int key) {
        if (!x) {
            x = new Node;
            x->key = key;
            return x;
        }

        x->size++;
        if (key < x->key) {
            x->left = _insert(x->left, key);

            if (x->left->weight < x->weight)
                return x->left_rotate();
        } else if (key > x->key) {
            x->right = _insert(x->right, key);

            if (x->right->weight < x->weight)
                return x->right_rotate();
        } else
            x->cnt++;

        return x;
    }

    int _count(Node *x, int key) {
        int answer = 0;
        while (x) {
            if (key < x->key) {
                x = x->left;
            } else if (key > x->key) {
                answer += (x->left ? x->left->size : 0) + x->cnt;
                x = x->right;
            } else {
                answer += (x->left ? x->left->size : 0) + x->cnt;
                break;
            }
        }

        return answer;
    }
};

vector<Treap::Node *> Treap::Node::bin;   

class Solver {
 public:
    Solver() : root(nullptr) {
        memset(length, 0, sizeof(length));
        memset(tdep, 0, sizeof(tdep));
        memset(f, 0, sizeof(f));
        memset(depth, 0, sizeof(depth));
        memset(head, 0, sizeof(head));
    }

    ~Solver() {
        delete root;
    }

    void add(int u, int p, int dis, int radius) {
        get_stack(sub[p]);
        
        while (stkpos--) {
            Node *x = stk[stkpos];
            
            if (x->size * ALPHAB > x->father->size * ALPHAA) {
                auto pos = x->father;
                auto fa = x->father->father;
                int dep = depth[pos->center];

                initialize(pos->entrance, dep);
                *pos = *solve(pos->entrance, dep, dep, pos);

                sub[pos->center] = pos;
                pos->father = fa;

                if (!fa)
                    root = pos;

                break;
            }
        }

        rad[u] = radius;
        Node *node = new Node(u);
        node->tree.insert(-rad[u]);
        node->dist.insert(-rad[u]);
        sub[u] = node;

        if (p) {
            add_edge(p, u, dis);

            length[u] = length[p] + dis;
            tdep[u] = tdep[p] + 1;
            f[0][u] = p;
            for (int j = 1; j <= LOGN; j++) {
                f[j][u] = f[j - 1][f[j - 1][u]];
            }

            depth[u] = depth[p] + 1;
            node->father = sub[p];
        } else {
            root = node;
            depth[u] = 0;
        }

        get_stack(sub[u]);

        for (int i = stkpos - 1; i >= 0; i--) {
            Node *cur = stk[i];
            cur->father->answer -= cur->answer;
        }

        for (int i = 0; i < stkpos; i++) {
            Node *cur = stk[i];
            Node *top = cur->father;

            int delta = evaluate_distance(u, top->center);
            int len = evaluate_distance(cur->entrance, top->center);
            int dis = evaluate_distance(u, top->entrance);
            top->size++;
            top->tree.insert(delta - rad[u]); 
            top->dist.insert(dis - rad[u]);

            top->answer += top->tree.count(rad[u] - delta) -
                           cur->dist.count(rad[u] - delta - len) +
                           cur->answer;
        }

    }

    int64 query() {
        assert(root);

        return root->answer;
    }

 private:
    struct Node {
        Node(int u)
            : answer(0), size(1),
              center(u), entrance(u),
              father(nullptr) {}
        
        int64 answer;
        int size;
        int center;
        int entrance;
        Treap tree;
        Treap dist;  // to father
        Node *father;
    };

    struct Edge {
        int to, w;
        int next;
    };

    int stkpos = 0;
    Node *stk[NMAX + 10];

    int mcnt = 0;
    Edge edges[NMAX * 2 + 10];
    int head[NMAX + 10];
    int rad[NMAX + 10];
    int length[NMAX + 10];
    int tdep[NMAX + 10];
    int f[LOGN + 1][NMAX + 10];

    void add_edge(int u, int v, int w) {
        mcnt++;
        edges[mcnt].to = v;
        edges[mcnt].w = w;
        edges[mcnt].next = head[u];
        head[u] = mcnt;
        mcnt++;
        edges[mcnt].to = u;
        edges[mcnt].w = w;
        edges[mcnt].next = head[v];
        head[v] = mcnt;
    }

    int evaluate_lca(int u, int v) {
        if (tdep[u] < tdep[v])
            swap(u, v);

        int delta = tdep[u] - tdep[v];
        for (int i = 0; i <= LOGN; i++) {
            if ((delta >> i) & 1)
                u = f[i][u];
        }

        if (u == v)
            return u;

        for (int i = LOGN; i >= 0; i--) {
            if (f[i][u] != f[i][v]) {
                u = f[i][u];
                v = f[i][v];
            }
        }

        return f[0][u];
    }

    int evaluate_distance(int u, int v) {
        return length[u] + length[v] -
               (length[evaluate_lca(u, v)] << 1);
    }

    Node *root;
    Node *sub[NMAX + 10];
    int depth[NMAX + 10];
    int dist[NMAX + 10];
    int size[NMAX + 10];
    int mind = 0;

    void get_stack(Node *cur) {
        if (!cur)
            return;

        stkpos = 0;
        while (cur->father) {
            stk[stkpos++] = cur;
            cur = cur->father;
        }
    }

    void initialize(int x, int mindep, int father = 0) {
        depth[x] = INT_MAX;
        
        if (sub[x]) {
            delete sub[x]->tree._root;
            delete sub[x]->dist._root;
        }

        for (int i = head[x]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (v == father || depth[v] < mindep)
                continue;

            initialize(v, mindep, x);
        }
    }

    void dfs(int x, Node *node, int father = 0) {
        size[x] = 1;
        node->dist.insert(dist[x] - rad[x]);

        for (int i = head[x]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (v == father || depth[v] < mind)
                continue;

            dist[v] = dist[x] + e.w;
            dfs(v, node, x);
            size[x] += size[v];
        }
    }

    int select_center(int x, int maxsize, int father = 0) {
        for (int i = head[x]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (v == father || depth[v] < mind)
                continue;

            if (size[v] > maxsize)
                return select_center(v, maxsize, x);
        }

        return x;
    }

    void evaluate(int x, Node *node, int father) {
        node->answer += node->tree.count(rad[x] - dist[x]);

        for (int i = head[x]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (v == father || depth[v] < mind)
                continue;

            dist[v] = dist[x] + e.w;
            evaluate(v, node, x);
        }
    }

    void push(int x, Node *node, int father) {
        node->tree.insert(dist[x] - rad[x]);

        for (int i = head[x]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (v == father || depth[v] < mind)
                continue;

            push(v, node, x);
        }
    }

    Node *solve(int x, int dep, int mindep, Node *father = nullptr) {
        Node *node = new Node(x);
        node->entrance = x;

        mind = mindep;
        dist[x] = 0;
        dfs(x, node);
        int p = select_center(x, size[x] >> 1);
        node->center = p;
        sub[p] = node;
        depth[p] = dep;

        node->tree.insert(-rad[p]);
        for (int i = head[p]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (depth[v] < mindep)
                continue;

            dist[v] = e.w;
            evaluate(v, node, p);
            push(v, node, p);
        }

        for (int i = head[p]; i; i = edges[i].next) {
            Edge &e = edges[i];
            int v = e.to;

            if (depth[v] < mindep)
                continue;

            auto c = solve(v, dep + 1, dep + 1); 

            if (father)
                c->father = father;
            else
                c->father = node;
            node->size += c->size;
            node->answer += c->answer;
        }

        return node;
    }
};

static Solver solver;

int main() {
    // freopen("flower.in", "r", stdin);
    // freopen("flower.out", "w", stdout);
    testid = readint();
    n = readint();

    int64 lastans = 0;
    for (int i = 1; i <= n; i++) {
        int f, c, r;
        f = readint();
        c = readint();
        r = readint();

        #ifdef ONLINE
        lastans %= 1000000000;
        f ^= lastans;
        #endif

        solver.add(i, f, c, r);
        lastans = solver.query();
        put(lastans);
    }

    flush();

    return 0;
}
