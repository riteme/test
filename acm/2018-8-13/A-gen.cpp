#include <cstdio>
#include <cstring>

#include <random>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int fa[NMAX + 10];
int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    printf("1 %d\n", n);
    random_device rd;
    for (int i = 1; i < n; i++) {
        int u, v;
        do {
            u = rd() % n + 1;
            v = rd() % n + 1;
        } while (find(u) == find(v));
        printf("%d %d\n", u, v);
        fa[find(u)] = find(v);
    }
    return 0;
}
