// fake!

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

#define NMAX 2500000
#define Lc(x) (x << 1)
#define Rc(x) ((x << 1) | 1)

int n, q, T;
int mi[NMAX];

namespace seg {
    void update(int x) {
        mi[x] = min(mi[Lc(x)], mi[Rc(x)]);
    }

    int search(int x, int l, int r, int K) {
        while (l < r) {
            int m = (l + r) / 2;
            if (mi[Rc(x)] < K) {
                x = Rc(x);
                l = m + 1;
            } else {
                x = Lc(x);
                r = m;
            }
        }
        return l;
    }

    int prev(int x, int xl, int xr, int r, int K) {
        if (xr <= r)
            return mi[x] < K ? search(x, xl, xr, K) : 0;

        int m = (xl + xr) / 2;
        int ret = 0;
        if (r > m)
            ret = prev(Rc(x), m + 1, xr, r, K);
        if (!ret)
            return prev(Lc(x), xl, m, r, K);
    }
}

#define L 0
#define R 1

namespace tr {
    int pa[NMAX];
    int ch[NMAX][2];
    int size[NMAX];

    void update(int x) {
        size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    }

    void rotate(int y) {
        int x = pa[y];
        int c = ch[x][1] == y;
        ch[x][c] = ch[y][c^1];
        ch[y][c^1] = x;

        if (pa[x])
            ch[pa[x]][ch[pa[x]][1] == x] = y;
        pa[y] = pa[x];
        pa[x] = y;
        pa[ch[x][c]] = x;

        size[y] = size[x];
        update(x);
    }

    void splay(int x, int t = 0) {
        while (pa[x] != t) {
            int p = pa[x], g = pa[p];
            if (g != t && (ch[g][1] == p) == (ch[p][1] == x))
                rotate(p);
            rotate(x);
        }
    }

    int locate1(int x, int p) {
        int r = 0;
        while (x) {
            if (p <= x) {
                r = x;
                x = ch[x][L];
            } else
                x = ch[x][R];
        }
        return r;
    }

    int locate2(int x, int p) {
        int r = 0;
        while (x) {
            if (p <= mi[T + x]) {
                r = x;
                x = ch[x][L];
            } else
                x = ch[x][R];
        }
        return r;
    }

    void cut(int x) {
        splay(x);
        pa[ch[x][0]] = pa[ch[x][1]] = 0;
        ch[x][0] = ch[x][1] = 0;
        update(x);
    }
}

bool en[NMAX];



void initialize() {
    read(n); read(q);
    T = 1;
    while (T < n) T <<= 1;
    T--;

    for (int i = 1; i <= n; i++)
        read(mi[T + i]);
    for (int i = T; i; i--)
        seg::update(i);

    mi[T + n + 1] = INT_MAX;
    en[0] = true;
}

int main() {
    initialize();

    while (q--) {
        int op, x, v;
        read(op); read(x);
        if (op == 1) {
            read(v);
        } else {

        }
    }

    return 0;
}