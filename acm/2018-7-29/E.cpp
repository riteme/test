#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 500

static int n, m, q;
static unordered_map<string, int> _id;
static bool GI[NMAX + 10][NMAX + 10];
static int G[NMAX + 10][NMAX + 10];

inline int id(const string &str) {
    if (!_id.count(str)) {
        _id[str] = ++n;
        // cerr << str << ": " << n << endl;
    }
    return _id[str];
}

void initialize() {
    cin >> m >> q;
    for (int i = 0; i < m; i++) {
        string a, r, b;
        cin >> a >> r >> b;
        int x = id(a), y = id(b);
        if (r == "is-a") {
            GI[x][y] = true;
            G[x][y] = max(G[x][y], 1);
        } else
            G[x][y] = max(G[x][y], 2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        int v = 0;
        if (G[i][k] && G[k][j]) v = max(G[i][k], G[k][j]);
        // cerr << k << " " << i << " " << j << G[i][j] << G[i][k] << G[k][j] << endl;
        G[i][j] = max(G[i][j], v);
        GI[i][j] |= GI[i][k] && GI[k][j];
    }

    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        int v = 0;
        if (G[i][k] && G[k][j]) v = max(G[i][k], G[k][j]);
        G[i][j] = max(G[i][j], v);
    }

    cout << boolalpha;
    for (int t = 1; t <= q; t++) {
        string a, r, b;
        cin >> a >> r >> b;
        int x = id(a), y = id(b);

        cout << "Query " << t << ": ";
        if (r == "is-a")
            cout << (x == y || GI[x][y]) << '\n';
        else
            cout << (G[x][y] == 2 ? true : false) << '\n';
    }

    return 0;
}
