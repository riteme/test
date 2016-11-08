#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 20

struct Point {
    Point(int _x, int _y)
        : x(_x), y(_y) {}

    int x, y;
};

static int n, m;
static char map[NMAX + 10][NMAX + 10];
static int dist[NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c = getchar();
            while (!isalpha(c)) {
                c = getchar();
            }
            
            map[i][j] = c;
        }
    }
}

inline int w(int x1, int y1, int x2, int y2) {
    return map[x1][y1] != map[x2][y2];
}

int main() {
    freopen("brick.in", "r", stdin);
    freopen("brick.out", "w", stdout);
    initialize();

    if (n == 0 || m == 0) {
        puts("0");
        return 0;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dist[i][j] = INT_MAX;

    for (int i = 0; i <= n + 1; i++)
        marked[i][0] = marked[i][m + 1] = true;
    for (int i = 0; i <= m + 1; i++)
        marked[0][i] = marked[n + 1][i] = true;

    queue<Point> q;
    for (int i = 1; i <= m; i++) {
        dist[1][i] = 1;
        marked[1][i] = true;
        q.push(Point(1, i));
    }

    while (!q.empty()) {
        Point u = q.front();
        marked[u.x][u.y] = false;
        q.pop();

        const int dx[] = {-1, 1, 0, 0,};
        const int dy[] = {0, 0, -1, 1};
        for (int pos = 0; pos < 4; pos++) {
            int tx = u.x + dx[pos];
            int ty = u.y + dy[pos];

            if (dist[u.x][u.y] + w(u.x, u.y, tx, ty) < dist[tx][ty]) {
                dist[tx][ty] = dist[u.x][u.y] + w(u.x, u.y, tx, ty); 

                if (!marked[tx][ty]) {
                    marked[tx][ty] = true;
                    q.push(Point(tx, ty));
                }
            }
        }
    }

    int answer = INT_MAX;
    for (int i = 1; i <= m; i++)
        answer = min(answer, dist[n][i]);
    printf("%d\n", answer);

    return 0;
}
