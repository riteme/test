#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, m;
static int indegree[NMAX + 10];
static int sorted[NMAX + 10];
static int a[NMAX + 10];
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        // G[x].push_back(y);
        G[y].push_back(x);
        indegree[x]++;
    }  // for
}

struct cmp {
    bool operator()(const int &a, const int &b) const {
        return a < b;
    }
};  // struct cmp

static void topological_sort() {
    priority_queue<int, vector<int>, cmp> q;

    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }  // for

    int pos = n;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        sorted[pos--] = u;

        for (unsigned i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            indegree[v]--;

            if (indegree[v] == 0) {
                q.push(v);
            }
        }  // for
    }      // while
}

int main() {
    initialize();
    topological_sort();

    for (int i = 1; i <= n; i++) {
        a[sorted[i]] = i;
    }  // for

    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }  // for

    return 0;
}  // function main
