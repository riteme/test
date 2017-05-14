#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long u64;

#define NMAX 1000000
#define BASE 233

static int h, w, n;
static u64 tpow[NMAX + 10];
static u64 tar;
static char buf[NMAX + 10];
static vector<int> cnt[NMAX + 10];

inline int id(int i, int j) {
    return (i - 1) * w + j;
}

void initialize() {
    scanf("%d%d%d", &h, &w, &n);

    tpow[0] = 1;
    for (int i = 1; i <= w * h; i++) {
        tpow[i] = tpow[i - 1] * BASE;
    }  // for

    for (int i = 1; i <= h; i++) {
        scanf("%s", buf + 1);

        cnt[i].resize(w + 1);

        for (int j = 1; j <= w; j++) {
            if (buf[j] == '#')
                tar += tpow[id(i, j)];
        }  // for
    }      // for

    int x = 1, y = 1;
    cnt[x][y]++;
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);

    }  // for
}

int main() {
    initialize();

    return 0;
}  // function main
