#define NDEBUG

#include <cassert>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define INFTY LLONG_MAX
#define EPSILON 0.00000001

template <typename T>
inline bool equ(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

#define NMAX 200000

typedef long long int64;
typedef long double float128;

struct Vector {
    Vector() : x(0.0), y(0.0) {}
    Vector(const float128 _x, const float128 _y)
        : x(_x), y(_y) {}

    float128 x, y;

    bool operator<(const Vector &b) const {
        return x < b.x;
    }

    Vector operator+(const Vector &b) const {
        return Vector(x + b.x, y + b.y);
    }

    Vector operator-(const Vector &b) const {
        return Vector(x - b.x, y - b.y);
    }

    float128 tangent() const {
        return y / x;
    }
};

class ConvexHull {
 public:
    ConvexHull() : _undoable(false) {}

    void set_undoable(bool undoable) {
        _undoable = undoable;
    }

    void push(const Vector &vec) {
        Operation *op;
        if (_undoable)
            op = new Operation;

        while (size() > 1 &&
               (vec - back()).tangent() <= (back() - second()).tangent()) {
            if (_undoable)
                op->push_back(back());

            _stk.pop_back();
        }

        if (_undoable)
            _op.push_back(op);

        _stk.push_back(vec);
    }

    void undo() {
        assert(_undoable);

        Operation *op = _op.back();
        _op.pop_back();

        _stk.pop_back();
        for (auto beg = op->rbegin(); beg != op->rend(); beg++) {
            _stk.push_back(*beg);
        }

        // delete op;
    }

    void clear() {
        assert(!_undoable);

        _stk.clear();
    }

    Vector minimize(const float128 slope) {
        assert(!empty());

        int left = 0, right = size() - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            float128 preslope = (_stk[mid + 1]  - _stk[mid]).tangent();

            if (slope >= preslope)
                left = mid;
            else
                right = mid;
        }

        if (left != right &&
            (_stk[right] - _stk[left]).tangent() <= slope)
            left = right;

        return _stk[left];
    }

    Vector &back() {
        return _stk.back();
    }

    Vector &second() {
        return _stk[size() - 2];
    }

    int size() const {
        return _stk.size();
    }

    bool empty() const {
        return _stk.empty();
    }

    Vector &operator[](const size_t pos) {
        return _stk[pos];
    }

 private:
    typedef vector<Vector> Operation;

    vector<Vector> _stk;
    bool _undoable;
    vector<Operation *> _op;
};

static class MyRandom {
 public:
    static constexpr int Seed = 577777777;

    MyRandom() {
        srand(Seed);
    }

    int operator()() const {
        return rand();
    }
} randint;

class Treap {
 public:
    Treap() : root(nullptr) {}

    struct Node {
        Node(const Vector &vec)
            : weight(randint()), key(vec),
              leftbound(vec.x), rightbound(vec.x),
              left(nullptr), right(nullptr) {
                  convex.push(vec);
            }

        int weight;
        Vector key;
        ConvexHull convex;
        float128 leftbound;
        float128 rightbound;
        Node *left;
        Node *right;

        void update_bound() {
            leftbound = key.x;
            rightbound = key.x;

            if (left)
                leftbound = min(leftbound, left->leftbound);
            if (right)
                rightbound = max(rightbound, right->rightbound);
        }

        void update() {
            convex.clear();
            rebuild(convex);
            update_bound();
        }

        Node *right_rotate() {
            Node *y = right;
            right = y->left;
            y->left = this;

            update();
            y->update();

            return y;
        }

     private:
        void rebuild(ConvexHull &con) {
            if (left)
                left->rebuild(con);

            con.push(key);

            if (right)
                right->rebuild(con);
        }
    };

    void push(const Vector &vec) {
        root = push(root, vec);
    }

    Vector minimize(float128 left, float128 right, float128 slope) {
        ConvexHull con;
        extract(root, left, right, slope, con);

        return con.minimize(slope);
    }

 private:
    Node *root;

    Node *push(Node *x, const Vector &vec) {
        if (!x)
            return new Node(vec);

        x->right = push(x->right, vec);

        if (x->right->weight < x->weight)
            return x->right_rotate();

        x->convex.push(vec);
        x->rightbound = max(x->key.x, x->right->rightbound);
        return x;
    }

    void extract(Node *x,
                 float128 left, float128 right, float128 slope,
                 ConvexHull &con) {
        if (!x)
            return;

        if (left <= x->leftbound && x->rightbound <= right) {
            con.push(x->convex.minimize(slope));
        } else {
            if (left < x->key.x)
                extract(x->left, left, right, slope, con);
            if (left <= x->key.x && x->key.x <= right)
                con.push(x->key);
            if (right > x->key.x)
                extract(x->right, left, right, slope, con);
        }
    }
};

static int n, _;
static int cnt;
static vector<int> G[NMAX + 10];
static int64 dist[NMAX + 10];
static int size[NMAX + 10];
static int father[NMAX + 10];
static int top[NMAX + 10];
static Treap tree[NMAX + 10];
static ConvexHull convex[NMAX + 10];
static int64 W[NMAX + 10];
static int64 P[NMAX + 10];
static int64 Q[NMAX + 10];
static int64 L[NMAX + 10];
static int64 f[NMAX + 10];

static void build_tree(int x) {
    size[x] = 1;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        dist[v] = dist[x] + W[v];
        build_tree(v);
        size[x] += size[v];
    }
}

static void decompose(int x) {
    int next = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (size[v] > size[next])
            next = v;
    }

    if (next) {
        top[next] = top[x];
        decompose(next);
    }

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v != next) {
            top[v] = v;
            decompose(v);
        }
    }
}

static void initialize() {
    scanf("%d%d", &n, &_);

    for (int i = 2; i <= n; i++) {
        scanf("%d%lld%lld%lld%lld", father + i, W + i, P + i, Q + i, L + i);

        G[father[i]].push_back(i);
    }

    build_tree(1);
    top[1] = 1;
    decompose(1);
}

static void dfs(int x) {
    // printf("enter %d\n", x);

    if (x != 1) {
        stack<Vector> stk;

        int p = father[x];
        int64 maxdist = L[x] - W[x];
        while (p && maxdist >= 0) {
            int t = top[p];
            int64 delta = dist[p] - dist[t];

            if (maxdist < delta) {
                stk.push(
                    tree[t].minimize(dist[p] - maxdist, dist[p], P[x])
                );

                break;
            } else {
                stk.push(convex[t].minimize(P[x]));
                maxdist -= delta + W[t];
            }

            p = father[t];
        }

        ConvexHull con;
        while (!stk.empty()) {
            con.push(stk.top());
            stk.pop();
        }

        Vector vec = con.minimize(P[x]);
        int64 si = vec.x;
        int64 fi = vec.y;
        f[x] = fi + P[x] * (dist[x] - si) + Q[x];
        cnt++;
        // printf("%d\n", cnt);
    }

    convex[top[x]].push(Vector(dist[x], f[x]));
    tree[top[x]].push(Vector(dist[x], f[x]));

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        dfs(v);
    }
    
    convex[top[x]].undo();

    // printf("exited %d\n", x);
}

int main() {
    // freopen("ex_ticket2.in", "r", stdin);
    initialize();

    for (int i = 1; i <= n; i++) {
        convex[i].set_undoable(true);
    }

    dfs(1);

    for (int i = 2; i <= n; i++) {
        printf("%lld\n", f[i]);
    }

    return 0;
}
