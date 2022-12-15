#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

struct vec {
    int x, y;
};

int n, m;
bool vis[128][128];
char a[128][128];
int head, tail;
vec q[20000];

int id(const vec &u) {
    return (u.x - 1) * m + u.y;
}

bool near_black(const vec &u) {
    return
        a[u.x + 1][u.y] == 'o' ||
        a[u.x - 1][u.y] == 'o' ||
        a[u.x][u.y + 1] == 'o' ||
        a[u.x][u.y - 1] == 'o';
}

void fill_white(const vec &s) {
    head = tail = 0;
    vis[s.x][s.y] = true;
    q[tail++] = s;
    int cnt = 0;
    while (head < tail) {
        vec u = q[head++];
        if (u.x < 1 || u.x > n || u.y < 1 || u.y > m || a[u.x][u.y] == 'o')
            continue;
        if (near_black(u))
            a[u.x][u.y] = 'x';
        else if (a[u.x][u.y] == '.')
            cnt++;
        constexpr int dx[] = {1, -1, 0, 0};
        constexpr int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; i++) {
            vec v = {u.x + dx[i], u.y + dy[i]};
            if (!vis[v.x][v.y]) {
                vis[v.x][v.y] = true;
                q[tail++] = v;
            }
        }
    }
    if (cnt == 0)
        a[s.x][s.y] = '.';
}

void print() {
    for (int i = 1; i <= n; i++) {
        puts(a[i] + 1);
    }
}

int pa[10086];
int find(int x) {
    return pa[x] <= 0 ? x : pa[x] = find(pa[x]);
}

vector<int> G[10086];

void find_black(const vec &s) {
    head = tail = 0;
    vis[s.x][s.y] = true;
    q[tail++] = s;
    int cnt = 0;
    int i = find(id(s));
    while (head < tail) {
        vec u = q[head++];
        if (u.x < 1 || u.x > n || u.y < 1 || u.y > m || a[u.x][u.y] == 'x')
            continue;
        if (a[u.x][u.y] == '.') {
            cnt++;
            continue;
        }
        int j = find(id(u));
        pa[j] = i;

        constexpr int dx[] = {1, -1, 0, 0};
        constexpr int dy[] = {0, 0, 1, -1};
        for (int k = 0; k < 4; k++) {
            vec v = {u.x + dx[k], u.y + dy[k]};
            if (!vis[v.x][v.y]) {
                vis[v.x][v.y] = true;
                q[tail++] = v;
            }
        }
    }
    pa[i] = -cnt;
}

bool air[10086];
bool fucked[10086];

void fuck(int u) {
    fucked[u] = true;

    sort(G[u].begin(), G[u].end());
    G[u].erase(unique(G[u].begin(), G[u].end()), G[u].end());

    if (air[u]) {
        for (int v : G[u]) {
            pa[v]++;
            if (!fucked[v] && -pa[v] <= 1)
                fuck(v);
        }
    } else {
        for (int v : G[u]) {
            if (!fucked[v])
                fuck(v);
        }
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", a[i] + 1);
    }

    memset(vis, 0, sizeof(vis));
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (!vis[x][y] && a[x][y] != 'o')
                fill_white({x, y});
        }
    }
    // print();

    memset(pa, 0, sizeof(pa));
    memset(vis, 0, sizeof(vis));
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (!vis[x][y] && a[x][y] == 'o')
                find_black({x, y});
        }
    }

    memset(air, 0, sizeof(air));
    for (int i = 1; i <= n * m; i++) {
        G[i].clear();
    }
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (a[x][y] != '.')
                continue;
            int i = id({x, y});
            air[i] = true;
            constexpr int dx[] = {1, -1, 0, 0};
            constexpr int dy[] = {0, 0, 1, -1};
            for (int k = 0; k < 4; k++) {
                int tx = x + dx[k];
                int ty = y + dy[k];
                if (a[tx][ty] == 'o') {
                    int j = find(id({tx, ty}));
                    G[i].push_back(j);
                    G[j].push_back(i);
                }
            }
        }
    }

    memset(fucked, 0, sizeof(fucked));
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            int u = id({x, y});
            if (a[x][y] == 'o' && pa[u] <= 0 && !fucked[u] && -pa[u] <= 1)
                fuck(u);
        }
    }

    int cnt = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            int u = id({x, y});
            if (a[x][y] == 'o' && pa[u] <= 0 && !fucked[u])
                cnt++;
        }
    }

    puts(cnt > 0 ? "LIVE" : "DEAD");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }

    return 0;
}
