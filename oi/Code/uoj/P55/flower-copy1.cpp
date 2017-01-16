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

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
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

#define NMAX 100000
#define LOGN 17
#define ALPHAA 81
#define ALPHAB 100

typedef long long int64;

static int testid;
static int n;

struct Edge {
    Edge(int v, int _w)
        : to(v), w(_w) {}

    int to, w;
};

typedef vector<Edge *> Graph[NMAX + 10];

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
        Node() {}
        Node(int _key)
            : key(_key), cnt(1), size(1), weight(randint()),
              left(nullptr), right(nullptr) {}
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
        if (!x)
            return new Node(key);

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
        // if (!x)
        //     return 0;
        // if (key < x->key)
        //     return _count(x->left, key);
        // if (key > x->key)
        //     return _count(x->right, key) +
        //            (x->left ? x->left->size : 0) + x->cnt;
        // return (x->left ? x->left->size : 0) + x->cnt;
        
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

class Solver {
 public:
    Solver() : root(nullptr) {
        memset(length, 0, sizeof(length));
        memset(tdep, 0, sizeof(tdep));
        memset(f, 0, sizeof(f));
        memset(depth, 0, sizeof(depth));
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

                for (auto c : pos->children) {
                    delete c;
                }

                initialize(pos->entrance, dep);
                *pos = *solve(pos->entrance, dep, dep);

                sub[pos->center] = pos;
                pos->father = fa;
                for (auto c : pos->children) {
                    c->father = pos;
                }

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
            G[p].push_back(new Edge(u, dis));
            G[u].push_back(new Edge(p, dis));

            length[u] = length[p] + dis;
            tdep[u] = tdep[p] + 1;
            f[0][u] = p;
            for (int j = 1; j <= LOGN; j++) {
                f[j][u] = f[j - 1][f[j - 1][u]];
            }

            depth[u] = depth[p] + 1;
            node->father = sub[p];
            sub[p]->children.push_back(node);
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
        ~Node() {
            for (auto &c : children) {
                delete c;
            }
        }
        
        int64 answer;
        int size;
        int center;
        int entrance;
        Treap tree;
        Treap dist;  // to father
        Node *father;
        vector<Node *> children;
    };

    int stkpos = 0;
    Node *stk[NMAX + 10];

    Graph G;
    int rad[NMAX + 10];
    int length[NMAX + 10];
    int tdep[NMAX + 10];
    int f[LOGN + 1][NMAX + 10];

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

        for (auto e : G[x]) {
            int v = e->to;

            if (v == father || depth[v] < mindep)
                continue;

            initialize(v, mindep, x);
        }
    }

    void dfs(int x, Node *node, int father = 0) {
        size[x] = 1;
        node->dist.insert(dist[x] - rad[x]);

        for (auto e : G[x]) {
            int v = e->to;

            if (v == father || depth[v] < mind)
                continue;

            dist[v] = dist[x] + e->w;
            dfs(v, node, x);
            size[x] += size[v];
        }
    }

    int select_center(int x, int maxsize, int father = 0) {
        for (auto e : G[x]) {
            int v = e->to;

            if (v == father || depth[v] < mind)
                continue;

            if (size[v] > maxsize)
                return select_center(v, maxsize, x);
        }

        return x;
    }

    void evaluate(int x, Node *node, int father) {
        node->answer += node->tree.count(rad[x] - dist[x]);

        for (auto e : G[x]) {
            int v = e->to;

            if (v == father || depth[v] < mind)
                continue;

            dist[v] = dist[x] + e->w;
            evaluate(v, node, x);
        }
    }

    void push(int x, Node *node, int father) {
        node->tree.insert(dist[x] - rad[x]);

        for (auto e : G[x]) {
            int v = e->to;

            if (v == father || depth[v] < mind)
                continue;

            push(v, node, x);
        }
    }

    Node *solve(int x, int dep, int mindep) {
        Node *node = new Node(x);
        node->entrance = x;

        mind = mindep;
        dist[x] = 0;
        dfs(x, node);
        int p = select_center(x, size[x] >> 1);
        node->center = p;
        sub[p] = node;
        depth[p] = dep;

        for (auto e : G[p]) {
            int v = e->to;

            if (depth[v] < mindep)
                continue;

            dist[v] = e->w;
            evaluate(v, node, p);
            push(v, node, p);
        }
        node->answer += node->tree.count(rad[p]);
        node->tree.insert(-rad[p]);

        for (auto e : G[p]) {
            int v = e->to;

            if (depth[v] < mindep)
                continue;

            auto c = solve(v, dep + 1, dep + 1); 
            c->father = node;
            node->size += c->size;
            node->answer += c->answer;
            node->children.push_back(c);
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
        printf("%lld\n", lastans);
    }

    return 0;
}
