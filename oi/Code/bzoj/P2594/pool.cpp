#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 1000000

static int n, m, q;

inline int readint() {
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar())
        ;
    int tmp = 0;
    for (; '0' <= ch && ch <= '9'; ch = getchar())
        tmp = tmp * 10 + int(ch) - 48;
    return tmp;
}

static int parent[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static bool reversed[NMAX + 10];
static unsigned min_value[NMAX + 10];

static void initialize_lct() {
    memset(parent, 0, sizeof(parent));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(reversed, false, sizeof(reversed));
    memset(min_value, 0xFF, sizeof(min_value));
}

static void initialize() {
    n = readint();
    m = readint();
    q = readint();
}

int main() {
    initialize_lct();

    return 0;
}  // function main
