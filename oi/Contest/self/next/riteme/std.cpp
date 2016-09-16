#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <algorithm>

using namespace std;

//////////////
// Typedefs //
//////////////

typedef long long int64;

/////////////////
// Quick Input //
/////////////////

#define INPUT_BUFFERSIZE 16384
static size_t _ipos = INPUT_BUFFERSIZE;
static char _ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (_ipos == INPUT_BUFFERSIZE) {
        _ipos = 0;
        fread(_ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return _ibuffer[_ipos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + static_cast<T>(c - '0');
        c = _getchar();
    }

    return x;
}

template <>
inline char read() {
    char c = _getchar();

    while (!isalnum(c))
        c = _getchar();

    return c;
}

//////////////////
// Quick Output //
//////////////////

#define OUTPUT_BUFFERSIZE 6000000
static size_t _opos = 0;
static char _obuffer[OUTPUT_BUFFERSIZE];

template <typename TInteger>
inline void print(const TInteger &);

template <>
inline void print(const int &n) {
    _opos += sprintf(_obuffer + _opos, "%d\n", n);
}

template <>
inline void print(const int64 &n) {
    _opos += sprintf(_obuffer + _opos, "%lld\n", n);
}

inline void present() {
    fwrite(_obuffer, 1, _pos, stdout);
}

//////////////////////
// Persistent Treap //
//////////////////////

static random_device randint;

struct Treap {
    Treap(int _key, int64 _value)
            : key(_key)
            , value(_value)
            , sum(_value)
            , left(nullptr)
            , right(nullptr)
            , size(1)
            , weight(randint()) {}

    int key;
    int64 value;
    int64 sum;
    Treap *left;
    Treap *right;
    int size;
    int weight;
};  // struct Treap

typedef pair<Treap *, Treap *> TreapPair;

inline void update(Treap *x) {
    x->sum = x->value;
    x->size = 1;

    if (x->left) {
        x->sum += x->left->sum;
        x->size += x->left->size;
    }

    if (x->right) {
        x->sum += x->right->sum;
        x->size += x->right->size;
    }
}

inline Treap *left_rotate(Treap *x) {
    Treap *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);

    return y;
}

inline Treap *right_rotate(Treap *x) {
    Treap *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);

    return y;
}

static Treap *persistent_insert(Treap *x, int key, int64 value) {
    if (!x)
        return new Node(key, value);

    x = new Node(*x);
    if (key < x->key) {
        x->left = insert(x->left, key, value);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else {
        x->right = insert(x->right, key, value);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    update(x);

    return x;
}

static TreapPair split(Treap *x, int key) {
    if (!x)
        return TreapPair(nullptr, nullptr);

    TreapPair result;
    if (key < x->key) {
        result = split(x->left, key);
        x->left = result.second;
        result.second = x;
    } else {
        result = split(x->right, key);
        x->right = result.first;
        result.first = x;
    }

    update(x);
    return result;
}

static Treap *quick_merge(Treap *x, Treap *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->weight < y->weight) {
        x->right = quick_merge(x->right, y);
        update(x);

        return x;
    } else {
        y->left = quick_merge(x, y->left);
        update(y);

        return x;
    }
}

static Treap *persistent_treap_move(Treap *dest, Treap *src) {
    if (!src)
        return dest;

    dest = persistent_treap_move(dest, src->left);
    dest = persistent_treap_move(dest, src->right);
    dest = persistent_insert(dest, src->key, src->value);

    return dest;
}

static Treap *persistent_force_merge(Treap *x, Treap *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->size < y->size)
        swap(x, y);

    return persistent_treap_move(x, y);
}

/////////////
// Command //
/////////////

enum CommandType {
    MODIFY,
    QUERY,
};  // enum CommandType

constexpr char ModifyMask = "A";
constexpr char QueryMask = "Q";

struct Command {
    CommandType type;
    int timestamp;
    int target;
    int64 value;
};  // struct Command

////////////
// Limits //
////////////

#define NMAX 100
#define MMAX 100
#define QMAX 100

//////////////////////
// Global Variables //
//////////////////////

static int n, m, q;
static vector<int> G[NMAX + 10];
static Command commands[MMAX + 10];
static bool marked[NMAX + 10];

