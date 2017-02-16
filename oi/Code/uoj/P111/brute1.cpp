#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

#define NMAX 30000

static int n, m;
static int b[NMAX + 10];
static int p[NMAX + 10];
static vector<int> doge[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", b + i, p + i);
        doge[b[i]].push_back(i);
    }  // for
}

static int dist[NMAX + 10];
static bool exist[NMAX + 10];

int main() {
    initialize();

    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;

    for (size_t i = 0; i < doge[b[0]].size(); i++) {
        int u = doge[b[0]][i];
        q.push(u);
        dist[u] = 0;
        exist[u] = true;
    }  // for

    while (!q.empty()) {
        int u = q.front();
        exist[u] = false;
        q.pop();

        for (int i = 1; b[u] + i * p[u] < n; i++) {
            int x = b[u] + i * p[u];

            for (size_t j = 0; j < doge[x].size(); j++) {
                int v = doge[x][j];

                if (dist[u] + i < dist[v]) {
                    dist[v] = dist[u] + i;

                    if (!exist[v]) {
                        exist[v] = true;
                        q.push(v);
                    }
                }
            }  // for
        }      // for

        for (int i = 1; b[u] - i * p[u] >= 0; i++) {
            int x = b[u] - i * p[u];

            for (size_t j = 0; j < doge[x].size(); j++) {
                int v = doge[x][j];

                if (dist[u] + i < dist[v]) {
                    dist[v] = dist[u] + i;

                    if (!exist[v]) {
                        exist[v] = true;
                        q.push(v);
                    }
                }
            }  // for
        }      // for
    }          // while

    if (dist[1] < 0x3f3f3f3f)
        printf("%d\n", dist[1]);
    else
        printf("-1\n");

    return 0;
}  // function main
