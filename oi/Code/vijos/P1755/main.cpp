#include <cstdio>
#include <climits>

#include <algorithm>

using namespace std;

static int map[10][10];
static bool line[10][10];
static bool col[10][10];
static bool block[10][10];

static int answer;

inline int blockid(int x, int y) {
    return (x - 1) / 3 + 1 + ((y - 1) / 3) * 3;
}

inline int value(int x, int y, int v) {
    return (10 - max(abs(x - 5), abs(y - 5))) * v;
}

static int limit = INT_MAX;

static void dfs(int x, int y, int sum) {
    if (x > 9)
        dfs(1, y + 1, sum);
    else if (y > 9) {
        limit--;

        if (answer < sum)
            answer = sum;
    } else {
        if (map[x][y] == 0) {
            int id = blockid(x, y);
            for (int i = 1; i <= 9 && limit; i++) {
                if (line[x][i] && col[y][i] && block[id][i]) {
                    line[x][i] = col[y][i] = block[id][i] = false;

                    dfs(x + 1, y, sum + value(x, y, i));

                    line[x][i] = col[y][i] = block[id][i] = true;
                }
            }
        } else if (limit)
            dfs(x + 1, y, sum);
    }
}

int main() {
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            line[i][j] = col[i][j] = block[i][j] = true;

    int pre = 0;
    int cnt = 0;
    bool flag = true;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            scanf("%d", &map[i][j]);

            if (map[i][j]) {
                cnt++;

                if (line[i][map[i][j]] == false ||
                    col[j][map[i][j]] == false ||
                    block[blockid(i, j)][map[i][j]] == false)
                    flag = false;

                line[i][map[i][j]] = false;
                col[j][map[i][j]] = false;
                block[blockid(i, j)][map[i][j]] = false;
                pre += value(i, j, map[i][j]);
            }
        }
    }

    // puts("read");

    if (flag)
        dfs(1, 1, 0);

    // printf("limit = %d\n", limit);

    if (answer == 0)
        puts("-1");
    else
        printf("%d\n", answer + pre);

    return 0;
}
