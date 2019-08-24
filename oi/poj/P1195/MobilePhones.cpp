//
// Copyright 2015 riteme
//

#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

#define SMAX 1024
#define ADD 1
#define QUERY 2
#define TERMINATE 3

static int s;
static int m[SMAX + 10][SMAX + 10];

inline int read() {
    int x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') x = x * 10 + c - '0', c = getchar();

    return x;
}

inline int read_with_sign() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' or c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while ('0' <= c and c <= '9') x = x * 10 + c - '0', c = getchar();

    return x * f;
}

inline int query(int x, int y) {
    int result = 0;

    for (int i = x; i > 0; i -= i & (-i)) {
        for (int j = y; j > 0; j -= j & (-j)) { result += m[i][j]; }  // for
    }                                                                 // for

    return result;
}

inline void insert(int x, int y, int v) {
    for (int i = x; i <= s; i += i & (-i)) {
        for (int j = y; j <= s; j += j & (-j)) { m[i][j] += v; }  // for
    }                                                             // for
}

void initialize();
void quit();

int main() {
    initialize();

    int instruction;
    while (true) {
        instruction = read();

        switch (instruction) {
            case TERMINATE: goto exit_point;
            case ADD:
                int x, y, a;
                x = read() + 1;
                y = read() + 1;
                a = read_with_sign();
                insert(x, y, a);
                break;

            case QUERY:
                int left, bottom, right, top;
                left = read() + 1;
                bottom = read() + 1;
                right = read() + 1;
                top = read() + 1;

                int ans = 0;
                ans = query(right, top) - query(left - 1, top) -
                      query(right, bottom - 1) + query(left - 1, bottom - 1);

                printf("%d\n", ans);
                break;
        }  // switch to instruction
    }      // while

exit_point:
    quit();
    return 0;
}  // function main

void initialize() {
    read();  // Ignore 0
    s = read();

    memset(m, 0, SMAX * SMAX * sizeof(int));
}

void quit() {}
