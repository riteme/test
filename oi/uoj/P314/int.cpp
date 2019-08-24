#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];
inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _buf[_pos++];
}

inline void read(int &x) {
    x = 0;
    int f = 1;
    char c;
    do {
        c = _getchar();
        if (c == '-') {
            f = -1;
            c = _getchar();
        }
    } while (!isalnum(c));

    for (; isalnum(c); c = _getchar())
        x = x * 10 + (c - '0');

    x *= f;
}

// Bit flags manipulations:
#define mask(x) ((1 << (x)) - 1)

inline void showbits(int x, int n) {
    while (n--) {
        putchar(x & 1 ? '1' : '0');
        x >>= 1;
    }
}

inline void set(int &dest, int flag) {
    dest |= flag;
}

inline void sets(int &dest, int flag, int m) {
    dest = (dest & ~m) | flag;
}

inline void del(int &dest, int m) {
    dest &= ~m;
}

inline void cpy(int &dest, int src, int m) {
    dest = (dest & ~m) | (src & m);
}

inline int locate(int x, int v, int maxp) {
    if (v) x = ~x;
    return __builtin_ctz(x | (1 << maxp));
}

#define NMAX 2097152

#define L(x) (x << 1)
#define R(x) (L(x) | 1)

#define SETALL 1
#define CLEARALL 2
#define OP_MASK (SETALL | CLEARALL)
#define MODE_ALLSET 4
#define MODE_ALLZERO 8
#define MODE_MASK (MODE_ALLSET | MODE_ALLZERO)

inline int nxtp(int x) {
    int k = 1;
    while (k < x)
        k <<= 1;
    return k;
}

template <unsigned N>
class Bitset {
 public:
    Bitset(int _n) : n(nxtp(_n)) {  // exp of 2 for convinence
        memset(dat, 0, sizeof(dat));

        for (int i = 1; i < n; i++) {
            set(dat[i], MODE_ALLZERO);
        }
    }

    int get(int p) {
        return _get(p, 1, 0, n);
    }

    void modify(int p, int v) {
        _modify(p, v, 1, 0, n);
    }

    void inverse(int p, int v) {  // ~v: target bit
        int x = 1, l = 0, r = n;
        while (x < n) {
            _push(x);
            int m = (l + r) >> 1;
            if (p < N * m) {
                x = L(x);
                r = m;
            } else {
                x = R(x);
                l = m;
            }
        }

        int s = p - N * l;
        int i = locate(dat[x] >> s, v, N);
        if (s + i < N)
            cpy(dat[x], (v ? (1 << i) : ~(1 << i)) << s, mask(i + 1) << s);
        else {
            cpy(dat[x], v ? 0 : mask(N), mask(N - s) << s);

            bool lbit = x & 1;
            x >>= 1;
            while (lbit || _test(R(x), v)) {
                if (!lbit)
                    _set(R(x), v ? CLEARALL : SETALL);

                _pull(x);
                lbit = x & 1;
                x >>= 1;
            }

            for (x = R(x); x < n; ) {
                if (_test(L(x), v)) {
                    _set(L(x), v ? CLEARALL : SETALL);
                    x = R(x);
                } else
                    x = L(x);
            }

            i = locate(dat[x], v, N);
            cpy(dat[x], v ? (1 << i) : ~(1 << i), mask(i + 1));
        }

        _update(x);
    }

    void show() {
        _show(1, 0, n);
        putchar('\n');
    }

 private:
    int n;
    int dat[NMAX + 10];

    void _set(int x, int s) {
        if (x < n)
            sets(dat[x], s, OP_MASK);
        else {
            if (s == SETALL)
                dat[x] = mask(N);
            else
                dat[x] = 0;
        }
    }

    void _push(int x) {
        assert(x < n);

        if (dat[x] & OP_MASK) {
            assert((dat[x] & OP_MASK) != OP_MASK);

            if (L(x) >= n) {  // if children are leaves
                if (dat[x] & SETALL)
                    dat[L(x)] = dat[R(x)] = mask(N);
                else
                    dat[L(x)] = dat[R(x)] = 0;
            } else {
                cpy(dat[L(x)], dat[x], OP_MASK);
                cpy(dat[R(x)], dat[x], OP_MASK);
            }

            if (dat[x] & SETALL)
                sets(dat[x], MODE_ALLSET, OP_MASK);
            else
                sets(dat[x], MODE_ALLZERO, OP_MASK);
            del(dat[x], OP_MASK);
        }
    }

