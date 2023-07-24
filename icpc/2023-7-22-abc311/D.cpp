#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

constexpr int NMAX = 200;

int n, m;
char S[NMAX + 10][NMAX + 10];
bool mark[NMAX + 10][NMAX + 10][4];

constexpr int dx[] = {1, 0, -1, 0};
constexpr int dy[] = {0, 1, 0, -1};

struct pos {
    int x, y, d;
};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", S[i] + 1);
    }

    queue<pos> Q;
    auto push = [&](int x, int y, int d) {
        if (mark[x][y][d])
            return;
        mark[x][y][d] = true;
        Q.push({x, y, d});
    };
    push(2, 2, 0);
    push(2, 2, 1);
    while (Q.size()) {
        auto [x, y, d] = Q.front();
        Q.pop();

        int tx = x + dx[d];
        int ty = y + dy[d];
        if (S[tx][ty] == '#') {
            for (int nd = 0; nd < 4; nd++) {
                push(x, y, nd);
            }
        } else {
            push(tx, ty, d);
        }
    }

    int ans = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (S[x][y] == '.' &&
                (mark[x][y][0] || mark[x][y][1] || mark[x][y][2] || mark[x][y][3]))
                ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}
