#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
char _buf[BUFFERSIZE];
size_t _pos = BUFFERSIZE;

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

#define NMAX 1000000

int n, q;
int a[NMAX];

struct Node {
    Node(int L, int R) : l(L), r(R), sum(1), lch(NULL), rch(NULL) {
        if (L < R) {
            int m = (L + R) / 2;
            lch = new Node(L, m);
            rch = new Node(m + 1, R);
            update();
        } else mi = a[L];
    }

    int l, r, mi, sum;
    Node *lch, *rch;

    int eval(int K) {
        if (mi >= K)
            return 0;
        if (l == r)
            return 1;
        if (rch->mi < K)
            return sum - rch->sum + rch->eval(K);
        return lch->eval(K);
    }

    void update() {
        mi = min(lch->mi, rch->mi);
        sum = rch->sum + lch->eval(rch->mi);
    }

    int query(int L, int K = INT_MAX) {
        if (l == r)
            return mi < K;
        if (L > rch->l)
            return rch->query(L, K);
        return rch->eval(K) + (L < rch->l ? lch->query(L, min(K, rch->mi)) : 0);
    }

    void modify(int x, int v) {
        if (l == r)
            mi = v;
        else {
            if (x <= lch->r)
                lch->modify(x, v);
            else
                rch->modify(x, v);
            update();
        }
    }
};

int main() {
    // scanf("%d%d", &n, &q);
    read(n); read(q);
    for (int i = 1; i <= n; i++)
        // scanf("%d", a + i);
        read(a[i]);

    auto tr = new Node(1, n);
    while (q--) {
        int op, x, v;
        // scanf("%d%d", &op, &x);
        read(op); read(x);
        if (op == 1) {
            // scanf("%d", &v);
            read(v);
            tr->modify(x, v);
        } else
            printf("%d\n", tr->query(x));
    }

    return 0;
}