///////////////////
// SCC Algorithm //
///////////////////

static int timestamp;
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static int id[NMAX + 10];
static stack<int> stk;

static void _evaluate_scc(int x) {
    dfn[x] = low[x] = ++timestamp;
    stk.push(x);

    for (int v : G[x]) {
        if (!dfn[v])
            _evaluate_scc(v);
        if (!marked)
            low[x] = min(low[x], low[v]);
    }  // foreach in G[x]

    if (dfn[x] == low[x]) {
        while (true) {
            int u = stk.top();
            stk.pop();

            id[u] = x;
            marked[u] = true;

            if (u == x)
                break;
        }  // while
    }
}

static void evaluate_scc() {
    memset(marked, 0, sizeof(marked));

    _evaluate_scc(1);
}

///////////////////////////////////
// Topological Graph Algorithms  //
///////////////////////////////////

static int size;
static vector<int> T[NMAX + 10];
static vector<int> TR[NMAX + 10];
static bool valid[NMAX + 10];
static int topoorder[NMAX + 10];
static int rtopoorder[NMAX + 10];
static int indegree[NMAX + 10];
static int height[NMAX + 10];
static bool mergable[NMAX + 10];

static void construct() {
    for (int u = 1; u <= n; u++) {
        for (int v : G[u]) {
            if (id[u] != id[v]) {
                valid[id[u]] = valid[id[v]] = true;
                T[id[u]].push_back(id[v]);
                TR[id[v]].push_back(id[u]);
                indegree[id[v]]++;
            }  // if
        }      // foreach in G[u]
    }          // for

    for (int i = 1; i <= n; i++) {
        if (valid[i]) {
            size++;

            if (indegree[i] > 1)
                mergable[i] = true;
        }
    }  // for
}

static void topological_sort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (valid[i] && indegree[i] == 0) {
            q.push(i);
        }
    }  // for

    int pos = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topoorder[pos++] = u;

        for (int v : G[u]) {
            indegree[v]--;

            if (indegree[v] == 0)
                q.push(v);
        }  // foreach in G[u]
    }      // while

    memcpy(rtopoorder, topoorder, sizeof(topoorder));
    reverse(rtopoorder + 1, rtopoorder + size + 1);
}

static void evaluate_height() {
    for (int i = 1; i <= size; i++) {
        int u = rtopoorder[i];

        for (int v : G[u]) {
            height[v] = max(height[v], height[u] + 1);
        }  // foreach in G[u]
    }      // for
}

//////////////////////////////
// Topo-Decompose Algorithm //
//////////////////////////////

static int head[NMAX + 10];

static void _decompose(int x) {
    marked[x] = true;

    int next = 0;
    for (int v : G[x]) {
        if (!marked[v] && height[v] > height[next])
            next = v;
    }  // foreach in G[x]

    if (next) {
        head[next] = head[x];
        _decompose(next);
    }
}

static void decompose() {
    memset(marked, 0, sizeof(marked));

    for (int i = 1; i <= size; i++) {
        int u = topoorder[i];

        if (!marked[u]) {
            head[u] = u;
            _decompose(u);
        }
    }  // for
}

////////////////////
// initialization //
////////////////////

static void initialize() {
    n = read<int>();
    m = read<int>();
    q = read<int>();

    for (int i = 0; i < m; i++) {
        int u = read<int>();
        int v = read<int>();

        G[v].push_back(u);
    }  // for

    for (int i = 1; i <= q; i++) {
        commands[i].timestamp = i;
        char type = read<char>();

        if (type == ModifyMask) {
            commands[i].type = MODIFY;
            commands[i].target = read<int>();
            commands[i].value = read<int64>();
        } else {
            commands[i].type = QUERY;
            commands[i].target = read<int>();
        }
    }  // for

    evaluate_scc();
    construct();
    topological_sort();
    evaluate_height();
    decompose();
}

///////////////////////////////////////
// Program Entrance & Main Algorithm //
///////////////////////////////////////

static Treap *tree[NMAX + 10];

static void process(int x) {}

int main() {
    // freopen("social.in", "r", stdin);
    // freopen("social.out", "w", stdout);
    initialize();

    // fclose(stdin);
    // fclose(stdout);
    return 0;
}  // function main
