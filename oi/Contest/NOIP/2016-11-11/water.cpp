#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define LOGA 30

typedef long long int64;

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
    char c = getchar();

    while (c < '0' || c > '9')
        c = getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }

    return x;
}

struct Node {
    Node()
        : depth(0), size(0), mark(0) {
        memset(next, 0, sizeof(next));
    }
    
    int depth;
    int size;
    int mark;
    Node *next[2];
};

inline void pushdown(Node *x) {
    if (x->mark) {
        if (x->next[0])
            x->next[0]->mark ^= x->mark;
        if (x->next[1])
            x->next[1]->mark ^= x->mark;
        if (x->mark & (1 << x->depth))
            swap(x->next[0], x->next[1]);
        x->mark = 0;
    }
}

inline void update(Node *x) {
    x->size = 0;
    if (x->next[0])
        x->size += x->next[0]->size;
    if (x->next[1])
        x->size += x->next[1]->size;
}

static void insert(Node *x, int pos, int data) {
    if (pos < 0) {
        x->size++;
        return;
    }

    int bit = (data >> pos) & 1;

    pushdown(x);
    if (!x->next[bit]) {
        x->next[bit] = new Node;
        x->next[bit]->depth = x->depth - 1;
    }

    insert(x->next[bit], pos - 1, data);
    update(x);
}

static int query(Node *x, int pos, int data) {
    if (!x)
        return 0;
    if (pos < 0)
        return x->size;
    
    int bit = (data >> pos) & 1;
    pushdown(x);
    return (!bit && x->next[1] ? x->next[1]->size : 0) +
           query(x->next[bit], pos - 1, data);
}

static void clear(Node *x) {
    if (!x)
        return;

    clear(x->next[0]);
    clear(x->next[1]);
    delete x;
}


static int n, K;
static Node *root;

int main() {
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    int t;
    t = readint();

    while (t--) {
        n = readint();
        K = readint();

        root = new Node;
        root->depth = LOGA;
        int64 answer = 0;
        for (int i = 1; i <= n; i++) {
            int v = readint();
            root->mark ^= v;
            insert(root, LOGA, v);
            answer += query(root, LOGA, K);
        }
        clear(root);

        printf("%lld\n", answer);
    }

    return 0;
}
