#include <cstdio>
#include <cstring>

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 40

static int n, cnt;
static map<string, int> id;
static vector<int> G[NMAX + 10];
static char buf[1000];
static string a[NMAX + 10], b[NMAX + 10];

static bool mark[NMAX + 10];
bool dfs(int x, int t) {
    if (x == t) return true;
    mark[x] = true;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (!mark[v] && dfs(v, t)) return true;
    }
    return false;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= cnt; i++) G[i].clear();
        cnt = 0;
        id.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%s", buf);
            a[i] = buf;
            if (!id.count(a[i])) id[a[i]] = ++cnt;
            scanf("%s", buf);
            b[i] = buf;
            if (!id.count(b[i])) id[b[i]] = ++cnt;
        }
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            memset(mark, 0, sizeof(mark));
            int u = id[a[i]];
            int v = id[b[i]];
            if (dfs(v, u)) {
                printf("%s %s\n", a[i].c_str(), b[i].c_str());
                ok = false;
                break;
            }
            G[id[a[i]]].push_back(id[b[i]]);
        }
        if (ok) puts("0");
    }
    return 0;
}
