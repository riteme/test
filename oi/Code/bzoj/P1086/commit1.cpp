/**
 * WA
 */

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, B;
static vector<int> G[NMAX + 10];
static int cnt;
static int id[NMAX + 10];
static int capital[NMAX + 10];
static bool marked[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &B);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }
}

typedef vector<int> IntVector;

static IntVector dfs(int x) {
    marked[x] = true;
    int size = 0;
    vector<IntVector> children;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (marked[v])
            continue;

        IntVector vec = dfs(v);
        size += vec.size();
        children.push_back(vec);

        if (size >= B) {
            cnt++;
            size = 0;
            capital[cnt] = x;

            for (size_t j = 0; j < children.size(); j++) {
                IntVector &c = children[j];

                for (size_t k = 0; k < c.size(); k++) {
                    int p = c[k];
                    id[p] = cnt;
                }
            }

            children.clear();
        }
    }
    
    IntVector ret;
    ret.push_back(x);
    for (size_t i = 0; i < children.size(); i++) {
        IntVector &c = children[i];
        for (size_t j = 0; j < c.size(); j++) {
            ret.push_back(c[j]);
        }
    }

    return ret;
}

int main() {
    initialize();

    IntVector remain = dfs(1);

    bool ok = false;
    if (remain.size() >= B) {
        ok = true;
        cnt++;
        capital[cnt] = 1;

        for (size_t i = 0; i < remain.size(); i++) {
            int p = remain[i];
            id[p] = cnt;
        }
    } else {
        for (size_t i = 0; i < G[1].size(); i++) {
            int v = G[1][i];

            if (id[v]) {
                ok = true;

                for (size_t j = 0; j < remain.size(); j++) {
                    int p = remain[j];

                    id[p] = id[v];
                }

                break;
            }
        }
    }

    if (ok) {
        printf("%d\n", cnt);

        for (int i = 1; i <= n; i++) {
            printf("%d ", id[i]);
        }
        printf("\n");

        for (int i = 1; i <= cnt; i++) {
            printf("%d ", capital[i]);
        }
        printf("\n");
    } else
        puts("0");

    return 0;
}
