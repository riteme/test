#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 1500000

static int n, m;
static vector<vector<int>> trees;

int main() {
    scanf("%d%d", &n, &m);

    trees.push_back(vector<int>(n + 1));
    trees.push_back(vector<int>(n + 1));

    char command[10];
    while (m--) {
        scanf("%s", command);

        if (command[0] == 'A') {
            int v, p, x;
            scanf("%d%d%d", &v, &p, &x);

            trees[v][p] += x;
        } else if (command[0] == 'Q') {
            int v, l, r;
            scanf("%d%d%d", &v, &l, &r);

            int answer = 0;
            for (int i = l; i <= r; i++) {
                answer += trees[v][i];
            }

            printf("%d\n", answer);
        } else {
            int v;
            scanf("%d", &v);

            trees.push_back(trees[v]);
        }
    }

    return 0;
}
