#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#define eps 1e-5
#define MAXN 11111
#define MAXM 55555
#define INF 1000000000
using namespace std;
struct EDGE {
    int v, next, w;
} edge[MAXM];
int head[MAXN], e;
int n, k, vis[MAXN], ans, root, num;
void init() {
    memset(vis, 0, sizeof(vis));
    memset(head, -1, sizeof(head));
    e = ans = 0;
}
void add(int u, int v, int w) {
    edge[e].v = v;
    edge[e].w = w;
    edge[e].next = head[u];
    head[u] = e++;
}
int mx[MAXN], size[MAXN], mi, dis[MAXN];
void dfssize(int u, int fa)  //处理子树的大小
{
    size[u] = 1;
    mx[u] = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa && !vis[v]) {
            dfssize(v, u);
            size[u] += size[v];
            if (size[v] > mx[u])
                mx[u] = size[v];
        }
    }
}
void dfsroot(int r, int u, int fa)  //求重心
{
    if (size[r] - size[u] > mx[u])
        mx[u] = size[r] - size[u];
    if (mx[u] < mi)
        mi = mx[u], root = u;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa && !vis[v])
            dfsroot(r, v, u);
    }
}
void dfsdis(int u, int d, int fa)  //求距离
{
    dis[num++] = d;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa && !vis[v])
            dfsdis(v, d + edge[i].w, u);
    }
}
int calc(int u, int d) {
    int ret = 0;
    num = 0;
    dfsdis(u, d, 0);
    sort(dis, dis + num);
    int i = 0, j = num - 1;
    while (i < j)  //经典
    {
        while (dis[i] + dis[j] > k && i < j)
            j--;
        ret += j - i;
        i++;
    }
    return ret;
}
void dfs(int u) {
    mi = n;
    dfssize(u, 0);
    dfsroot(u, u, 0);
    ans += calc(root, 0);
    vis[root] = 1;
    for (int i = head[root]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (!vis[v]) {
            ans -= calc(v, edge[i].w);
            dfs(v);
        }
    }
}
int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        if (!n && !k)
            break;
        init();
        int u, v, w;
        for (int i = 0; i < n - 1; i++) {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}
