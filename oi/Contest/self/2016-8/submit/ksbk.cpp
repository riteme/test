#define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

#define INPUT_BUFFERSIZE 4096
static size_t _pos = INPUT_BUFFERSIZE;
static char _buffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (_pos == INPUT_BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 2500000

typedef unsigned long long int64;

static int n;
static int64 k;
static int a[NMAX + 10];
static int p[NMAX + 10];
static int loopcnt;
static vector<int> loop[NMAX + 10];
static int loopid[NMAX + 10];
static int looppos[NMAX + 10];

inline size_t mod(int a, int b) {
    int m = a % b;
    if (m < 0)
        return m + b;
    else
        return m;
}

int main() {
    // freopen("ksbk.in", "r", stdin);
    // freopen("ksbk.out", "w", stdout);

    n = read<int>();
    k = read<int64>();
    for (int i = 1; i <= n; i++)
        a[i] = read<int>();
    for (int i = 1; i <= n; i++)
        p[i] = read<int>();

    for (int i = 1; i <= n; i++) {
        if (!loopid[i]) {
            int u = i;
            int pos = 0;
            loopcnt++;
            do {
                loop[loopcnt].push_back(a[u]);
                loopid[u] = loopcnt;
                looppos[u] = pos++;
                u = p[u];
            } while (u != i);  // do ... while
        }
    }  // for

    for (int i = 1; i <= n; i++) {
        int length = loop[loopid[i]].size();
        int mk = k % length;
        int x = loop[loopid[i]][mod(looppos[i] - mk, length)];
        printf("%d ", x);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
