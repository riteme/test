#include <cstdio>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100

static int n;
static vector<int> G[NMAX + 10];
static vector<int> topo;
static int in[NMAX + 10];

void initialize() {
    scanf("%d", &n);
    memset(in, 0, sizeof(in));

    for (int i = 1; i <= n; i++) {
        int x;

        while (true) {
            scanf("%d", &x);
            if (x == 0) {
                break;
            }

            G[i].push_back(x);
            in[x]++;
        }  // while
    }      // for
}

void topological_sort() {
    in[0] = INT_MAX;

    while (topo.size() < n) {
        int v = 0;
        for (int i = 1; i <= n; i++) {
            if (in[i] < in[v]) {
                v = i;
            }
        }  // for

        for (int i = 0; i < G[v].size(); i++) {
            in[G[v][i]]--;
        }  // for

        topo.push_back(v);
        in[v] = INT_MAX;
    }  // while
}

int main() {
    initialize();

    topological_sort();

    for (int i = 0; i < topo.size(); i++) {
        printf("%d ", topo[i]);
    }  // for

    return 0;
}  // function main
