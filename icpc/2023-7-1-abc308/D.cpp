#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

constexpr int NMAX = 500;

int m, m;
char S[NMAX + 10][NMAX + 10];
bool f[NMAX + 10][NMAX + 10][5];
const char *T = "snuke";

struct pos {
    int x, y, k;
};

int main() {
    scanf("%d%d", &m, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", S[i] + 1);
    }

    std::queue<pos> q;
    if (S[1][1] == T[0])
        q.push({1, 1, 0});
    while (q.size()) {
        pos p = q.front();
        q.pop();

        int l = (p.k + 1) % 5;
        constexpr int dx[] = {-1, 1, 0, 0};
        constexpr int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int x = p.x + dx[i];
            int y = p.y + dy[i];
            if (!f[x][y][l] && S[x][y] == T[l]) {
                f[x][y][l] = true;
                q.push({x, y, l});
            }
        }
    }

    bool okay = false;
    for (int k = 0; k < 5; k++) {
        okay |= f[m][m][k];
    }

    puts(okay ? "Yes" : "No");
    return 0;
}
