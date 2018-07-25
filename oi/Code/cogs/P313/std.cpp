#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define maxn 50010
struct TwoSAT {
    int n;
    vector<int> G[8010 * 2];
    bool mark[maxn];
    int S[maxn], c;

    void init(int n) {
        this->n = n;
        for (int i = 0; i < 2 * n; i++)
            G[i].clear();
        memset(mark, 0, sizeof mark);
    }

    bool DFS(int x) {
        if (mark[x ^ 1])
            return false;
        if (mark[x])
            return true;
        mark[x] = true;
        S[c++] = x;
        for (int i = 0; i < G[x].size(); i++)
            if (!DFS(G[x][i]))
                return false;
        return true;
    }

    void add(int u, int v) {
        // u=u<<1^uval;v=v<<1^vval;
        G[u].push_back(v ^ 1);
        G[v].push_back(u ^ 1);
    }

    bool solve() {
        for (int i = 0; i < 2 * n; i += 2) {
            if (!mark[i] && !mark[i ^ 1]) {
                c = 0;
                if (!DFS(i)) {
                    while (c > 0)
                        mark[S[--c]] = false;
                    if (!DFS(i ^ 1))
                        return false;
                }
            }
        }
        return true;
    }
} SAT;
int n, m;
int main() {
    freopen("spo.in", "r", stdin);
    freopen("spo.out", "w", stdout);
    scanf("%d%d", &n, &m);
    SAT.init(n);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        u--;
        v--;
        SAT.add(u, v);
    }
    if (!SAT.solve())
        printf("NIE");
    else {
        for (int i = 1; i <= 2 * n; i += 2)
            if (SAT.mark[i - 1])
                printf("%d\n", i);
            else
                printf("%d\n", i + 1);
    }
    return 0;
}
