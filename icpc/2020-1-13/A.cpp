#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, s;
char buf[NMAX + 10];
char m[NMAX + 10][NMAX + 10];
char mt[NMAX + 10][NMAX + 10];

char rot(char c, int d) {
    if (d == 1) {
        switch (c) {
            case '<': return '^';
            case '^': return '>';
            case '>': return 'v';
            case 'v': return '<';
        }
    } else {
        switch (c) {
            case '<': return 'v';
            case 'v': return '>';
            case '>': return '^';
            case '^': return '<';
        }
    }
    return '.';
}

void L() {
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
        mt[n + 1 - y][x] = m[x][y];
    memcpy(m, mt, sizeof(m));
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
        m[x][y] = rot(m[x][y], -1);
}

void R() {
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
        mt[y][n + 1 - x] = m[x][y];
    memcpy(m, mt, sizeof(m));
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
        m[x][y] = rot(m[x][y], 1);
}

int main() {
    scanf("%d%s", &n, buf);
    for (int i = 1; i <= n; i++)
        scanf("%s", m[i] + 1);

    for (int i = 0; buf[i]; i++)
        s += buf[i] == 'L' ? -1 : 1;
    if (s < 0) {
        s = -s;
        while (s--) L();
    } else {
        while (s--) R();
    }

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++)
            putchar(m[x][y]);
        putchar('\n');
    }

    return 0;
}