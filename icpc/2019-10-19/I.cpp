#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isidigit(c));
    do {
        x = x * 10 + c - 'a';
        _getc(c);
    } while (isidigit(c));
}

struct range {
    range(int _l, int _r) : l(_l), r(_r) {}

    int l, r;

    bool has(int i) const {
        return l <= i && i <= r;
    }

    bool contain(const range &z) const {
        return l <= z.l && z.r <= r;
    }
}

static int n, m, c1, c2;
static int cnt[4];
static range ran[4][NMAX + 10];

void initialize() {
    read(n); read(m); read(c1); read(c2);

    for (int i = 1; i <= m; i++) {
        int x, y, w;
        read(x); read(y);
        if ((x & 1) == (y & 1)) {
            if (x < y)
                swap(x, y);
            ran[x & 1][++cnt[x & 1]] = {x, y};
        } else {

        }
    }
}

int main() {
    initialize();

    return 0;
}
