#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

#define NMAX 50000

static int n;
static int s[NMAX + 10];
static int f[NMAX + 10];
static int c[NMAX + 10];
static int cnt[NMAX + 10];
static int r = 0;
static int m = 0;

inline int read() {
    int x = 0, op = 1;
    char ch = getchar();
    while (ch < '0' or ch > '9') {
        if (ch == '-') op = -1;

        ch = getchar();
    }  // while
    while ('0' <= ch and ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }  // while
    return x * op;
}

void initialize();
void output();

int main() {
    initialize();

    for (int i = 2; i <= n; i++) {
        // int j;
        // for (j = r; j > 0; j--) {
        //     // printf("c[%d]: %d, s[%d]: %d\n", j, c[j], i, s[i]);
        //     if (c[j] < s[i]) break;
        // }  // for
        auto iter = std::upper_bound(&c[0], &c[r + 1], s[i]);
        int j = std::distance(&c[1], iter);

        f[i] = j + 1;

        if (s[i] < c[j + 1]) c[j + 1] = s[i];
        if (j == r) r++;
        if (m < f[i]) m = f[i];
    }  // for

    output();
    return 0;
}  // function main

void initialize() {
    n = read();

    std::generate_n(&s[1], n, []() { return read(); });
    std::fill(std::begin(f), std::end(f), 0);
    std::fill(std::begin(cnt), std::end(cnt), 0);
    std::fill(std::begin(c), std::end(c), INT_MAX);

    f[0] = 0;
    f[1] = 1;

    c[0] = INT_MIN;
    c[1] = s[1];

    cnt[0] = 1;
    cnt[1] = 1;

    r = 1;
}

void output() { printf("%d", m); }
