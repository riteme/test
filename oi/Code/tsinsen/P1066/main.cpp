#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 3000

static int n;
static int m;
static int size;
static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
    size = n;
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x != y) {
        set[x] = y;
        size--;
    }
}

int main() {
    scanf("%d %d", &n, &m);

    make_set();
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        union_set(a, b);
    }  // for

    printf("%d", size);

    return 0;
}  // function main
