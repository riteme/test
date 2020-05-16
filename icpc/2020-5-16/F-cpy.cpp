#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define LMAX 1000000

int n, m, L;
int d[NMAX + 10][NMAX + 10][4];
char s[LMAX + 10], mp[NMAX + 10][NMAX + 10];
int suf[LMAX + 10];
int to[LMAX + 10][4];

struct State {
    int x, y, r, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

int rot(int r, char c) {
    if (c == 'L')
        return (r + 3) & 3;
    return (r + 1) & 3;
}

void solve() {
    scanf("%s", s);
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);

    suf[L] = 0;
    int lp[] = {L, -1, -1, -1};
    for (int i = L - 1; i >= 0; i--) {
        suf[i] = (suf[i + 1] + (s[i] == 'L' ? 3 : 1)) & 3;
        lp[suf[i]] = i;
        for (int j = 1; j < 4; j++)
            to[i][j] = lp[(suf[i] + 4 - j) & 3];
    }

    int tx, ty;
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= m; y++)
    for (int i = 0; i < 4; i++)
        d[x][y][i] = 0x3f3f3f3f;

    priority_queue<State> q;
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= m; y++)
    if (mp[x][y] == 'S') {
        d[x][y][0] = 0;
        q.push({x, y, 0, 0});
    } else if (mp[x][y] == 'E') {
        tx = x;
        ty = y;
    }

    do {
        auto u = q.top();
        q.pop();
        if (u.t > d[u.x][u.y][u.r])
            continue;

        if (u.t < L) {
            for (int i = 1; i < 4; i++)
            if (to[u.t][i] >= 0) {
                int nr = (u.r + i) & 3;
                int nt = to[u.t][i];
                if (d[u.x][u.y][nr] > nt) {
                    d[u.x][u.y][nr] = nt;
                    q.push({u.x, u.y, nr, nt});
                }
            }
        }

        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};
        int nx = u.x + dx[u.r];
        int ny = u.y + dy[u.r];
        if (1 <= nx && nx <= n &&
            1 <= ny && ny <= m &&
            mp[nx][ny] != '#' &&
            d[nx][ny][u.r] > u.t) {
            d[nx][ny][u.r] = u.t;
            q.push({nx, ny, u.r, u.t});
        }
    } while (!q.empty());

    int md = L + 10;
    for (int i = 0; i < 4; i++)
        md = min(md, d[tx][ty][i]);
    puts(md <= L ? "Yes" : "No");
}

int main() {
    while (scanf("%d%d%d", &n, &m, &L) != EOF)
        solve();
    return 0;
}