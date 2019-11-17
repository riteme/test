#include "protocol.h"

#include <cstdio>
#include <cstring>

#define LT 1
#define GT 0
#define NIL -1

static int count;
static int G[500][500];
static bool visited[500];

int n;
Pack s[500];
static int seq[500];

bool dfs(int x, int t) {
    if (x == t) return true;
    visited[x] = true;
    for (int i = 1; i <= G[x][0]; i++) {
        int v = G[x][i];
        if (!visited[v] && dfs(v, t))
            return true;
    }
    return false;
}

int read_cache(int i, int j) {
    memset(visited, 0, sizeof(visited));
    if (dfs(i, j)) return GT;
    memset(visited, 0, sizeof(visited));
    if (dfs(j, i)) return LT;
    return NIL;
}

static int cached;
int cached_cmp(int i, int j) {
    int ret = read_cache(i, j);
    if (ret == NIL) {
        count++;
        ret = seq[i] < seq[j] ? LT : GT;
    } else {
        cached++;
        return ret;
    }

    if (ret == GT)
        G[i][++G[i][0]] = j;
    else
        G[j][++G[j][0]] = i;
    return ret;
}

bool Pack::operator<(const Pack &z) const {
    return cached_cmp(i, z.i);
}

bool is_sorted() {
    for (int i = 2; i <= n; i++)
        if (s[i - 1].v > s[i].v)
            return false;
    return true;
}

void read() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        s[i] = {i, seq[i]};
    }
}

void show() {
    fprintf(stderr, "count: %4d / cached: %3d / rate: %.2lf%%\n",
            count, cached, 100.0 * cached / (count + cached));
}
