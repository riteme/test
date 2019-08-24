#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

//#define BSIZE 1
#define BSIZE 500
#define NMAX 100000

struct Point {
    int x, y, z;
};

static int n, m, h, q;
static int cnt;
static Point p[BSIZE];

static int tail;
static struct Block {
    void build() {
        dat = new int[n * m * h];
        memset(dat, 0, sizeof(int) * n * m * h);
    }

    int *dat;

    int &operator()(const Point &u) {
        return dat[u.x * m * h + u.y * h + u.z];
    }

    int &operator()(int x, int y, int z) {
        return dat[x * m * h + y * h + z];
    }
} b[NMAX + 10];

int main() {
    scanf("%d%d%d%d", &n, &m, &h, &q);
    while (q--) {
        int op, x, y, z;
        scanf("%d%d%d%d", &op, &x, &y, &z);
        x--; y--; z--;
        if (op == 1) {
            if (cnt == BSIZE) {
                auto &t = b[tail];
                b[tail++].build();
                queue<Point> Q;
                for (int i = 0; i < cnt; i++) {
                    Q.push(p[i]);
                    t(p[i]) = 1;
                }
                cnt = 0;
                while (!Q.empty()) {
                    auto u = Q.front();
                    Q.pop();
                    auto add = [&Q, &t, &u](int x, int y, int z) {
                        if (x < 0 || x >= n ||
                            y < 0 || y >= m ||
                            z < 0 || z >= h ||
                            t(x, y, z)) return;
                        t(x, y, z) = t(u) + 1;
                        Q.push({x, y, z});
                    };
                    add(u.x + 1, u.y, u.z);
                    add(u.x - 1, u.y, u.z);
                    add(u.x, u.y + 1, u.z);
                    add(u.x, u.y - 1, u.z);
                    add(u.x, u.y, u.z + 1);
                    add(u.x, u.y, u.z - 1);
                }
            }
            p[cnt++] = {x, y, z};
        } else {
            int ans = INT_MAX;
            for (int i = 0; i < tail; i++)
                ans = min(ans, b[i](x, y, z) - 1);
            for (int i = 0; i < cnt; i++)
                ans = min(ans, abs(p[i].x - x) + abs(p[i].y - y) + abs(p[i].z - z));
            printf("%d\n", ans);
        }
    }
    return 0;
}
