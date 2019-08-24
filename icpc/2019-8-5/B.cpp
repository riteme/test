#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cctype>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

inline void read(int &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

#define KMAX 30
#define NMAX 100000

static struct Node {
    bool t;
    int c;
    Node *ch[2];
} mem[4000000];
static size_t pos;

inline Node *alloc() {
    memset(mem + pos, 0, sizeof(Node));
    return &mem[pos++];
}

static int n, c[NMAX + 10];

Node *insert(Node *x, int v, int k, bool t) {
    if (!x) x = alloc();
    x->t = t;
    if (k >= 0) {
        int p = (v >> k) & 1;
        x->ch[p] = insert(x->ch[p], v, k - 1, t);
    } else x->c++;
    return x;
}

Node *meld(Node *x, Node *y, int k, int v) {
    if (!x) return y;
    if (!y) return x;
    if (k < 0) {
        int j = min(x->c, y->c);
        while (j--) c[++n] = v;
        x->t = x->c > y->c ? x->t : y->t;
        x->c = abs(x->c - y->c);
        return x->c ? x : NULL;
    }
    x->ch[0] = meld(x->ch[0], y->ch[0], k - 1, v);
    x->ch[1] = meld(x->ch[1], y->ch[1], k - 1, v);
    if (x->ch[0] && x->ch[1] && x->ch[0]->t != x->ch[1]->t) {
        bool lt = x->ch[0]->t;
        Node *z = meld(x->ch[0], x->ch[1], k - 1, v | (1 << k));
        if (z && z->t == lt) {
            x->ch[0] = z;
            x->ch[1] = NULL;
        } else {
            x->ch[1] = z;
            x->ch[0] = NULL;
        }
    }
    if (!x->ch[0] && !x->ch[1]) return NULL;
    if (x->ch[0]) x->t = x->ch[0]->t;
    else x->t = x->ch[1]->t;
    return x;
}

int main() {
    int T;
    //scanf("%d", &T);
    read(T);
    while (T--) {
        Node *a = NULL, *b = NULL;
        //scanf("%d", &n);
        read(n);
        pos = 0;
        for (int i = 0; i < n; i++) {
            int v;
            //scanf("%d", &v);
            read(v);
            a = insert(a, v, KMAX - 1, true);
        }
        for (int i = 0; i < n; i++) {
            int v;
            //scanf("%d", &v);
            read(v);
            b = insert(b, v, KMAX - 1, false);
        }
        n = 0;
        assert(!meld(a, b, KMAX - 1, 0));
        sort(c + 1, c + n + 1);
        for (int i = 1; i <= n; i++) printf(i < n ? "%d "  :"%d\n", c[i]);
    }
    return 0;
}
