#include <iostream>
#include <queue>

using namespace std;

#define NMAX 1000

static int n;
static int deg[NMAX + 1];
static vector<int> G[NMAX + 1];

static void initialize() {
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        deg[u]++;
        deg[v]++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

static int seq[NMAX - 1];
static bool marked[NMAX + 1];

/**
 * O(n log n) algorithm for encoding
 */
static void encode() {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1)
            q.push(i);
    }

    int pos = 0;
    while (pos < n - 2) {
        int u = q.top();
        marked[u] = true;
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (!marked[v]) {
                deg[v]--;

                if (deg[v] == 1)
                    q.push(v);

                // u's degree is 1
                seq[pos++] = v;
                break;
            }
        }
    }
}

int main() {
    initialize();
    encode();

    for (size_t i = 0; i < n - 2; i++) {
        cout << seq[i] << " ";
    }
    cout << endl;

    return 0;
}
