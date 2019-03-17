#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;
static int fa[NMAX + 10], right[NMAX + 10], left[NMAX + 10];
static bool mark[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) left[i] = i;
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        int u = find(x), v = find(y);
        right[u] = left[v];
        fa[u] = v;
        left[v] = left[u];
    }
    for (int i = 1; i <= n; i++) mark[right[i]] = true;
    int x;
    for (x = 1; mark[x]; x++) ;
    do {
        printf("%d ", x);
    } while ((x = right[x]));
    return 0;
}
