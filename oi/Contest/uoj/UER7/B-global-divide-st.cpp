#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 65536
static size_t _ipos = INPUT_BUFFERSIZE;
static char _ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (_ipos == INPUT_BUFFERSIZE) {
        _ipos = 0;
        fread(_ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return _ibuffer[_ipos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (c < '0' || c > '9') {
        c = _getchar();
    }  // while

    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 100000
#define LOGN 17
#define CMAX 1000000

static int n;
static int h[NMAX + 10];
static int answer[NMAX + 10];
static int st_max[NMAX + 10][LOGN + 1];
static int st_min[NMAX + 10][LOGN + 1];
static int highbit[NMAX + 10];
static int record[NMAX + 10];

inline int high(int x) {
    if (highbit[x] >= 0)
        return highbit[x];

    int pos = 0;
    while (x >> (pos + 1) > 0)
        pos++;
    highbit[x] = pos;
    return pos;
}

static void initialize_st_max() {
    for (int i = 0; i <= n; i++)
        st_max[i][0] = h[i];

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 0; i <= n; i++) {
            int next = i + (1 << (j - 1));
            if (next <= n)
                st_max[i][j] = max(st_max[i][j - 1], st_max[next][j - 1]);
        }  // for
    }      // for
}

static int query_max(int left, int right) {
    int k = high(right - left + 1);
    return max(st_max[left][k], st_max[right - (1 << k) + 1][k]);
}

static void initialize_st_min() {
    for (int i = 0; i <= n; i++)
        st_min[i][0] = h[i];

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 0; i <= n; i++) {
            int next = i + (1 << (j - 1));
            if (next <= n)
                st_min[i][j] = min(st_min[i][j - 1], st_min[next][j - 1]);
        }  // for
    }      // for
}

static int query_min(int left, int right) {
    int k = high(right - left + 1);
    return min(st_min[left][k], st_min[right - (1 << k) + 1][k]);
}

static int query(int limit) {
    int i = 1, j = 1;
    int answer = 0;
    while (i <= n && j <= n) {
        if (i > j)
            j = i;

        while (j < n && query_max(i, j + 1) - query_min(i, j + 1) <= limit)
            j++;

        answer = max(answer, j - i + 1);
        i++;
    }  // while

    return answer;
}

static void initialize() {
    // scanf("%d", &n);
    n = readint();

    for (int i = 1; i <= n; i++) {
        // scanf("%d", h + i);
        h[i] = readint();
    }

    initialize_st_max();
    initialize_st_min();
}

inline void update(int i, int limit) {
    int maxv = h[i];
    int minv = h[i];

    for (int j = i - 1; j >= 1; j--) {
        if (i - j + 1 > limit)
            return;

        maxv = max(maxv, h[j]);
        minv = min(minv, h[j]);

        answer[i - j + 1] = min(answer[i - j + 1], maxv - minv);
    }  // for
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        highbit[i] = -1;
    }  // for

    for (int i = 2; i <= n; i++)
        answer[i] = INT_MAX;

    double rate = 200;
    for (int i = rate; i <= CMAX; rate *= 1.05, i = rate) {
        int length = query(i);
        answer[length] = i;
    }  // for

    for (int i = 2; i <= n; i++)
        update(i, 300);

    for (int i = 2; i <= n; i++)
        if (answer[i] == INT_MAX)
            answer[i] = answer[i - 1];

    for (int i = 2; i <= n; i++)
        printf("%d\n", answer[i]);

    return 0;
}  // function main
