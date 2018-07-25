#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define INFTY 1000000000

static int nl, nr, m;
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &nl, &nr, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(nl + v);
        G[nl + v].push_back(u);
    }
}

static int match[NMAX + 10];
static int dist[NMAX + 10];

static int greedy_init() {
    int cnt = 0;

    for (int i = 1; i <= nl; i++) {
        for (size_t j = 0; j < G[i].size(); j++) {
            int v = G[i][j];

            if (!match[v]) {
                match[i] = v;
                match[v] = i;
                cnt++;

                break;
            }
        }
    }

    return cnt;
}

static bool bfs() {
    queue<int> q;

    for (int i = 1; i <= nl; i++) {
        if (!match[i]) {
            dist[i] = 0;
            q.push(i);
        } else {
            dist[i] = INFTY;
        }
    }

    dist[0] = INFTY;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] >= dist[0])
            continue;

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (dist[match[v]] >= INFTY) {
                dist[match[v]] = dist[u] + 1;
                q.push(match[v]);
            }
        }
    }

    return dist[0] < INFTY;
}

static bool dfs(int x) {
    if (!x)
        return true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (dist[match[v]] == dist[x] + 1 && dfs(match[v])) {
            match[x] = v;
            match[v] = x;

            return true;
        }
    }

    dist[x] = INFTY;
    return false;
}

static int hopcroft_karp() {
    int answer = greedy_init();

    while (bfs()) {
        for (int i = 1; i <= nl; i++)
            if (dist[i] == 0 && dfs(i))
                answer++;
    }

    return answer;
}

int main() {
    initialize();

    int cnt = hopcroft_karp();

    printf("%d\n", cnt);
    for (int i = 1; i <= nl; i++) {
        if (match[i])
            printf("%d ", match[i] - nl);
        else
            printf("0 ");
    }

    return 0;
}
