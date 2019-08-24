/**
 * 体现自己智商捉鸡的时候到了
 * mdzz NOIP又在第三题放个搜索.....
 * 注意细节！
 * 还有放在这个位置的题目肯定是要你剪枝的！
 * 向左可以用向右替换！除了左边是空的情况下！有了这个剪枝就可以过了！
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

static int n;
static int data[6][8];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= 5; i++) {
        int pos = 1;

        while (true) {
            int x;
            scanf("%d", &x);

            if (x == 0)
                break;

            data[i][pos++] = x;
        }  // while
    }      // for
}

static int current;
static int map[6][6][8];
static bool marked1[6][8];
static bool marked2[6][8];

static void fall() {
    for (int i = 1; i <= 5; i++) {
        int* pos = remove(&map[current][i][1], &map[current][i][8], 0);
        fill(pos, &map[current][i][8], 0);
    }  // for
}

static bool fuck() {
    bool flag = false;

    memset(marked1, 0, sizeof(marked1));
    memset(marked2, 0, sizeof(marked2));

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            if (map[current][i][j] == 0)
                continue;

            if (!marked1[i][j]) {
                int top = j, bottom = j;

                while (bottom > 1 &&
                       map[current][i][bottom - 1] == map[current][i][j])
                    bottom--;
                while (top < 7 &&
                       map[current][i][top + 1] == map[current][i][j])
                    top++;

                if (top - bottom >= 2)
                    for (int k = bottom; k <= top; k++)
                        marked1[i][k] = true;
            }

            if (!marked2[i][j]) {
                int left = i, right = i;

                while (left > 1 &&
                       map[current][left - 1][j] == map[current][i][j])
                    left--;
                while (right < 5 &&
                       map[current][right + 1][j] == map[current][i][j])
                    right++;

                if (right - left >= 2)
                    for (int k = left; k <= right; k++)
                        marked2[k][j] = true;
            }

        }  // for
    }      // for

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            if (marked1[i][j] || marked2[i][j]) {
                map[current][i][j] = 0;
                flag = true;
            }
        }  // for
    }      // for

    return flag;
}

struct Step {
    int x, y, direction;
};  // struct Step

static Step steps[6];

static bool dfs(int step) {
    if (step == 0) {
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 7; j++) {
                if (map[0][i][j])
                    return false;
            }  // for
        }      // for

        return true;
    }

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            if (map[step][i][j] == 0)
                continue;

            current = step - 1;

            // Right
            if (i < 5) {
                memcpy(map[step - 1], map[step], sizeof(data));
                swap(map[step - 1][i][j], map[step - 1][i + 1][j]);

                fall();
                while (true) {
                    if (!fuck())
                        break;
                    fall();
                }  // while

                steps[step].x = i;
                steps[step].y = j;
                steps[step].direction = 1;

                if (dfs(step - 1))
                    return true;
            }

            current = step - 1;

            // Left
            if (i > 1 && map[step][i - 1][j] == 0) {
                memcpy(map[step - 1], map[step], sizeof(data));
                swap(map[step - 1][i][j], map[step - 1][i - 1][j]);

                fall();
                while (true) {
                    if (!fuck())
                        break;
                    fall();
                }  // while

                steps[step].x = i;
                steps[step].y = j;
                steps[step].direction = -1;

                if (dfs(step - 1))
                    return true;
            }
        }  // for
    }      // for

    return false;
}

int main() {
    initialize();

    memcpy(map[n], data, sizeof(data));
    if (!dfs(n)) {
        puts("-1");
        return 0;
    }

    for (int i = n; i >= 1; i--) {
        printf(
            "%d %d %d\n", steps[i].x - 1, steps[i].y - 1, steps[i].direction);
    }  // for

    return 0;
}  // function main
