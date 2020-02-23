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

#define LTR 1
#define NLE 2
#define SMAX 4

int R[LEN];
i64 f[LEN][SMAX], f0[LEN][SMAX];
i64 g[LEN][SMAX], g0[LEN][SMAX];

i64 solve(i64 _R) {
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
            for (int s = 0; s < SMAX; s++) if (f[c][s]) {
                int r = s & LTR ? 9 : R[k - 1];

                if (i != 0) {
                    int ns = s;
                    if (0 < r) ns |= LTR;
                    f0[c][ns] += f[c][s];
                    g0[c][ns] += g[c][s];
                }

                if (i <= r) {
                    int ns = s;
                    if (i < r) ns |= LTR;
                    if (i) ns |= NLE;
                    int nc = i || (s & NLE) ? c + 1 : c;
                    if (nc < LEN) {
                        f0[nc][ns] += f[c][s];
                        g0[nc][ns] += g[c][s];
                    }
                }

                if (r && r != i) {
                    int ns = s | NLE;
                    f0[c][ns] += f[c][s];
                    g0[c][ns] += g[c][s];
                    if (i < r)
                        g0[c][ns] += f[c][s] * c;
                }

                if (i + 1 < r) {
                    int ns = s | LTR | NLE;
                    f0[c][ns] += f[c][s] * (r - i - 1);
                    g0[c][ns] += (f[c][s] * c + g[c][s]) * (r - i - 1);
                }

                int p = min(i, r) - 1;
                if (p >= 1) {
                    int ns = s | LTR | NLE;
                    f0[c][ns] += f[c][s] * p;
                    g0[c][ns] += g[c][s] * p;
                }
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
        printf("Case %d: %lld\n", _t, solve(r) - solve(l - 1));
    }
    return 0;
}