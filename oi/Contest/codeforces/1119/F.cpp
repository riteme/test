#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 250000

typedef long long i64;

struct Edge {
    int v, w;
};

static int n;
static vector<TEdge> T[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        T[u].push_back({v, w});
        T[v].push_back({u, w});
    }
    return 0;
}
