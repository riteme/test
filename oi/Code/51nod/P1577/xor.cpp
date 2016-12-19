/**
 * 贪心地维护线性基，每次维护最靠后的线性基
 * 时间/空间复杂度：O(n log n)
 */

#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

using namespace std;

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
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 500000
#define SPACESIZE 30

static int n, m;
static int vec[NMAX + 10][SPACESIZE];
static int left[NMAX + 10][SPACESIZE];

inline void append(int pos, int x) {
    memcpy(&vec[pos][0], &vec[pos - 1][0], sizeof(int) * SPACESIZE);
    memcpy(&left[pos][0], &left[pos - 1][0], sizeof(int) * SPACESIZE);
    
    int t = pos;
    for (int i = SPACESIZE - 1; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (vec[pos][i]) {
                int tmpx = vec[pos][i];
                int tmpt = left[pos][i];

                if (t > tmpt) {
                    vec[pos][i] = x;
                    left[pos][i] = t;
                }

                x ^= tmpx;
                t = min(t, tmpt);
            } else {
                vec[pos][i] = x;
                left[pos][i] = t;

                break;
            }
        }
    }
}

static void initialize() {
    // scanf("%d", &n);
    n = readint();

    for (int i = 1; i <= n; i++) {
        int v;
        // scanf("%d", &v);
        v = readint();

        append(i, v);
    }
}

inline bool query(int l, int r, int v) {
    for (int i = SPACESIZE - 1; i >= 0; i--) {
        if ((v >> i) & 1) {
            if (vec[r][i] && left[r][i] >= l)
                v ^= vec[r][i];
            else
                return false;
        }
    }

    return true;
}

int main() {
    initialize();

    // scanf("%d", &m);
    m = readint();

    while (m--) {
        int l, r, v;
        // scanf("%d%d%d", &l, &r, &v);
        l = readint();
        r = readint();
        v = readint();

        puts(query(l, r, v) ? "YES" : "NO");
    }

    return 0;
}
