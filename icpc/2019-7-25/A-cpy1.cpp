#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <random>
#include <unordered_map>
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

#define NMAX 100010
#define MMAX 400000
#define BSIZE 500
#define BMAX 800

typedef unsigned int u32;

static int n, m;
static int A[MMAX + 10];
static bool rev[BMAX];
static unordered_map<int, u32> h0[BMAX], h[BMAX];
static u32 w[NMAX];

#define flip(i, j) h[i][A[j]] ^= w[A[j ^ 1]]

inline u32 query(int u) {
    int j = (m - 1) / BSIZE;
    u32 r = 0;
    for (int i = 0; i <= j; i++) if (h0[i].count(u))
        r ^= h[i][u] ^ (rev[i] ? 0 : h0[i][u]);
    return r;
}

int main() {
    srand(random_device()());
    for (int i = 1; i < NMAX; i++) w[i] = rand();
    int T;
    //scanf("%d", &T);
    read(T);
    while (T--) {
        memset(rev, 0, sizeof(rev));
        //scanf("%d%d", &n, &m);
        read(n); read(m);
        m <<= 1;
        for (int i = 0; i < m; i++) read(A[i]); //scanf("%d", A + i);
        for (int i = 0; i * BSIZE < m; i++) for (int j = i * BSIZE; j < (i + 1) * BSIZE && j < m; j++)
            h0[i][A[j]] ^= w[A[j ^ 1]];
        int q;
        //scanf("%d", &q);
        read(q);
        while (q--) {
            int op, u, v;
            //scanf("%d%d%d", &op, &u, &v);
            read(op); read(u); read(v);
            if (op == 1) {
                u = (u << 1) - 2;
                v = (v << 1) - 1;
                int l = u / BSIZE, r = v / BSIZE;
                if (l == r) for (int j = u; j <= v; j++) flip(l, j);
                else {
                    for (int j = u; j < (l + 1) * BSIZE; j++) flip(l, j);
                    for (int j = r * BSIZE; j <= v; j++) flip(r, j);
                    for (int i = l + 1; i < r; i++) rev[i] ^= 1;
                }
            } else putchar((query(u) == query(v)) + '0');
        }
        putchar('\n');
        for (int i = 0; i * BSIZE < m; i++) {
            h0[i].clear();
            h[i].clear();
        }
    }

    return 0;
}

