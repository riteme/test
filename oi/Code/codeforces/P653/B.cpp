#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

static int n, q;
static vector<char> G[256];

static void initialize() {
    scanf("%d%d", &n, &q);

    char buffer1[10], buffer2[10];
    for (int i = 0; i < q; i++) {
        scanf("%s%s", buffer1, buffer2);

        G[static_cast<unsigned>(buffer2[0])].push_back(buffer1[0]);
    }  // for
}

static int dfs(char x, int depth = 0) {
    if (depth == n - 1)
        return 1;
    else {
        int son = 0;

        for (unsigned i = 0; i < G[static_cast<unsigned>(x)].size(); i++) {
            son += dfs(G[static_cast<unsigned>(x)][i], depth + 1);
        }  // for

        return son;
    }
}

int main() {
    initialize();

    printf("%d", dfs('a'));

    return 0;
}  // function main
