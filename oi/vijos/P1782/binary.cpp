#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 10086
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

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }  // while

    return x;
}

#define NMAX 1000000

struct Query {
    int left, right;
    int value;
};  // struct Query

static int n, q;
static int limit[NMAX + 10];
static int mark[NMAX + 10];
static Query op[NMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &q);
    n = readint();
    q = readint();

    for (int i = 1; i <= n; i++)
        // scanf("%d", limit + i);
        limit[i] = readint();
    for (int i = 1; i <= q; i++) {
        // scanf("%d%d%d", &op[i].value, &op[i].left, &op[i].right);
        op[i].value = readint();
        op[i].left = readint();
        op[i].right = readint();
    }
}

static bool validate() {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += mark[i];

        if (sum > limit[i])
            return false;
    }  // for

    return true;
}

static bool test(int x) {
    memset(mark, 0, sizeof(mark));

    for (int i = 1; i <= x; i++) {
        mark[op[i].left] += op[i].value;
        mark[op[i].right + 1] -= op[i].value;
    }  // for

    return validate();
}

int main() {
    initialize();

    int left = 1, right = q;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (test(mid))
            left = mid;
        else
            right = mid;
    }

    if (left != right && test(left))
        left = right;

    if (test(left))
        printf("0\n");
    else
        printf("-1\n%d\n", left);

    return 0;
}  // function main
