#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE, _sz;
char _buf[BUFFERSIZE];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        _sz = fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _pos < _sz ? _buf[_pos++] : 0;
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getc(); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
}

#define LEN 16

typedef long long i64;

#define GTL 1
#define LTR 2
#define NLE 4
#define SMAX 8

int L[LEN], R[LEN];
i64 f[LEN][SMAX], f0[LEN][SMAX];
i64 g[LEN][SMAX], g0[LEN][SMAX];

i64 solve(i64 _L, i64 _R) {
    for (int i = 0; i < LEN; i++, _L /= 10)
        L[i] = _L % 10;
    for (int i = 0; i < LEN; i++, _R /= 10)
        R[i] = _R % 10;

    i64 sum = 0;
    for (int i = 0; i < 10; i++) {
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        f[0][0] = 1;

        for (int k = LEN - 1; k; k--) {
            memset(f0, 0, sizeof(f));
            memset(g0, 0, sizeof(g));
            for (int c = 0; c < LEN; c++)
            for (int s = 0; s < SMAX; s++) {
                int l = s & GTL ? 0 : L[k - 1];
                int r = s & LTR ? 9 : R[k - 1];

                for (int d = l; d <= r; d++) {
                    int ns = s;
                    if (d > l) ns |= GTL;
                    if (d < r) ns |= LTR;
                    if (d) ns |= NLE;

                    int nc = d == i && (i || (s & NLE)) ? c + 1 : c;
                    if (nc < LEN) {
                        f0[nc][ns] += f[c][s];
                        g0[nc][ns] += g[c][s];
                        if (i < d)
                            g0[nc][ns] += f[c][s] * c;
                    }
                }c
            }

            if (k > 1) {
                memcpy(f, f0, sizeof(f));
                memcpy(g, g0, sizeof(g));
            }
        }

        for (int i = 0; i < LEN; i++)
        for (int s = 0; s < SMAX; s++)
            sum += g0[i][s];
    }

    return sum;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        i64 l, r;
        scanf("%lld%lld", &l, &r);
        printf("Case %d: %lld\n", _t, solve(l, r));
    }
    return 0;
}