#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 300000

typedef pair<int, int> ForbiddenPair;

namespace std {
template <>
struct hash<ForbiddenPair> {
    auto operator()(const ForbiddenPair &p) const -> size_t {
        auto h = hash<int>();

        return h(p.first) * h(p.second);
    }
};  // struct hash<ForbiddenPair>
}

static int n, m, k;
static int degree1;
static unordered_set<ForbiddenPair> forbidden;
static list<int> unvisited;

static void initialize() {
    scanf("%d%d%d", &n, &m, &k);
    degree1 = n - 1;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        forbidden.insert({ u, v });
        forbidden.insert({ v, u });

        if (v == 1 || u == 1)
            degree1--;
    }  // for
}

static void bfs(int x, int &cnt) {
    // printf("dfs: x = %d\n", x);
    queue<int> q;
    q.push(x);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;

        while (true) {
            auto iter = find_if(
                unvisited.begin(),
                unvisited.end(),
                [u](int current) {
                    return forbidden.find({ u, current }) == forbidden.end();
                });

            if (iter == unvisited.end())
                break;

            q.push(*iter);
            unvisited.erase(iter);
        }
    }  // while
}

static int dfs(int x) {
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (i != x)
            unvisited.push_back(i);
    }  // for

    bfs(x, cnt);

    // printf("dfs: cnt = %d\n", cnt);

    return cnt;
}

static int count_subtree(int x) {
    unvisited.clear();

    for (int i = 1; i <= n; i++) {
        if (i != x)
            unvisited.push_back(i);
    }  // for

    int cnt = 0;
    while (true) {
        auto iter = find_if(
            unvisited.begin(),
            unvisited.end(),
            [x](int current) {
                return forbidden.find({ x, current }) == forbidden.end();
            });

        if (iter == unvisited.end())
            break;

        int reserve;
        int v = *iter;
        unvisited.erase(iter);
        bfs(v, reserve);
        cnt++;
    }  // while

    // printf("count: cnt = %d\n", cnt);
    return cnt;
}

int main() {
    initialize();

    if (degree1 < k)
        printf("impossible");
    else if (dfs(1) != n)
        printf("impossible");
    else {
        if (count_subtree(1) > k)
            printf("impossible");
        else
            printf("possible");
    }

    return 0;
}  // function main
