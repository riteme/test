#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

static int n;
static int state[6][5][7];

static void fall(int a[5][7]) {
    for (int i = 0; i < 5; i++) {
        int pos = 0;

        for (int j = 0; j < 7; j++) {
            if (a[i][j])
                a[i][pos++] = a[i][j];
        }

        for (; pos < 7; pos++)
            a[i][pos] = 0;
    }
}

static bool clear(int a[5][7]) {
    bool marked[5][7];
    memset(marked, 0, sizeof(marked));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (a[i][j] == 0)
                continue;

            if (0 < i && i < 4 &&
                a[i - 1][j] == a[i][j] &&
                a[i + 1][j] == a[i][j])
                marked[i - 1][j] = marked[i + 1][j] = marked[i][j] = true;
            if (0 < j && j < 7 &&
                a[i][j - 1] == a[i][j] &&
                a[i][j + 1] == a[i][j])
                marked[i][j - 1] = marked[i][j + 1] = marked[i][j] = true;
        }
    }

    bool result = false;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (marked[i][j]) {
                a[i][j] = 0;
                result = true;
            }
        }
    }

    return result;
}

static int x[5];
static int y[5];
static int d[5];

static bool dfs(int step) {
    bool status = true;
    for (int i = 0; i < 5 && status; i++)
        for (int j = 0; j < 7 && status; j++)
            if (state[step][i][j])
                status = false;

    if (status)
        return step == n;
    if (step == n)
        return false;

    bool flag = false;
    for (int i = 0; i < 5 && !flag; i++) {
        for (int j = 0; j < 7 && !flag; j++) {
            if (state[step][i][j] == 0)
                continue;

            x[step] = i;
            y[step] = j;

            if (!flag && i < 4) {
                d[step] = 1;
                memcpy(&state[step + 1][0][0],
                       &state[step][0][0],
                       sizeof(int) * 35);
                swap(state[step + 1][i][j], state[step + 1][i + 1][j]);

                fall(state[step + 1]);
                while (clear(state[step + 1]))
                    fall(state[step + 1]);
                
                flag = dfs(step + 1);
            }

            if (!flag && i > 0 && state[step][i - 1][j] == 0) {
                d[step] = -1;
                memcpy(&state[step + 1][0][0],
                       &state[step][0][0],
                       sizeof(int) * 35);
                swap(state[step + 1][i][j], state[step + 1][i - 1][j]);

                fall(state[step + 1]);
                while (clear(state[step + 1]))
                    fall(state[step + 1]);
                
                flag = dfs(step + 1);
            }
        }
    }

    return flag;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 5; i++) {
        int pos = 0;
        int v;
        
        while (true) {
            scanf("%d", &v);
            
            if (v == 0)
                break;

            state[0][i][pos++] = v;
        }
    }

    if (dfs(0))
        for (int i = 0; i < n; i++)
            printf("%d %d %d\n", x[i], y[i], d[i]);
    else
        puts("-1");

    return 0;
}
