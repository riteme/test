#include <cstdio>
#include <climits>
#include <cctype>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100

struct Point {
    Point()
        : x(0), y(0) {}

    Point(int _x, int _y)
        : x(_x), y(_y) {}

    int x;
    int y;
};

static int n, m;
static int map[NMAX + 10][NMAX + 10];
static int tox[NMAX + 10][NMAX + 10];
static int toy[NMAX + 10][NMAX + 10];
static Point P[256];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c = getchar();
            while (!isalnum(c))
                c = getchar();

            if (c == '0')
                map[i][j] = 0;
            else if (c == '1')
                map[i][j] = 1;
            else {
                map[i][j] = c;
                if (P[c].x == 0)
                    P[c] = Point(i, j);
                else {
                    tox[P[c].x][P[c].y] = i;
                    toy[P[c].x][P[c].y] = j;
                    tox[i][j] = P[c].x;
                    toy[i][j] = P[c].y;
                }
            }
        }
    }
}

static int dist[NMAX + 10][NMAX + 10];
static bool visited[NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10][NMAX + 10];

int main() {
    freopen("way.in", "r", stdin);
    freopen("way.out", "w", stdout);
    initialize();

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dist[i][j] = INT_MAX;

    queue<Point> q;
    dist[1][1] = 0;
    marked[1][1] = true;
    q.push(Point(1, 1));
    
    while (!q.empty()) {
        Point u = q.front();
        marked[u.x][u.y] = false;
        q.pop();

        if (map[u.x][u.y] == 1)
            continue;

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        for (int pos = 0; pos < 4; pos++) {
            int tx = u.x + dx[pos];
            int ty = u.y + dy[pos];

            if (map[tx][ty] == 1)
                continue;
            if (map[tx][ty] > 1 && !visited[tx][ty]) {
                int cx = tox[tx][ty];
                int cy = toy[tx][ty];

                marked[cx][cy] = true;
                visited[tx][ty] = true;
                dist[cx][cy] = dist[u.x][u.y] + 1;
                q.push(Point(cx, cy));
            } else if (map[tx][ty] == 0) {
                if (dist[u.x][u.y] + 1 < dist[tx][ty]) {
                    dist[tx][ty] = dist[u.x][u.y] + 1;

                    if (!marked[tx][ty]) {
                        marked[tx][ty] = true;
                        q.push(Point(tx, ty));
                    }
                }
            }
        }
    }

    if (dist[n][m] >= INT_MAX)
        puts("No Solution.");
    else
        printf("%d\n", dist[n][m]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
