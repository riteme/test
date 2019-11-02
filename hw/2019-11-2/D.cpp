#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static char _buf[BUFFERSIZE];
static size_t _pos = BUFFERSIZE, _read;

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        _read = fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        _getc(c);
    } while (isdigit(c));
}

#define MEMSIZE 50000000

static char mem[MEMSIZE];
static size_t mempos;
void *operator new(size_t s) {
    void *r = mem + mempos;
    mempos += s;
    return r;
}

struct Node {
    Node(int _val) : wt(rand()), val(_val),
                     lch(NULL), rch(NULL), rev(0) {}

    int wt, val;
    Node *lch, *rch;
    bool rev;

    void push() {
        if (rev) {
            swap(lch, rch);
            if (lch) lch->rev ^= 1;
            if (rch) rch->rev ^= 1;
            rev = 0;
        }
    }
};

Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    if (x->wt < y->wt) {
        x->push();
        x->rch = meld(x->rch, y);
        return x;
    }
    y->push();
    y->lch = meld(x, y->lch);
    return y;
}

Node *lms(Node *x) {
    x->push();
    if (x->lch) {
        Node *r = lms(x->lch);
        if (x->lch == r) x->lch = NULL;
        return r;
    } else return x;
}

Node *rms(Node *x) {
    x->push();
    if (x->rch) {
        Node *r = rms(x->rch);
        if (x->rch == r) x->rch = NULL;
        return r;
    } else return x;
}

#define NMAX 200000

static int n, q;
static Node *tr[NMAX + 10];

int main() {
    srand(time(0));
    while (true) {
        read(n); read(q);
        if (feof(stdin) && _pos >= _read) break;
        memset(tr + 1, 0, sizeof(Node*) * n);
        mempos = 0;
        int op, u, v, w;
        while (q--) {
            //scanf("%d%d%d", &op, &u, &v);
            read(op); read(u); read(v);
            if (op == 1) {
                //scanf("%d", &w);
                read(w);
                Node *x = new Node(w);
                if (v == 0) {
                    tr[u] = meld(x, tr[u]);
                } else {
                    tr[u] = meld(tr[u], x);
                }
            } else if (op == 2) {
                Node *x;
                if (!tr[u]) puts("-1");
                else if (v == 0) {
                    x = lms(tr[u]);
                    printf("%d\n", x->val);
                    tr[u] = meld(x->rch, tr[u] == x ? NULL : tr[u]);
                } else {
                    x = rms(tr[u]);
                    printf("%d\n", x->val);
                    tr[u] = meld(tr[u] == x ? NULL : tr[u], x->lch);
                }
            } else {
                //scanf("%d", &w);
                read(w);
                if (w && tr[v]) tr[v]->rev ^= 1;
                tr[u] = meld(tr[u], tr[v]);
                tr[v] = NULL;
            }
        }
    }
    return 0;
}
