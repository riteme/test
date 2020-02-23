/**
 * 显然是最短路，但是不能直接上
 * 数据范围是30000，容易联想到n sqrt n的算法
 * 对于p大于sqrt n的，暴力连边
 * **对于p小于等于sqrt n的**：
 * 将每栋楼视为sqrt n层，第i层是P = i的doge的传送点
 * 每次先到达对应的楼层，然后走到相邻的楼栋
 * 每层楼都可以到一楼
 * 这样可以分析出点数和边数都是n sqrt n的！
 * 后面这部分没有想到，做法真机智
 */

#define NDEBUG

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 30000
#define SQRTN 200

static int n, m;
static int B[NMAX + 10], P[NMAX + 10];
static vector<int> doge[NMAX + 10];
static int BLOCKSIZE;

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", B + i, P + i);
        doge[B[i]].push_back(i);
    }  // for

    BLOCKSIZE = min(10, static_cast<int>(sqrt(n)));
}

typedef pair<int, int> State;
static int dist[SQRTN + 10][NMAX + 10];
static bool exist[SQRTN + 10][NMAX + 10];
static queue<State> q;

inline void relax(int ux, int uy, int vx, int vy, int d) {
    if (dist[ux][uy] + d < dist[vx][vy]) {
        dist[vx][vy] = dist[ux][uy] + d;

        if (!exist[vx][vy]) {
            exist[vx][vy] = true;
            q.push(State(vx, vy));
        }
    }
}

int main() {
    initialize();

    memset(dist, 0x3f, sizeof(dist));
    dist[0][B[0]] = 0;
    exist[0][B[0]] = true;
    q.push(State(0, B[0]));

    while (!q.empty()) {
        State u = q.front();
        int h = u.first, x = u.second;
        exist[h][x] = false;
        q.pop();

        if (h > 0) {
            if (x + h < n)
                relax(h, x, h, x + h, 1);
            if (x - h >= 0)
                relax(h, x, h, x - h, 1);
            relax(h, x, 0, x, 0);
        } else {
            for (size_t i = 0; i < doge[x].size(); i++) {
                int dog = doge[x][i];
                int p = P[dog];

                if (p <= BLOCKSIZE)
                    relax(0, x, p, x, 0);
                else {
                    for (int k = 1; x + k * p < n; k++)
                        relax(0, x, 0, x + k * p, k);
                    for (int k = 1; x - k * p >= 0; k++)
                        relax(0, x, 0, x - k * p, k);
                }
            }  // for
        }
    }  // while

    if (dist[0][B[1]] < 0x3f3f3f3f)
        printf("%d\n", dist[0][B[1]]);
    else
        printf("-1\n");

    return 0;
}  // function main
