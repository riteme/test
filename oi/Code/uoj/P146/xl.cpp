#include <cstdio>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;
static int to[NMAX + 10];
static int id[NMAX + 10];
static int dist[NMAX + 10];

inline int dfs(int x, int num) {
    int cnt = 0;
    while (!id[x]) {
        id[x] = num;
        if (!id[to[x]])
            dist[to[x]] = dist[x] + 1;
        x = to[x];
        cnt++;
    }

    if (id[x] != num)
        return INT_MAX;

    return cnt - dist[x];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", to + i);

    int dcnt = 1;
    int answer = INT_MAX;
    for (int i = 1; i <= n; i++)
        if (!id[i])
            answer = min(answer, dfs(i, dcnt++));

    printf("%d\n", answer);
    return 0;
}