    void _pull(int x) {
        assert(x < n);

        if (_test(L(x), 0) && _test(R(x), 0))
            sets(dat[x], MODE_ALLZERO, MODE_MASK);
        else if (_test(L(x), 1) && _test(R(x), 1))
            sets(dat[x], MODE_ALLSET, MODE_MASK);
        else
            sets(dat[x], 0, MODE_MASK);
    }

    void _update(int x) {
        assert(x >= n);
        for (x >>= 1; x; x >>= 1)
            _pull(x);
    }

    bool _test(int x, int v) {
        if (v)
            return (x < n &&
                       ((dat[x] & SETALL) ||
                        (!(dat[x] & OP_MASK) && (dat[x] & MODE_ALLSET)))
                   ) ||
                   (x >= n && dat[x] == mask(N));
        return (x < n &&
                   ((dat[x] & CLEARALL) ||
                    (!(dat[x] & OP_MASK) && (dat[x] & MODE_ALLZERO)))
               ) ||
               (x >= n && !dat[x]);
    }

    // index [0..30n), [l, r)
    int _get(int p, int x, int l, int r) {
        int lb = N * l, rb = N * r;
        if (x >= n) {
            assert(p < rb);
            if (p <= lb)
                return dat[x] & mask(p + N - lb);
            return dat[x] >> (p - lb);
        }

        _push(x);
        int m = (l + r) >> 1;
        int mb = N * m;
        if (p + N <= mb)
            return _get(p, L(x), l, m);
        else if (p >= mb)
            return _get(p, R(x), m, r);
        return _get(p, L(x), l, m) |
               (_get(p, R(x), m, r) << (mb - p));
    }

    void _modify(int p, int v, int x, int l, int r) {
        int lb = N * l, rb = N * r;
        if (x >= n) {
            assert(p < rb);
            if (p <= lb)
                cpy(dat[x], v >> (lb - p), mask(p + N - lb));
            else
                cpy(dat[x], v << (p - lb), mask(rb - p) << (p - lb));
        } else {
            _push(x);
            int m = (l + r) >> 1;
            int mb = N * m;
            if (p < mb)
                _modify(p, v, L(x), l, m);
            if (p + N >= mb)
                _modify(p, v, R(x), m, r);
            _pull(x);
        }
    }

    void _show(int x, int l, int r) {
        if (x >= n) {
            showbits(dat[x], N);
            putchar(' ');
        } else {
            if (_test(x, 0)) {
                for (int i = l; i < r; i++) {
                    showbits(0, N);
                    putchar(' ');
                }
            } else if (_test(x, 1)) {
                for (int i = l; i < r; i++) {
                    showbits(mask(N), N);
                    putchar(' ');
                }
            } else {
                int m = (l + r) >> 1;
                _show(L(x), l, m);
                _show(R(x), m, r);
            }
        }
    }
};

int main() {
#ifdef NDEBUG
    int n, tmp, a, b, c;
    read(n);
    read(tmp);read(tmp);read(tmp);

    Bitset<30> *bits = new Bitset<30>(n);
    while (n--) {
        read(a);
        read(b);

        if (a == 1) {
            read(c);

            /*int v = b >= 0 ? 1 : 0;
            b = v ? b : -b;
            while (b) {
                int i = __builtin_ctz(b);
                bits->inverse(c + i, v);
                b ^= 1 << i;
            }*/
            int t = bits->get(c) + b;
            if (t >= 0) {
                bits->modify(c, t & mask(30));
                if ((t >> 30) & 1)
                    bits->inverse(c + 30, 1);
            } else {
                bits->modify(c, (1 << 30) + t);
                bits->inverse(c + 30, 0);
            }
        } else
            printf("%d\n", bits->get(b) & 1);
    }
#else
    int n;
    scanf("%d", &n);

    Bitset<4> *bits = new Bitset<4>(n);
    int q;
    while (scanf("%d", &q) != EOF) {
        if (q == 1) {
            int p, x = 0, y = 0;
            char buf[32];
            scanf("%d%s", &p, buf);
            for (int i = 0; buf[i]; i++) {
                x = (x << 1) | (buf[i] - '0');
            }
            for (int i = 0; buf[i]; i++) {
                y = (y << 1) | (x & 1);
                x >>= 1;
            }
            bits->modify(p, y);
        } else if (q == 2) {
            int p, v;
            scanf("%d%d", &p, &v);
            bits->inverse(p, v);
        } else {
            int p;
            scanf("%d", &p);
            showbits(bits->get(p), 4);
            putchar('\n');
        }

        bits->show();
    }
#endif
}
