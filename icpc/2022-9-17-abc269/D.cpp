#include <cstdio>
#include <cstring>

#include <map>
#include <queue>
#include <algorithm>

using namespace std;

using vec = pair<int, int>;

int n;
vec v[10000];
int m[10000];
map<vec, int> p;

void bfs(int s) {
    queue<int> q;
    m[s] = s;
    q.push(s);
    while (q.size()) {
        int i = q.front();
        q.pop();
        constexpr int dx[] = {-1, -1,  0,  0, +1, +1};
        constexpr int dy[] = {-1,  0, -1, +1,  0, +1};
        for (int k = 0; k < 6; k++) {
            int x = v[i].first + dx[k];
            int y = v[i].second + dy[k];
            if (p.count({x, y})) {
                int j = p[{x, y}];
                if (!m[j]) {
                    m[j] = s;
                    q.push(j);
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[i] = {x, y};
        p[v[i]] = i;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!m[i]) {
            cnt++;
            bfs(i);
        }
    }

    printf("%d\n", cnt);
    return 0;
}
