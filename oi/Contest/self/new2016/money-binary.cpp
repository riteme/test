#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = 0;
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

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 1000000

static int n, k, L, R;
static int w[NMAX + 10];

inline bool test(int x) {
    for (int i = x; i <= n; i++)
        if (w[i] - w[i - x] >= k)
            return true;

    return false;
}

int main() {
    n = readint();
    k = readint();
    L = readint();
    R = readint();

    for (int i = 1; i <= n; i++)
        w[i] = readint() + w[i - 1];

    int left = L, right = R + 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (test(mid))
            right = mid;
        else
            left = mid;
    }

    if (left != right && !test(left))
        left = right;

    if (left > R)
        puts("-1");
    else
        printf("%d\n", left);

    return 0;
}  // function main
